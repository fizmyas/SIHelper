#include "settingswindow.h"
#include "strings/strings_settingswindow.h"
#include "ui_settingswindow.h"
#include <QFileDialog>
#include <QMessageBox>

using namespace settingswindowStrings;

settingsWindow::settingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settingsWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/settings.png"));
    setWindowTitle(MSG_SETTINGS_TITLE());
    questionsFileName="";
    settingsFieldsList.append(ui->fileEdit);
    settingsFieldsList.append(ui->player1_Edit);
    settingsFieldsList.append(ui->player2_Edit);
    settingsFieldsList.append(ui->player3_Edit);
    settingsFieldsList.append(ui->player4_Edit);
    ui->appealQuantityBox->setDisabled(true);
    QObject::connect(ui->appealLimitedBox, SIGNAL(toggled(bool)), ui->appealQuantityBox, SLOT(setEnabled(bool)));
    appealsQuantity=0;
    isAppealsLimited=false;
}

settingsWindow::~settingsWindow()
{
    delete ui;
}

void settingsWindow::on_applyButton_clicked()
{
    if (ui->fileEdit->toPlainText().isEmpty())
    {
        QMessageBox::critical(NULL, MSG_ERROR(), MSG_QUESTION_FILE_NOT_FOUND());
        return;
    }
    player1_name = ui->player1_Edit->toPlainText();
    player2_name = ui->player2_Edit->toPlainText();
    player3_name = ui->player3_Edit->toPlainText();
    player4_name = ui->player4_Edit->toPlainText();
    if (ui->appealLimitedBox->isChecked())
    {
        isAppealsLimited=true;
        appealsQuantity = ui->appealQuantityBox->value();
    }
    else
    {
        isAppealsLimited=false;
    }
    emit settingsIsSet();
    foreach (QTextEdit *field, settingsFieldsList)
    {
        field->clear();
    }
    close();
}

void settingsWindow::on_cancelButton_clicked()
{
    close();
}

void settingsWindow::on_chooseFileButton_clicked()
{
    QFileDialog dialog;
    ui->fileEdit->setText(dialog.getOpenFileName());
    questionsFileName = ui->fileEdit->toPlainText();
}
