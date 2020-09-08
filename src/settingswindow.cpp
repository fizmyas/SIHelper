#include "settingswindow.h"
#include "strings/strings_settingswindow.h"
#include "ui_settingswindow.h"
#include <QFileDialog>
#include <QMessageBox>

using namespace settingswindowStrings;

settingsWindow::settingsWindow(QWidget *parent) :
    QWidget(parent),
    questionsFileName(""),
#ifdef _NETWORK_GAME_
    isNetworkGame(0),
#endif // _NETWORK_GAME_
    isAppealsLimited(0),
    appealsQuantity(0),
    shootingThemesQuantity(0),
    oShootingThemesQuantity(0),
    waitingSignal(0),
    waitingAnswer(0),
    isResignal(false),
    isFalstart(false),
    isQA(false),
    ui(new Ui::settingsWindow)

{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icons/settings.png"));
    setWindowTitle(MSG_SETTINGS_TITLE());
    settingsFieldsList.append(ui->fileEdit);
    settingsFieldsList.append(ui->player1_Edit);
    settingsFieldsList.append(ui->player2_Edit);
    settingsFieldsList.append(ui->player3_Edit);
    settingsFieldsList.append(ui->player4_Edit);
    ui->appealQuantityBox->setDisabled(true);
    ui->shootingSpinBox->setDisabled(true);
    ui->oShootingSpinBox->setDisabled(true);
    ui->usualGameButton->setChecked(true);
#ifndef _NETWORK_GAME_
    ui->networkGameButton->setVisible(false);
    ui->resignalBox->setVisible(false);
    ui->falstartBox->setVisible(false);
    ui->waitingAnswerBox->setVisible(false);
    ui->waitingAnswerLabel->setVisible(false);
    ui->second2Label->setVisible(false);
#endif // _NETWORK_GAME_
    QObject::connect(ui->appealLimitedBox, SIGNAL(toggled(bool)), ui->appealQuantityBox, SLOT(setEnabled(bool)));
    QObject::connect(ui->shootingCheckBox, SIGNAL(toggled(bool)), ui->shootingSpinBox, SLOT(setEnabled(bool)));
    QObject::connect(ui->oShootingCheckBox, SIGNAL(toggled(bool)), ui->oShootingSpinBox, SLOT(setEnabled(bool)));
    QObject::connect(ui->usualGameButton, SIGNAL(toggled(bool)), ui->playersBox, SLOT(setEnabled(bool)));

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

#ifdef _NETWORK_GAME_
    isNetworkGame = ui->networkGameButton->isChecked();
#endif // _NETWORK_GAME_
    if (ui->shootingCheckBox->isChecked())
    {
        shootingThemesQuantity = ui->shootingSpinBox->value();
    }

    if (ui->oShootingCheckBox->isChecked())
    {
        oShootingThemesQuantity = ui->oShootingSpinBox->value();
    }

    waitingSignal = ui->waitingSignalBox->value();
    waitingAnswer = ui->waitingAnswerBox->value();
    isResignal = ui->resignalBox->isChecked();
    isFalstart = ui->falstartBox->isChecked();
    isQA = ui->qaBox->isChecked();

    foreach (QTextEdit *field, settingsFieldsList)
    {
        field->clear();
    }

#ifdef _NETWORK_GAME_
    if (!isNetworkGame)
    {
        emit settingsIsSet();
    }
    else
    {
        emit startServer();
    }
#else
    emit settingsIsSet();
#endif // _NETWORK_GAME_


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
