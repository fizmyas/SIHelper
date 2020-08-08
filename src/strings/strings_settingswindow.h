#ifndef STRINGS_SETTINGSWINDOW_H
#define STRINGS_SETTINGSWINDOW_H

#include <QObject>

namespace settingswindowStrings
{
    QString MSG_SETTINGS_TITLE()
    {
        return QString::fromUtf8("Настройки");
    }
    QString MSG_ERROR()
    {
        return QString::fromUtf8("Ошибка");
    }

    QString MSG_QUESTION_FILE_NOT_FOUND()
    {
        return QString::fromUtf8("Пакет не задан");
    }
}
#endif // STRINGS_SETTINGSWINDOW_H
