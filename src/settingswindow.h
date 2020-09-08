#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QList>
#include <QTextEdit>

namespace Ui {
class settingsWindow;
}

class settingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit settingsWindow(QWidget *parent = nullptr);
    ~settingsWindow();
    QString questionsFileName;
    QString player1_name;
    QString player2_name;
    QString player3_name;
    QString player4_name;
#ifdef _NETWORK_GAME_
    bool isNetworkGame;
#endif // _NETWORK_GAME_
    bool isAppealsLimited;
    int appealsQuantity;
    int shootingThemesQuantity;
    int oShootingThemesQuantity;
    int waitingSignal;
    int waitingAnswer;
    bool isResignal;
    bool isFalstart;
    bool isQA;

signals:
    void settingsIsSet();
    void startServer();

private slots:
    void on_applyButton_clicked();

    void on_cancelButton_clicked();

    void on_chooseFileButton_clicked();

private:
    Ui::settingsWindow *ui;
    QList<QTextEdit*> settingsFieldsList;
};

#endif // SETTINGSWINDOW_H
