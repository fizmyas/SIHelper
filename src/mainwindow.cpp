#include "mainwindow.h"
#include "strings/strings_mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

using namespace mainwindowStrings;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
#ifdef _NETWORK_GAME_
    isNetworkGame(false),
#endif // _NETWORK_GAME_
    isGamePlaying(false),
    isAppealsLimited(false),
    playersQuantity(0),
    answerQuantity (0),
    maxWaitSignal(0),
    maxWaitAnswer(0),
#ifdef _NETWORK_GAME_
    isAnswerInwriting(0),
#endif // _NETWORK_GAME_
    falstart(true),
    isResignal(false),
    isFalstart(false),
    isQA(false),
    countWrongAnswers(0)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/mainSI.png"));
    setWindowTitle(MSG_MAINWINDOW_TITLE());
    ui->plus1Button->setIcon(QIcon(":/icons/plus.png"));
    ui->plus1Button->setText("");
    ui->plus2Button->setIcon(QIcon(":/icons/plus.png"));
    ui->plus2Button->setText("");
    ui->plus3Button->setIcon(QIcon(":/icons/plus.png"));
    ui->plus3Button->setText("");
    ui->plus4Button->setIcon(QIcon(":/icons/plus.png"));
    ui->plus4Button->setText("");
    ui->minus1Button->setIcon(QIcon(":/icons/minus.png"));
    ui->minus1Button->setText("");
    ui->minus2Button->setIcon(QIcon(":/icons/minus.png"));
    ui->minus2Button->setText("");
    ui->minus3Button->setIcon(QIcon(":/icons/minus.png"));
    ui->minus3Button->setText("");
    ui->minus4Button->setIcon(QIcon(":/icons/minus.png"));
    ui->minus4Button->setText("");
    appealWindowExample = new AppealWindow();
    appealWindowExample->setWindowModality(Qt::WindowModal);
    settingsWindowExample = new settingsWindow();
    settingsWindowExample->setWindowModality(Qt::WindowModal);
#ifdef _NETWORK_GAME_
    networkWindowExample = new serverSettings();
    networkWindowExample->setWindowModality(Qt::WindowModal);
#endif // _NETWORK_GAME_
    current_question = new int[4];
    protocol = new QString[4];
    appealsUsersQuantity = new int[4];
    answerDirection = new int[4];
    setZero(current_question);
    setZero(answerDirection);
    questionsFile.setFileName("");
    plus_minus_buttons.append(ui->plus1Button);
    plus_minus_buttons.append(ui->plus2Button);
    plus_minus_buttons.append(ui->plus3Button);
    plus_minus_buttons.append(ui->plus4Button);
    plus_minus_buttons.append(ui->minus1Button);
    plus_minus_buttons.append(ui->minus2Button);
    plus_minus_buttons.append(ui->minus3Button);
    plus_minus_buttons.append(ui->minus4Button);
    setGraphics();

    QObject::connect(appealWindowExample, SIGNAL(appeal_apply(int, int)), this, SLOT(appeal_apply(int, int)));
    QObject::connect(appealWindowExample, SIGNAL(appeal_reject(int)), this, SLOT(appeal_reject(int)));
    QObject::connect(settingsWindowExample, SIGNAL(settingsIsSet()), this, SLOT(setSettings()));
#ifdef _NETWORK_GAME_
    QObject::connect(networkWindowExample, SIGNAL(settingsIsSet()), this, SLOT(setSettings()));
    QObject::connect(networkWindowExample, SIGNAL(newAnswerSignal(int)), this, SLOT(newAnswer(int)));
    QObject::connect(networkWindowExample, SIGNAL(textAnswerSignal(QString)), this, SLOT(textAnswer(QString)));
    QObject::connect(settingsWindowExample, SIGNAL(startServer()), networkWindowExample, SLOT(show()));
#endif // _NETWORK_GAME_
    QObject::connect(&waitSignalTimer, SIGNAL(timeout()), this, SLOT(signalTimeout()));
}

MainWindow::~MainWindow()
{
    delete appealWindowExample;
    delete settingsWindowExample;
#ifdef _NETWORK_GAME_
    delete networkWindowExample;
#endif
    delete[] answerDirection;
    delete[] appealsUsersQuantity;
    delete[] current_question;
    delete[] protocol;
    delete ui;
}

void MainWindow::on_settingsButton_clicked()
{
    settingsWindowExample->show();
}

void MainWindow::on_plus1Button_clicked()
{
    if (ui->sum1_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum1_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum + change_sum;
        ui->sum1_Browser->setText(QString::number(new_sum));
        ui->sum1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus1Button->setDisabled(true);
        ui->minus1Button->setDisabled(true);
        current_question[0] = 1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 1;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(1, MSG_ANSWER_CORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_minus1Button_clicked()
{
    if (ui->sum1_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum1_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum - change_sum;
        ui->sum1_Browser->setText(QString::number(new_sum));
        ui->sum1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus1Button->setDisabled(true);
        ui->minus1Button->setDisabled(true);
        current_question[0] = -1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 1;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(1, MSG_ANSWER_INCORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
        wrongAnswer();

    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_plus2Button_clicked()
{
    if (ui->sum2_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum2_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum + change_sum;
        ui->sum2_Browser->setText(QString::number(new_sum));
        ui->sum2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus2Button->setDisabled(true);
        ui->minus2Button->setDisabled(true);
        current_question[1] = 1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 2;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(2, MSG_ANSWER_CORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_minus2Button_clicked()
{
    if (ui->sum2_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum2_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum - change_sum;
        ui->sum2_Browser->setText(QString::number(new_sum));
        ui->sum2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus2Button->setDisabled(true);
        ui->minus2Button->setDisabled(true);
        current_question[1] = -1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 2;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(2, MSG_ANSWER_INCORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
        wrongAnswer();
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_plus3Button_clicked()
{
    if (ui->sum3_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum3_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum + change_sum;
        ui->sum3_Browser->setText(QString::number(new_sum));
        ui->sum3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus3Button->setDisabled(true);
        ui->minus3Button->setDisabled(true);
        current_question[2] = 1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 3;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(3, MSG_ANSWER_CORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_minus3Button_clicked()
{
    if (ui->sum3_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum3_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum - change_sum;
        ui->sum3_Browser->setText(QString::number(new_sum));
        ui->sum3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus3Button->setDisabled(true);
        ui->minus3Button->setDisabled(true);
        current_question[2] = -1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 3;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(3, MSG_ANSWER_INCORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
        wrongAnswer();
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_plus4Button_clicked()
{
    if (ui->sum4_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum4_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum + change_sum;
        ui->sum4_Browser->setText(QString::number(new_sum));
        ui->sum4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus4Button->setDisabled(true);
        ui->minus4Button->setDisabled(true);
        current_question[3] = 1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 4;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(4, MSG_ANSWER_CORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_minus4Button_clicked()
{
    if (ui->sum4_Browser->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_PLAYER_NOT_FOUND());
        return;
    }
    else
    {
        int current_sum = ui->sum4_Browser->toPlainText().toInt();
        int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
        int new_sum = current_sum - change_sum;
        ui->sum4_Browser->setText(QString::number(new_sum));
        ui->sum4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        ui->plus4Button->setDisabled(true);
        ui->minus4Button->setDisabled(true);
        current_question[3] = -1;
#ifdef _NETWORK_GAME_
        if (!isNetworkGame)
        {
            answerQuantity++;
            answerDirection[answerQuantity-1] = 4;
        }
#else
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
#endif // _NETWORK_GAME_
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCorrectnessToPlayer(4, MSG_ANSWER_INCORRECT());
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
        wrongAnswer();
    }
#endif // _NETWORK_GAME_
}

void MainWindow::on_startGameButton_clicked()
{
    questionsFile.setFileName(settingsWindowExample->questionsFileName);
    if (questionsFile.fileName().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_QUESTION_FILE_NOT_FOUND());
        return;
    }

    isGamePlaying = true;
    ui->playersBox->setEnabled(true);
    ui->settingsButton->setDisabled(true);
    ui->nextQuestionButton->setEnabled(true);
    ui->finishGameButton->setEnabled(true);

    foreach (QPushButton *button, plus_minus_buttons)
    {
        button->setDisabled(true);
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendPlayersToPlayers(ui->name1_Browser->toPlainText(),
                                                   ui->name2_Browser->toPlainText(),
                                                   ui->name3_Browser->toPlainText(),
                                                   ui->name4_Browser->toPlainText());
    }
#endif // _NETWORK_GAME_

    parseQuestionsFile(&questionsFile);
    current_stage = STAGE_ABSTRACT;
    current_theme_number = 0;
}

void MainWindow::on_nextQuestionButton_clicked()
{
    switch (current_stage)
    {
        case STAGE_ABSTRACT:
            ui->answerBrowser->setText(fullPaket.abstract);
            current_stage = STAGE_THEME;
            break;
        case STAGE_THEME:
            if(current_theme_number < fullPaket.numThemes)
            {
                current_theme_number++;
                currentQuestionNumber = 0;
            }
            else
            {
                return;
            }

            if (current_theme_number > 1)
            {
                appendLog(protocol, current_question);
            }
            ui->numberThemeBrowser->setText(QString::number(current_theme_number));
            ui->numberThemeBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->nameThemeBrowser->setText(fullPaket.dataThemes[current_theme_number-1].title);
            ui->valueQuestionBrowser->clear();
            ui->questionBrowser->clear();
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].comment);
            current_stage = STAGE_QUESTION;
            break;
        case STAGE_QUESTION:
            if (fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].value != 10)
            {
                appendLog(protocol, current_question);
            }
            ui->globalTimerBrowser->clear();
            ui->queue1Browser->clear();
            ui->queue2Browser->clear();
            ui->queue3Browser->clear();
            ui->queue4Browser->clear();
            setZero(answerDirection);
            answerQuantity = 0;
            countWrongAnswers = 0;
            if (!isFalstart)
            {
                falstart = false;
            }
#ifdef _NETWORK_GAME_
            if (isNetworkGame)
            {
                networkWindowExample->sendTimeToPlayers(MSG_TIME_PREFFIX());
                networkWindowExample->sendQuestionToPlayers(current_theme_number,
                                                            fullPaket.dataThemes[current_theme_number-1].title,
                                                            fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].value,
                                                            fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].textQuestion);
            }
#endif // _NETWORK_GAME_
            setZero(current_question);
            ui->appealButton->setDisabled(true);
            ui->startTimerButton->setEnabled(true);
            ui->answerBrowser->clear();
            ui->valueQuestionBrowser->setText(QString::number(fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].value));
            ui->valueQuestionBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->questionBrowser->setText(fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].textQuestion);
            if(isQA)
            {
                ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].answer);
            }
#ifdef _NETWORK_GAME_
            if (!isNetworkGame)
            {
                foreach (QPushButton *button, plus_minus_buttons)
                {
                    button->setEnabled(true);
                }
            }
#else
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setEnabled(true);
            }
#endif // _NETWORK_GAME_
            current_stage = STAGE_ANSWER;
            break;

        case STAGE_ANSWER:
#ifdef _NETWORK_GAME_
            if (isNetworkGame)
            {
                networkWindowExample->sendTimeToPlayers(MSG_BLOCK_PREFFIX());
            }
#endif // _NETWORK_GAME_
            if(!isQA)
            {
                ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].answer);
            }
            ui->appealButton->setEnabled(true);
            ui->startTimerButton->setDisabled(true);
            falstart = true;
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setDisabled(true);
            }
            if (fullPaket.dataThemes[current_theme_number-1].questions[currentQuestionNumber].value != 50)
            {
                currentQuestionNumber++;
                current_stage = STAGE_QUESTION;
            }
            else
            {
                if (current_theme_number == fullPaket.numThemes)
                {
                    current_stage = STAGE_FINISH;
                }
                else
                {
                    current_stage = STAGE_THEME;
                }
            }
            break;
        case STAGE_FINISH:
            ui->numberThemeBrowser->clear();
            ui->nameThemeBrowser->clear();
            ui->valueQuestionBrowser->clear();
            ui->questionBrowser->clear();
            ui->answerBrowser->clear();
            QMessageBox::information(NULL, MSG_INFO(), MSG_THEMES_OVER());
            break;
    }
}

void MainWindow::on_appealButton_clicked()
{
    appealWindowExample->show();
}

void MainWindow::on_finishGameButton_clicked()
{
    if (!isGamePlaying)
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_GAME_NOT_STARTED());
        return;
    }
    else
    {
        isGamePlaying = false;
    }

    delete [] fullPaket.dataThemes;

    QString exportFileName;
    QFileDialog exportDialog;
    exportFileName = exportDialog.getExistingDirectory() + MSG_EXPORT_FILE_NAME();
    exportFile.setFileName(exportFileName);

    if (!exportFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        exportFile.write(protocol[i].toUtf8());
        exportFile.write("\n");
    }
    exportFile.close();

#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->show();
        networkWindowExample->raise();
    }
#endif // _NETWORK_GAME_
    QMessageBox::information(NULL, MSG_INFO(), MSG_GAME_OVER());
    setGraphics();
}

void MainWindow::on_startTimerButton_clicked()
{
    waitSignalTimer.start(maxWaitSignal*1000);
    if (isFalstart)
    {
        falstart = false;
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendTimeToPlayers(MSG_TIME_PREFFIX());
    }
#endif // _NETWORK_GAME_
    ui->globalTimerBrowser->setText(QString::number(waitSignalTimer.remainingTime()/1000)  + " секунд");
    ui->globalTimerBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QTimer::singleShot(1000, this, SLOT(updateGlobalTimer()));
}


void MainWindow::on_exitButton_clicked()
{
    if (isGamePlaying)
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_GAME_IS_PLAYING());
        return;
    }
    this->close();
}

void MainWindow::setGraphics()
{
    ui->name1_Browser->setText(MSG_PLAYER_1());
    ui->name2_Browser->setText(MSG_PLAYER_2());
    ui->name3_Browser->setText(MSG_PLAYER_3());
    ui->name4_Browser->setText(MSG_PLAYER_4());
    ui->sum1_Browser->setText(MSG_0());
    ui->sum2_Browser->setText(MSG_0());
    ui->sum3_Browser->setText(MSG_0());
    ui->sum4_Browser->setText(MSG_0());
    ui->sum1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->sum2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->sum3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->sum4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->name1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->name2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->name3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->name4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->numberThemeBrowser->clear();
    ui->nameThemeBrowser->clear();
    ui->valueQuestionBrowser->clear();
    ui->questionBrowser->clear();
    ui->answerBrowser->clear();
    ui->playersBox->setDisabled(true);
    ui->settingsButton->setEnabled(true);
    ui->nextQuestionButton->setDisabled(true);
    ui->appealButton->setDisabled(true);
    ui->startTimerButton->setDisabled(true);
    ui->finishGameButton->setDisabled(true);
    ui->name1_Browser->setStyleSheet("background-color: red");
    ui->name2_Browser->setStyleSheet("background-color: green");
    ui->name3_Browser->setStyleSheet("background-color: yellow");
    ui->name4_Browser->setStyleSheet("background-color: blue");
#ifndef _NETWORK_GAME_
    ui->queue1Label->setVisible(false);
    ui->queue2Label->setVisible(false);
    ui->queue3Label->setVisible(false);
    ui->queue4Label->setVisible(false);
    ui->queue1Browser->setVisible(false);
    ui->queue2Browser->setVisible(false);
    ui->queue3Browser->setVisible(false);
    ui->queue4Browser->setVisible(false);
    ui->timerP1Label->setVisible(false);
    ui->timerP1Label->setVisible(false);
    ui->timerP2Label->setVisible(false);
    ui->timerP3Label->setVisible(false);
    ui->timerP4Label->setVisible(false);
    ui->timerP1Browser->setVisible(false);
    ui->timerP2Browser->setVisible(false);
    ui->timerP3Browser->setVisible(false);
    ui->timerP4Browser->setVisible(false);
#endif // _NETWORK_GAME_
}

void MainWindow::parseQuestionsFile(QFile *file)
{
    int nThemes=0;
    int iter=0;
    QString readData="";
    if (!file->open(QIODevice::ReadOnly)) //открываем файл для чтения количества тем
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_OPEN_FILE_ERROR());
        return;
    }
    readData = QString::fromUtf8(file->readLine());
    while (!file->atEnd()) //считаем количество тем в пакете
    {
        if (readData.startsWith(MSG_THEME()))
        {
            nThemes++;
        }
        readData = QString::fromUtf8(file->readLine());
    }
    fullPaket.numThemes = nThemes;
    file->close();

    if (fullPaket.numThemes < 1)
    {
        return;
    }

    if (!file->open(QIODevice::ReadOnly)) //открываем файл для чтения пакета
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_OPEN_FILE_ERROR());
        return;
    }

    fullPaket.dataThemes = new theme[fullPaket.numThemes];

    readData = QString::fromUtf8(file->readLine());
    while (!readData.startsWith(MSG_THEME()))
    {
        fullPaket.abstract += readData;
        readData = QString::fromUtf8(file->readLine());
    }

    while (!file->atEnd() && iter < fullPaket.numThemes)
    {
        while (!readData.startsWith(MSG_10())) //пока не 10, читаем заголовок
        {
            if(readData.startsWith(MSG_COMMENT())) //если коммент, то читаем коммент до 10
            {
                while (!readData.startsWith(MSG_10()))
                {
                    fullPaket.dataThemes[iter].comment += readData;
                    readData = QString::fromUtf8(file->readLine());
                }
            }
            else //иначе продолжаем читать заголовок
            {
                fullPaket.dataThemes[iter].title += readData;
                fullPaket.dataThemes[iter].comment += "";
                readData = QString::fromUtf8(file->readLine());
            }
        }

        fullPaket.dataThemes[iter].questions[0].value = 10;
        fullPaket.dataThemes[iter].questions[0].textQuestion += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 10
        {
            fullPaket.dataThemes[iter].questions[0].textQuestion += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[0].answer += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_20())) //пока не 20, читаем ответ 10
        {
            fullPaket.dataThemes[iter].questions[0].answer += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[1].value = 20;
        fullPaket.dataThemes[iter].questions[1].textQuestion += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 20
        {
            fullPaket.dataThemes[iter].questions[1].textQuestion += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[1].answer += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_30())) //пока не 30, читаем ответ 20
        {
            fullPaket.dataThemes[iter].questions[1].answer += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[2].value = 30;
        fullPaket.dataThemes[iter].questions[2].textQuestion += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 30
        {
            fullPaket.dataThemes[iter].questions[2].textQuestion += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[2].answer += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_40())) //пока не 40, читаем ответ 30
        {
            fullPaket.dataThemes[iter].questions[2].answer += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[3].value = 40;
        fullPaket.dataThemes[iter].questions[3].textQuestion += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 40
        {
            fullPaket.dataThemes[iter].questions[3].textQuestion += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[3].answer += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_50())) //пока не 50, читаем ответ 40
        {
            fullPaket.dataThemes[iter].questions[3].answer += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[4].value = 50;
        fullPaket.dataThemes[iter].questions[4].textQuestion += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 50
        {
            fullPaket.dataThemes[iter].questions[4].textQuestion += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].questions[4].answer += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_THEME()) && !file->atEnd()) //пока не новая тема или не конец файла, читаем ответ 50
        {
            fullPaket.dataThemes[iter].questions[4].answer += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        iter++;
    }

    return;
}

void MainWindow::setZero(int *array)
{
    if (array)
    {
        for (unsigned int i=0; i<4; i++)
        {
            array[i]=0;
        }
    }
    else
    {
        return;
    }
}

void MainWindow::appendLog(QString *log, int *question)
{
    if (log && question)
    {
        for (unsigned int i = 0; i<4; i++)
        {
            log[i] += QString::number(question[i]) + ";";
        }
    }
    else
    {
        return;
    }
}

void MainWindow::appeal_apply(int type, int numPlayer)
{
    if (isAppealsLimited && appealsUsersQuantity[numPlayer-1] <= 0)
    {
        QMessageBox::information(NULL, MSG_INFO(), MSG_NO_APPEALS());
    }
    else
    {
        switch (type)
        {
        case 0:
            for (unsigned int i=0; i<4; i++)
            {
                if(answerDirection[i] == numPlayer)
                {
                    for (unsigned int j=i; j<4; j++)
                    {
                        if (answerDirection[j] > 0)
                        {
                            updateDisplay(answerDirection[j], current_question[answerDirection[j] - 1]);
                            current_question[answerDirection[j] - 1]=0;
                        }
                    }
                }
            }
            current_question[numPlayer-1] = 1;
            updateDisplay(numPlayer, -1);
            break;
        case 1:
            for (unsigned int i=0; i<4; i++)
            {
                if(answerDirection[i] == numPlayer)
                {
                    for (unsigned int j=i; j<4; j++)
                    {
                        if (answerDirection[j] > 0)
                        {
                            updateDisplay(answerDirection[j], current_question[answerDirection[j] - 1]);
                            current_question[answerDirection[j] - 1]=0;
                        }
                    }
                }
            }
            current_question[numPlayer-1] = -1;
            updateDisplay(numPlayer, 1);
            break;
        case 2:
            for (unsigned int i=0; i<4; i++)
            {
                updateDisplay(i+1, current_question[i]);
                current_question[i] = 0;
            }
            break;
        }
        QMessageBox::information(NULL, MSG_INFO(), MSG_APPEAL_ACCEPTED());
    }
}

void MainWindow::appeal_reject(int numPlayer)
{
    if (isAppealsLimited)
    {
        if (appealsUsersQuantity[numPlayer-1] > 0)
        {
            appealsUsersQuantity[numPlayer-1]--;
            QMessageBox::information(NULL, MSG_INFO(), MSG_APPEAL_REJECTED());
        }
        else
        {
            QMessageBox::information(NULL, MSG_INFO(), MSG_NO_APPEALS());
        }
    }
    else
    {
        QMessageBox::information(NULL, MSG_INFO(), MSG_APPEAL_REJECTED());
    }
}

void MainWindow::setSettings()
{
#ifdef _NETWORK_GAME_
    isNetworkGame = settingsWindowExample->isNetworkGame;
    if (!isNetworkGame)
    {
        ui->name1_Browser->setText(settingsWindowExample->player1_name);
        ui->name2_Browser->setText(settingsWindowExample->player2_name);
        ui->name3_Browser->setText(settingsWindowExample->player3_name);
        ui->name4_Browser->setText(settingsWindowExample->player4_name);
    }
    else
    {
        if (!networkWindowExample->playersList[0].name.isEmpty())
        {
            ui->name1_Browser->setText(networkWindowExample->playersList[0].name);
        }
        else
        {
            ui->name1_Browser->clear();
        }

        if (!networkWindowExample->playersList[1].name.isEmpty())
        {
            ui->name2_Browser->setText(networkWindowExample->playersList[1].name);
        }
        else
        {
            ui->name2_Browser->clear();
        }

        if (!networkWindowExample->playersList[2].name.isEmpty())
        {
            ui->name3_Browser->setText(networkWindowExample->playersList[2].name);
        }
        else
        {
            ui->name3_Browser->clear();
        }

        if (!networkWindowExample->playersList[3].name.isEmpty())
        {
            ui->name4_Browser->setText(networkWindowExample->playersList[3].name);
        }
        else
        {
            ui->name4_Browser->clear();
        }

        isAnswerInwriting = networkWindowExample->isAnswerInwritting;
    }
#else
    ui->name2_Browser->setText(settingsWindowExample->player2_name);
    ui->name3_Browser->setText(settingsWindowExample->player3_name);
    ui->name4_Browser->setText(settingsWindowExample->player4_name);
#endif // _NETWORK_GAME_

    ui->name1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    if (ui->name1_Browser->toPlainText().isEmpty())
    {
        ui->sum1_Browser->clear();
        ui->player1Box->setDisabled(true);
    }
    else
    {
        playersQuantity++;
    }

    ui->name2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    if (ui->name2_Browser->toPlainText().isEmpty())
    {
        ui->sum2_Browser->clear();
        ui->player2Box->setDisabled(true);
    }
    else
    {
        playersQuantity++;
    }

    ui->name3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    if (ui->name3_Browser->toPlainText().isEmpty())
    {
        ui->sum3_Browser->clear();
        ui->player3Box->setDisabled(true);
    }
    else
    {
        playersQuantity++;
    }

    ui->name4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    if (ui->name4_Browser->toPlainText().isEmpty())
    {
        ui->sum4_Browser->clear();
        ui->player4Box->setDisabled(true);
    }
    else
    {
        playersQuantity++;
    }

    isAppealsLimited = settingsWindowExample->isAppealsLimited;
    for (unsigned int i=0; i<4; i++)
    {
        if (isAppealsLimited)
        {
            appealsUsersQuantity[i] = settingsWindowExample->appealsQuantity;
        }
        else
        {
            appealsUsersQuantity[i] = 0;
        }
    }

    maxWaitSignal = settingsWindowExample->waitingSignal;
    maxWaitAnswer = settingsWindowExample->waitingAnswer;
    isResignal = settingsWindowExample->isResignal;
    isFalstart = settingsWindowExample->isFalstart;
    isQA = settingsWindowExample->isQA;
}

void MainWindow::updateDisplay(int usernum, int old_value)
{

    int current_sum = 0;
    switch (usernum)
    {
        case 1:
            current_sum = ui->sum1_Browser->toPlainText().toInt();
            break;
        case 2:
            current_sum = ui->sum2_Browser->toPlainText().toInt();
            break;
        case 3:
            current_sum = ui->sum3_Browser->toPlainText().toInt();
            break;
        case 4:
            current_sum = ui->sum4_Browser->toPlainText().toInt();
            break;
    }
    int change_sum = ui->valueQuestionBrowser->toPlainText().toInt();
    int new_sum = 0;
    switch (old_value)
    {
    case -1:
        new_sum = current_sum + change_sum;
        break;
    case 0:
        new_sum = current_sum;
        break;
    case 1:
        new_sum = current_sum - change_sum;
        break;
    }
    switch (usernum)
    {
        case 1:
            ui->sum1_Browser->setText(QString::number(new_sum));
            ui->sum1_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            break;
        case 2:
            ui->sum2_Browser->setText(QString::number(new_sum));
            ui->sum2_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            break;
        case 3:
            ui->sum3_Browser->setText(QString::number(new_sum));
            ui->sum3_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            break;
        case 4:
            ui->sum4_Browser->setText(QString::number(new_sum));
            ui->sum4_Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            break;
    }
#ifdef _NETWORK_GAME_
    if (isNetworkGame)
    {
        networkWindowExample->sendCurrentResultsToPlayers(ui->sum1_Browser->toPlainText().toInt(),
                                                          ui->sum2_Browser->toPlainText().toInt(),
                                                          ui->sum3_Browser->toPlainText().toInt(),
                                                          ui->sum4_Browser->toPlainText().toInt());
    }
#endif // _NETWORK_GAME_
}

void MainWindow::updateGlobalTimer()
{
    int secondsToTimeout = waitSignalTimer.remainingTime();
    if(secondsToTimeout > 0)
    {
        ui->globalTimerBrowser->setText(QString::number(secondsToTimeout/1000) + " секунд");
        ui->globalTimerBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        QTimer::singleShot(1000, this, SLOT(updateGlobalTimer()));
    }
}

void MainWindow::signalTimeout()
{
    waitSignalTimer.stop();
#ifdef _NETWORK_GAME_
    if(isNetworkGame)
    {
        networkWindowExample->sendTimeoutToPlayers();
        on_nextQuestionButton_clicked();
    }
#endif // _NETWORK_GAME_
    ui->globalTimerBrowser->clear();
}

#ifdef _NETWORK_GAME_
void MainWindow::newAnswer(int playerNumber)
{
    for (unsigned i=0; i<4; i++)
    {
        if(answerDirection[i] == playerNumber) // если ты уже отвечал, то больше отвечать не можешь
        {
            networkWindowExample->sendQueueToPlayer(playerNumber, 0);
            return;
        }
    }
    waitSignalTimer.stop();
    if(falstart)
    {
        networkWindowExample->sendCorrectnessToPlayer(playerNumber, MSG_FALSTART());
    }
    else
    {
        answerQuantity++;
        answerDirection[answerQuantity-1] = playerNumber;
        if (answerQuantity <= 4)
        {
            networkWindowExample->sendQueueToPlayer(playerNumber, answerQuantity);
            switch (playerNumber)
            {
                case 0:
                    return;
                    break;
                case 1:
                    ui->queue1Browser->setText(QString::number(answerQuantity));
                    ui->queue1Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                    break;
                case 2:
                    ui->queue2Browser->setText(QString::number(answerQuantity));
                    ui->queue2Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                    break;
                case 3:
                    ui->queue3Browser->setText(QString::number(answerQuantity));
                    ui->queue2Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                    break;
                case 4:
                    ui->queue4Browser->setText(QString::number(answerQuantity));
                    ui->queue4Browser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                    break;
            }
        }
        else
        {
            return;
        }
    }
    if (answerQuantity == 1)
    {
        switch (playerNumber)
        {
            case 0:
                return;
                break;
            case 1:
                ui->player1Box->setEnabled(true);
                ui->plus1Button->setEnabled(true);
                ui->minus1Button->setEnabled(true);
                break;
            case 2:
                ui->player2Box->setEnabled(true);
                ui->plus2Button->setEnabled(true);
                ui->minus2Button->setEnabled(true);
                break;
            case 3:
                ui->player3Box->setEnabled(true);
                ui->plus3Button->setEnabled(true);
                ui->minus3Button->setEnabled(true);
                break;
            case 4:
                ui->player4Box->setEnabled(true);
                ui->plus4Button->setEnabled(true);
                ui->minus4Button->setEnabled(true);
                break;
        }
    }
}
#endif // _NETWORK_GAME_

#ifdef _NETWORK_GAME_
void MainWindow::wrongAnswer()
{
    if (answerQuantity < 4)
    {
        countWrongAnswers++;
        if (isResignal)
        {
            networkWindowExample->sendTimeToPlayers(MSG_TIME_PREFFIX());
            answerQuantity = 0;
            if(isFalstart) // перезапускаем таймер, если игра с переотбивками и с фальстартами. Без ф/с и п/о всё вручную
            {
                waitSignalTimer.start(maxWaitSignal*1000);
            }
        }
        else
        {
            switch (answerDirection[countWrongAnswers]) //смотрим следующего в очереди на ответ
            {
                case 0: // никого нет. Ждём отбивок дальше
                    waitSignalTimer.start(maxWaitSignal*1000);
                    break;
                case 1:
                    networkWindowExample->sendQueueToPlayer(1, 1);
                    ui->plus1Button->setEnabled(true);
                    ui->minus1Button->setEnabled(true);
                    break;
                case 2:
                    networkWindowExample->sendQueueToPlayer(2, 1);
                    ui->plus2Button->setEnabled(true);
                    ui->minus2Button->setEnabled(true);
                    break;
                case 3:
                    networkWindowExample->sendQueueToPlayer(3, 1);
                    ui->plus3Button->setEnabled(true);
                    ui->minus3Button->setEnabled(true);
                    break;
                case 4:
                    networkWindowExample->sendQueueToPlayer(4, 1);
                    ui->plus4Button->setEnabled(true);
                    ui->minus4Button->setEnabled(true);
                    break;
            }

            if (answerDirection[answerQuantity] != 0)
            {
                networkWindowExample->sendQueueToPlayer(1, 1);
                ui->player1Box->setEnabled(true);
            }
        }
    }
    else
    {
        return;
    }
}
#endif // _NETWORK_GAME_

#ifdef _NETWORK_GAME_
void MainWindow::textAnswer(QString answer)
{
    if (isAnswerInwriting)
    {
        QMessageBox::information(NULL, MSG_INFO(), answer);
    }
}
#endif // _NETWORK_GAME_
