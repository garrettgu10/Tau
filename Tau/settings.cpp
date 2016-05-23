#include "settings.h"
#include <constants.h>

Settings::Settings()
{
    saver = new QSettings();
}

void Settings::load()
{
    refreshInterval = saver->value("refreshInterval",defaultRefreshInterval).toInt();
    winningScore = saver->value("winningScore",3).toInt();
}

void Settings::save()
{
    saver->setValue("winningScore",winningScore);
    saver->setValue("refreshInterval",refreshInterval);
}

int Settings::getWinningScore() const
{
    return winningScore;
}

void Settings::setWinningScore(int value)
{
    winningScore = value;
}

int Settings::getRefreshInterval() const
{
    return refreshInterval;
}

void Settings::setRefreshInterval(int value)
{
    refreshInterval = value;
}
