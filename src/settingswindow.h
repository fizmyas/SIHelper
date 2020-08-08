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
    bool isAppealsLimited;
    int appealsQuantity;

signals:
    void settingsIsSet();

private slots:
    void on_applyButton_clicked();

    void on_cancelButton_clicked();

    void on_chooseFileButton_clicked();

private:
    Ui::settingsWindow *ui;
    QList<QTextEdit*> settingsFieldsList;
};

#endif // SETTINGSWINDOW_H
