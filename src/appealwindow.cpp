#include "appealwindow.h"
#include "strings/strings_appealwindow.h"
#include "ui_appealwindow.h"

using namespace appealwindowStrings;

AppealWindow::AppealWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppealWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/appeals.png"));
    setWindowTitle(MSG_APPEALWINDOW_TITLE());
}

AppealWindow::~AppealWindow()
{
    delete ui;
}

void AppealWindow::on_applyButton_clicked()
{
    if (ui->approveButton->isChecked())
    {
        emit appeal_apply(APPEAL_ACCEPT_ANSWER, ui->appealerNumberSpinBox->value());
    }
    else
    {
        emit appeal_apply(APPEAL_REJECT_QUESTION, ui->appealerNumberSpinBox->value());
    }
    close();
}

void AppealWindow::on_cancelButton_clicked()
{
    emit appeal_reject(ui->appealerNumberSpinBox->value());
    close();
}
