#include "mainwindow.h"
#include "strings/strings_mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

using namespace mainwindowStrings;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
    current_question = new int[4];
    protocol = new QString[4];
    appealsUsersQuantity = new int[4];
    answerDirection = new int[4];
    isAppealsLimited = false;
    setZero(current_question);
    setZero(answerDirection);
    questionsFile.setFileName("");
    isGamePlaying = false;
    playersQuantity = 0;
    answerQuantity = 0;
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
}

MainWindow::~MainWindow()
{
    delete appealWindowExample;
    delete settingsWindowExample;
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 1;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 2;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 2;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 3;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 3;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 4;
    }
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
        answerQuantity++;
        answerDirection[answerQuantity-1] = 4;
    }
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

    parseQuestionsFile(&questionsFile);
    current_stage = STAGE_BEGIN;
    current_theme_number = 0;
}

void MainWindow::on_nextQuestionButton_clicked()
{
    switch (current_stage)
    {
        case STAGE_BEGIN:
            ui->answerBrowser->setText(fullPaket.abstract);
            current_stage = STAGE_ABSTRACT;
            break;
        case STAGE_ABSTRACT:
            current_stage = STAGE_THEME;
            if(current_theme_number < fullPaket.numThemes)
            {
                current_theme_number++;
            }
            else
            {
                return;
            }
            ui->numberThemeBrowser->setText(QString::number(current_theme_number));
            ui->numberThemeBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->nameThemeBrowser->setText(fullPaket.dataThemes[current_theme_number-1].title);
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].comment);
            break;
        case STAGE_THEME:
            current_stage = STAGE_Q10;
            setZero(current_question);
            answerQuantity = 0;
            ui->answerBrowser->clear();
            ui->valueQuestionBrowser->setText(MSG_10());
            ui->valueQuestionBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->questionBrowser->setText(fullPaket.dataThemes[current_theme_number-1].Q10);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setEnabled(true);
            }
            break;
        case STAGE_Q10:
            current_stage = STAGE_A10;
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].A10);
            ui->appealButton->setEnabled(true);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setDisabled(true);
            }
            break;
        case STAGE_A10:
            current_stage = STAGE_Q20;
            ui->appealButton->setDisabled(true);
            appendLog(protocol, current_question);
            setZero(current_question);
            answerQuantity = 0;
            ui->answerBrowser->clear();
            ui->valueQuestionBrowser->setText(MSG_20());
            ui->valueQuestionBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->questionBrowser->setText(fullPaket.dataThemes[current_theme_number-1].Q20);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setEnabled(true);
            }
            break;
        case STAGE_Q20:
            current_stage = STAGE_A20;
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].A20);
            ui->appealButton->setEnabled(true);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setDisabled(true);
            }
            break;
        case STAGE_A20:
            current_stage = STAGE_Q30;
            ui->appealButton->setDisabled(true);
            appendLog(protocol, current_question);
            setZero(current_question);
            answerQuantity = 0;
            ui->answerBrowser->clear();
            ui->valueQuestionBrowser->setText(MSG_30());
            ui->valueQuestionBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->questionBrowser->setText(fullPaket.dataThemes[current_theme_number-1].Q30);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setEnabled(true);
            }
            break;
        case STAGE_Q30:
            current_stage = STAGE_A30;
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].A30);
            ui->appealButton->setEnabled(true);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setDisabled(true);
            }
            break;
        case STAGE_A30:
            current_stage = STAGE_Q40;
            ui->appealButton->setDisabled(true);
            appendLog(protocol, current_question);
            setZero(current_question);
            answerQuantity = 0;
            ui->answerBrowser->clear();
            ui->valueQuestionBrowser->setText(MSG_40());
            ui->valueQuestionBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->questionBrowser->setText(fullPaket.dataThemes[current_theme_number-1].Q40);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setEnabled(true);
            }
            break;
        case STAGE_Q40:
            current_stage = STAGE_A40;
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].A40);
            ui->appealButton->setEnabled(true);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setDisabled(true);
            }
            break;
        case STAGE_A40:
            current_stage = STAGE_Q50;
            ui->appealButton->setDisabled(true);
            appendLog(protocol, current_question);
            setZero(current_question);
            answerQuantity = 0;
            ui->answerBrowser->clear();
            ui->valueQuestionBrowser->setText(MSG_50());
            ui->valueQuestionBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
            ui->questionBrowser->setText(fullPaket.dataThemes[current_theme_number-1].Q50);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setEnabled(true);
            }
            break;
        case STAGE_Q50:
            current_stage = STAGE_A50;
            ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].A50);
            ui->appealButton->setEnabled(true);
            foreach (QPushButton *button, plus_minus_buttons)
            {
                button->setDisabled(true);
            }
            break;
        case STAGE_A50:
            ui->appealButton->setDisabled(true);
            appendLog(protocol, current_question);
            if (current_theme_number == fullPaket.numThemes)
            {
                current_stage = STAGE_FINISH;
                ui->numberThemeBrowser->clear();
                ui->nameThemeBrowser->clear();
                ui->valueQuestionBrowser->clear();
                ui->questionBrowser->clear();
                ui->answerBrowser->clear();
                QMessageBox::information(NULL, MSG_INFO(), MSG_THEMES_OVER());
            }
            else
            {
                current_stage = STAGE_THEME;
                ui->valueQuestionBrowser->clear();
                ui->questionBrowser->clear();
                if(current_theme_number < fullPaket.numThemes)
                {
                    current_theme_number++;
                }
                else
                {
                    return;
                }
                ui->numberThemeBrowser->setText(QString::number(current_theme_number));
                ui->numberThemeBrowser->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
                ui->nameThemeBrowser->setText(fullPaket.dataThemes[current_theme_number-1].title);
                ui->answerBrowser->setText(fullPaket.dataThemes[current_theme_number-1].comment);
            }
            break;
        case STAGE_FINISH:
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
    QMessageBox::information(NULL, MSG_INFO(), MSG_GAME_OVER());
    setGraphics();
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
    ui->finishGameButton->setDisabled(true);
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

        fullPaket.dataThemes[iter].Q10 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 10
        {
            fullPaket.dataThemes[iter].Q10 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].A10 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_20())) //пока не 20, читаем ответ 10
        {
            fullPaket.dataThemes[iter].A10 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].Q20 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 20
        {
            fullPaket.dataThemes[iter].Q20 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].A20 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_30())) //пока не 30, читаем ответ 20
        {
            fullPaket.dataThemes[iter].A20 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].Q30 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 30
        {
            fullPaket.dataThemes[iter].Q30 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].A30 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_40())) //пока не 40, читаем ответ 30
        {
            fullPaket.dataThemes[iter].A30 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].Q40 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 40
        {
            fullPaket.dataThemes[iter].Q40 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].A40 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_50())) //пока не 50, читаем ответ 40
        {
            fullPaket.dataThemes[iter].A40 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].Q50 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_ANSWER())) //пока не ответ, читаем 50
        {
            fullPaket.dataThemes[iter].Q50 += readData;
            readData = QString::fromUtf8(file->readLine());
        }

        fullPaket.dataThemes[iter].A50 += readData;
        readData = QString::fromUtf8(file->readLine());
        while (!readData.startsWith(MSG_THEME()) && !file->atEnd()) //пока не новая тема или не конец файла, читаем ответ 50
        {
            fullPaket.dataThemes[iter].A50 += readData;
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
    ui->name1_Browser->setText(settingsWindowExample->player1_name);
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

    ui->name2_Browser->setText(settingsWindowExample->player2_name);
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

    ui->name3_Browser->setText(settingsWindowExample->player3_name);
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

    ui->name4_Browser->setText(settingsWindowExample->player4_name);
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
}
