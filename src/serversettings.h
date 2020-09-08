#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>

namespace Ui {
class serverSettings;
}

class serverSettings : public QWidget
{
    Q_OBJECT

public:
    explicit serverSettings(QWidget *parent = nullptr);
    ~serverSettings();

    struct player
    {
        QTcpSocket *playerSocket;
        bool state;
        int inGameNumber;
        int ID;
        QString name;
    };

    player *playersList;
    bool isWaitingFinished;
    bool isAnswerInwritting;
    void sendQuestionToPlayers(int number, QString name, int value, QString Question);
    void sendPlayersToPlayers(QString p1, QString p2, QString p3, QString p4);
    void sendCurrentResultsToPlayers(int p1, int p2, int p3, int p4);
    void sendQueueToPlayer(int number, int queue);
    void sendCorrectnessToPlayer(int number, QString result);
    void sendTimeoutToPlayers();
    void sendTimeToPlayers(QString data);

signals:
    void settingsIsSet();
    void newAnswerSignal(int playerNumber);
    void textAnswerSignal(QString answer);

public slots:

private:
    Ui::serverSettings *ui;
    QTcpServer *tcpServer;
    quint16 nextBlockSize;
    QMap<int,QTcpSocket*> playersSocketList;
    //QList<QTcpSocket*> playersSocketList;
    int currentNumberOfPlayers;
    void sendDataToPlayer(QTcpSocket *playerSocket, int numberInList, const QString &data);

private slots:
    void playerRequest();
    void on_startServerButton_clicked();
    void readPlayersData();
    void on_stopServerButton_clicked();
    void on_startGameButton_clicked();
    void playerDisconnected();
};

#endif // SERVERSETTINGS_H
