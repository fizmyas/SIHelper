#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appealwindow.h"
#include "settingswindow.h"
#include <QFile>
#include <QList>
#include <QPushButton>

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

    void appeal_apply(int type, int numPlayer);

    void appeal_reject(int numPlayer);

    void setSettings();

private:
    Ui::MainWindow *ui;
    AppealWindow *appealWindowExample;
    settingsWindow *settingsWindowExample;

    QList<QPushButton*> plus_minus_buttons;

    struct theme
    {
        QString title;
        QString comment;
        QString Q10;
        QString Q20;
        QString Q30;
        QString Q40;
        QString Q50;
        QString A10;
        QString A20;
        QString A30;
        QString A40;
        QString A50;
    };

    struct paket
    {
        QString abstract;
        int numThemes;
        struct theme *dataThemes;
    };

    int *current_question;
    QString *protocol;
    unsigned int playersQuantity;

    enum stage
    {
        STAGE_BEGIN = 0,
        STAGE_ABSTRACT,
        STAGE_THEME,
        STAGE_Q10,
        STAGE_A10,
        STAGE_Q20,
        STAGE_A20,
        STAGE_Q30,
        STAGE_A30,
        STAGE_Q40,
        STAGE_A40,
        STAGE_Q50,
        STAGE_A50,
        STAGE_FINISH
    };

    QFile questionsFile;
    QFile exportFile;
    paket fullPaket;
    bool isGamePlaying;
    stage current_stage;
    int current_theme_number;
    bool isAppealsLimited;
    int *appealsUsersQuantity;
    int *answerDirection;
    int answerQuantity;

    void setGraphics();
    void parseQuestionsFile(QFile *file);
    void setZero(int *array);
    void appendLog(QString *log, int *question);
    void updateDisplay(int usernum, int old_value);
};
#endif // MAINWINDOW_H
