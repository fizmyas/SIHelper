#ifndef STRINGS_MAINWINDOW_H
#define STRINGS_MAINWINDOW_H

#include <QObject>

namespace mainwindowStrings
{
    QString MSG_MAINWINDOW_TITLE()
    {
        return QString::fromUtf8("Своя игра. Помощник ведущего");
    }

    QString MSG_INFO()
    {
        return QString::fromUtf8("Информация");
    }

    QString MSG_ERROR()
    {
        return QString::fromUtf8("Ошибка");
    }

    QString MSG_QUESTION_FILE_NOT_FOUND()
    {
        return QString::fromUtf8("Пакет не задан. Выберите файл в Настройках");
    }

    QString MSG_GAME_IS_PLAYING()
    {
        return QString::fromUtf8("Идёт игра!\nЗавершите игру прежде чем выйти");
    }

    QString MSG_EXPORT_FILE_NAME()
    {
        return QString::fromUtf8("/Протокол.csv");
    }

    QString MSG_GAME_OVER()
    {
        return QString::fromUtf8("Игра успешно завершена!");
    }

    QString MSG_GAME_NOT_STARTED()
    {
        return QString::fromUtf8("Игра не начиналась!");
    }

    QString MSG_PLAYER_NOT_FOUND()
    {
        return QString::fromUtf8("Этот игрок не участвует в игре");
    }

    QString MSG_THEMES_OVER()
    {
        return QString::fromUtf8("Все темы сыграны!\nЗавершите игру");
    }

    QString MSG_OPEN_FILE_ERROR()
    {
        return QString::fromUtf8("Невозможно открыть файл");
    }

    QString MSG_THEME()
    {
        return QString::fromUtf8("Тема");
    }

    QString MSG_COMMENT()
    {
        return QString::fromUtf8("Комментарий");
    }

    QString MSG_10()
    {
        return QString::fromUtf8("10");
    }

    QString MSG_20()
    {
        return QString::fromUtf8("20");
    }

    QString MSG_30()
    {
        return QString::fromUtf8("30");
    }

    QString MSG_40()
    {
        return QString::fromUtf8("40");
    }

    QString MSG_50()
    {
        return QString::fromUtf8("50");
    }

    QString MSG_ANSWER()
    {
        return QString::fromUtf8("Ответ");
    }

    QString MSG_APPEAL_ACCEPTED()
    {
        return QString::fromUtf8("Апелляция принята");
    }

    QString MSG_APPEAL_REJECTED()
    {
        return QString::fromUtf8("Апелляция отклонена");
    }

    QString MSG_NO_APPEALS()
    {
        return QString::fromUtf8("У игрока больше не осталось апелляций!");
    }

    QString MSG_PLAYER_1()
    {
        return QString::fromUtf8("Игрок 1");
    }

    QString MSG_PLAYER_2()
    {
        return QString::fromUtf8("Игрок 2");
    }

    QString MSG_PLAYER_3()
    {
        return QString::fromUtf8("Игрок 3");
    }

    QString MSG_PLAYER_4()
    {
        return QString::fromUtf8("Игрок 4");
    }

    QString MSG_0()
    {
        return QString::fromUtf8("0");
    }

    QString MSG_ANSWER_CORRECT()
    {
        return QString::fromUtf8("Верно!");
    }

    QString MSG_ANSWER_INCORRECT()
    {
        return QString::fromUtf8("Неверно!");
    }

    QString MSG_FALSTART()
    {
        return QString::fromUtf8("Фальстарт!");
    }

    QString MSG_TIME_PREFFIX()
    {
        return QString::fromUtf8("Время!");
    }

    QString MSG_BLOCK_PREFFIX()
    {
        return QString::fromUtf8("Block:#");
    }
}

#endif // STRINGS_MAINWINDOW_H
