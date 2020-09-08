#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appealwindow.h"
#include "settingswindow.h"
#ifdef _NETWORK_GAME_
#include "serversettings.h"
#endif // _NETWORK_GAME_
#include <QFile>
#include <QList>
#include <QPushButton>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();
    void on_settingsButton_clicked();
    void on_appealButton_clicked();
    void on_startGameButton_clicked();
    void on_finishGameButton_clicked();
    void on_nextQuestionButton_clicked();
    void on_plus1Button_clicked();
    void on_minus1Button_clicked();
    void on_plus2Button_clicked();
    void on_minus2Button_clicked();
    void on_plus3Button_clicked();
    void on_minus3Button_clicked();
    void on_plus4Button_clicked();
    void on_minus4Button_clicked();
    void on_startTimerButton_clicked();
    void appeal_apply(int type, int numPlayer);
    void appeal_reject(int numPlayer);
    void setSettings();
    void updateGlobalTimer();
    void signalTimeout();
#ifdef _NETWORK_GAME_
    void newAnswer(int playerNumber);
    void textAnswer(QString answer);
#endif // _NETWORK_GAME_

private:
    Ui::MainWindow *ui;
    AppealWindow *appealWindowExample;
    settingsWindow *settingsWindowExample;
#ifdef _NETWORK_GAME_
    serverSettings *networkWindowExample;
#endif // _NETWORK_GAME_
    QList<QPushButton*> plus_minus_buttons;

    struct question
    {
        int value;
        QString textQuestion;
        QString answer;
    };

    struct theme
    {
        QString title;
        QString comment;
        question questions[5];
    };

    struct paket
    {
        QString abstract;
        int numThemes;
        struct theme *dataThemes;
    };

    int *current_question;
    QString *protocol;

    enum stage
    {
        STAGE_ABSTRACT = 0,
        STAGE_THEME,
        STAGE_QUESTION,
        STAGE_ANSWER,
        STAGE_FINISH
    };

    QFile questionsFile;
    QFile exportFile;
    paket fullPaket;
#ifdef _NETWORK_GAME_
    bool isNetworkGame;
#endif // _NETWORK_GAME_
    bool isGamePlaying;
    stage current_stage;
    int current_theme_number;
    int currentQuestionNumber;
    bool isAppealsLimited;
    unsigned int playersQuantity;
    int *appealsUsersQuantity;
    int *answerDirection;
    int answerQuantity;
    QTimer waitSignalTimer;
    QTimer waitAnswerTimer;
    int maxWaitSignal;
    int maxWaitAnswer;
#ifdef _NETWORK_GAME_
    int isAnswerInwriting;
#endif // _NETWORK_GAME_
    bool falstart; // произошёл ли фальстарт
    bool isResignal;
    bool isFalstart; // игра с фальстартами или без
    bool isQA; // показывать вопросы и ответы одновременно
    int countWrongAnswers;

    void setGraphics();
    void parseQuestionsFile(QFile *file);
    void setZero(int *array);
    void appendLog(QString *log, int *question);
    void updateDisplay(int usernum, int old_value);
#ifdef _NETWORK_GAME_
    void wrongAnswer();
#endif // _NETWORK_GAME_
};
#endif // MAINWINDOW_H
