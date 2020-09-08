#include "serversettings.h"
#include "ui_serversettings.h"
#include "strings/strings_serversettingswindow.h"
#include <QMessageBox>
#include <QString>
#include <QTime>
#include <windows.h>

#define _MAX_PLAYERS_QUANTITY_ 4

using namespace serverSettingsWindowStrings;

serverSettings::serverSettings(QWidget *parent) :
    QWidget(parent),
    isWaitingFinished(false),
    isAnswerInwritting(false),
    ui(new Ui::serverSettings),
    nextBlockSize(0)
{
    ui->setupUi(this);
    setWindowTitle(MSG_SERVERSETTINGS_TITLE());
    playersList = new player[_MAX_PLAYERS_QUANTITY_];
    tcpServer = new QTcpServer(this);
    QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(playerRequest()));
}

serverSettings::~serverSettings()
{
    delete [] playersList;
    delete tcpServer;
    delete ui;
}

void serverSettings::on_startServerButton_clicked()
{
    if(!tcpServer->listen(QHostAddress::Any, ui->portNumberEdit->text().toInt()))
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_COULD_NOT_START_SERVER());
        tcpServer->close();
        return;
    }
    else
    {
        isWaitingFinished = false;
        currentNumberOfPlayers = 0;
        QMessageBox::information(NULL, MSG_INFO(), MSG_SERVER_STARTED());
    }
}

void serverSettings::on_startGameButton_clicked()
{
    isAnswerInwritting = ui->answerInwritingBox->isChecked();
    if (isAnswerInwritting)
    {
        for (int i=0; i<currentNumberOfPlayers; i++)
        {
            sendDataToPlayer(playersSocketList[i], i, MSG_INWRITTING_PREFFIX());
        }
    }
    emit settingsIsSet();
    hide();
}

void serverSettings::on_stopServerButton_clicked()
{
    playersSocketList.clear();
    for (int i=0; i<currentNumberOfPlayers; i++)
    {
        playersList[i].ID = 0;
        playersList[i].playerSocket = NULL;
        playersList[i].name = "";
        playersList[i].inGameNumber = 0;
        playersList[i].state = false;
    }
    currentNumberOfPlayers = 0;
    QFile *serverLog = new QFile("./server.log");
    if (!serverLog->open(QIODevice::Append))
    {
        QMessageBox::critical(NULL, MSG_ERROR(), "Не удалость открыть лог-файл");
    }
    else
    {
        serverLog->write(ui->testFieldText->toPlainText().toUtf8());
        serverLog->close();
        delete serverLog;
    }
    tcpServer->close();
    QMessageBox::information(NULL, MSG_INFO(), MSG_SERVER_STOPPED());
    close();
}

void serverSettings::playerRequest()
{
    if (currentNumberOfPlayers <= ui->maxNumberOfPlayersBox->value())
    {
        currentNumberOfPlayers++;
        QTcpSocket *playerSocket = tcpServer->nextPendingConnection();
        QObject::connect(playerSocket, SIGNAL(disconnected()), playerSocket, SLOT(deleteLater()));
        QObject::connect(playerSocket, SIGNAL(readyRead()), this, SLOT(readPlayersData()));
        QObject::connect(playerSocket, SIGNAL(disconnected()), this, SLOT(playerDisconnected()));
        playersSocketList[currentNumberOfPlayers-1] = playerSocket;
        playersList[currentNumberOfPlayers-1].playerSocket = playerSocket;
        playersList[currentNumberOfPlayers-1].state = true;
        playersList[currentNumberOfPlayers-1].inGameNumber = currentNumberOfPlayers;
        playersList[currentNumberOfPlayers-1].ID = playerSocket->socketDescriptor();
        sendDataToPlayer(playerSocket, currentNumberOfPlayers-1, "Connection installed");
    }
}

void serverSettings::readPlayersData()
{
    QTcpSocket *playerSocket = (QTcpSocket*)sender();
    QDataStream dataFromPlayer(playerSocket);
    dataFromPlayer.setVersion(QDataStream::Qt_5_12);
    QString datastring;
    for(;;)
    {
        if (!nextBlockSize)
        {
            if (playerSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            dataFromPlayer >> nextBlockSize;
        }
        if (playerSocket->bytesAvailable() < nextBlockSize)
        {
            break;
        }
        QTime time;
        QString str;
        dataFromPlayer >> time >> str;
        datastring = str;
        QString strMessage = time.toString() + " " + "Players has sent: " + str;
        ui->testFieldText->append(strMessage);
        nextBlockSize = 0;

        if (datastring.startsWith(MSG_NAME_PREFFIX()))
        {
            for (int i = 0; i < ui->maxNumberOfPlayersBox->value(); i++)
            {
                if (playersList[i].ID == playerSocket->socketDescriptor())
                {
                    QStringList list = datastring.split(":#");
                    playersList[i].name = list[1];
                    sendDataToPlayer(playerSocket, playersList[i].inGameNumber-1, MSG_ID_PREFFIX() + QString::number(playersList[i].ID));
                    break;
                }
            }
        }

        int playerNumber = 0;
        if (datastring.startsWith(MSG_ID_PREFFIX()))
        {
            QString emptyAnswer = "";
            for (int i = 0; i < ui->maxNumberOfPlayersBox->value(); i++)
            {
                if (playersList[i].ID == playerSocket->socketDescriptor())
                {
                    playerNumber = playersList[i].inGameNumber;
                    break;
                }
            }
            emit newAnswerSignal(playerNumber);
        }

        if (datastring.startsWith(MSG_ANSWER_PREFFIX()))
        {
            QStringList list = datastring.split(":#");
            emit textAnswerSignal(list[1]);
        }
    }
}

void serverSettings::sendDataToPlayer(QTcpSocket *playerSocket, int numberInList, const QString &data)
{

    bool playerState = playersList[numberInList].state;
    if (!playerState || playerSocket == NULL)
    {
        ui->testFieldText->append(QString::number(playersList[numberInList].ID) + " - UnconnectedState!\n");
        return;
    }

    QByteArray arrBlock;
    QDataStream dataToPlayer(&arrBlock, QIODevice::WriteOnly);
    dataToPlayer.setVersion(QDataStream::Qt_5_12);
    dataToPlayer << quint16(0) << QTime::currentTime() << data;
    dataToPlayer.device()->seek(0);
    dataToPlayer << quint16(arrBlock.size() - sizeof(quint16));
    playerSocket->write(arrBlock);
}

void serverSettings::sendQuestionToPlayers(int number, QString name, int value, QString Question)
{
    for (int i=0; i<playersSocketList.size(); i++)
    {
        sendDataToPlayer(playersSocketList[i], i, MSG_NUMBER_PREFFIX() + QString::number(number));
        sendDataToPlayer(playersSocketList[i], i, MSG_THEME_PREFFIX() + name);
        sendDataToPlayer(playersSocketList[i], i, MSG_VALUE_PREFFIX() + QString::number(value));
        if (ui->answerInwritingBox->isChecked())
        {
            sendDataToPlayer(playersSocketList[i], i, MSG_QUESTION_PREFFIX() + Question);
        }
    }
}

void serverSettings::sendCurrentResultsToPlayers(int p1, int p2, int p3, int p4)
{

    for (int i=0; i<playersSocketList.size(); i++)
    {
        sendDataToPlayer(playersSocketList[i], i, MSG_SUM1_PREFFIX() + QString::number(p1));
        sendDataToPlayer(playersSocketList[i], i, MSG_SUM2_PREFFIX() + QString::number(p2));
        sendDataToPlayer(playersSocketList[i], i, MSG_SUM3_PREFFIX() + QString::number(p3));
        sendDataToPlayer(playersSocketList[i], i, MSG_SUM4_PREFFIX() + QString::number(p4));
    }
}

void serverSettings::sendPlayersToPlayers(QString p1, QString p2, QString p3, QString p4)
{
    for (int i=0; i<playersSocketList.size(); i++)
    {
        sendDataToPlayer(playersSocketList[i], i, MSG_NAME1_PREFFIX() + p1);
        sendDataToPlayer(playersSocketList[i], i, MSG_NAME2_PREFFIX() + p2);
        sendDataToPlayer(playersSocketList[i], i, MSG_NAME3_PREFFIX() + p3);
        sendDataToPlayer(playersSocketList[i], i, MSG_NAME4_PREFFIX() + p4);
    }
}

void serverSettings::sendQueueToPlayer(int number, int queue)
{
    sendDataToPlayer(playersSocketList[number-1], number-1, MSG_QUEUE_PREFFIX() + QString::number(queue));
}

void serverSettings::sendCorrectnessToPlayer(int number, QString result)
{
    sendDataToPlayer(playersSocketList[number-1], number-1, MSG_CORRECTNESS_PREFFIX() + result);
}

void serverSettings::sendTimeoutToPlayers()
{

    for (int i=0; i<playersSocketList.size(); i++)
    {
        sendDataToPlayer(playersSocketList[i], i, MSG_TIMEOUT_PREFFIX());
    }
}

void serverSettings::playerDisconnected()
{
    /*QTcpSocket *playerSocket = (QTcpSocket*)sender();
    int id = playerSocket->socketDescriptor();*/
    for (int i=0; i<currentNumberOfPlayers; i++)
    {        
        playersList[i].state = false;
    }
    QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_DISCONNECTED());
}


void serverSettings::sendTimeToPlayers(QString data)
{
    for (int i=0; i<playersSocketList.size(); i++)
    {
        sendDataToPlayer(playersSocketList[i], i, data);
    }
}
