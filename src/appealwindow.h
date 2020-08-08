#ifndef APPEALWINDOW_H
#define APPEALWINDOW_H

#include <QWidget>

namespace Ui {
class AppealWindow;
}

class AppealWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AppealWindow(QWidget *parent = nullptr);
    ~AppealWindow();

signals:
    void appeal_apply(int type, int numPlayer);
    void appeal_reject(int numPlayer);

private slots:
    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AppealWindow *ui;

    enum appealType
    {
        APPEAL_ACCEPT_ANSWER = 0,
        APPEAL_REJECT_QUESTION
    };
};

#endif // APPEALWINDOW_H
