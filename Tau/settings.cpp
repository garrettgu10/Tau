#include "settings.h"

Settings::Settings()
{
    saver = new QSettings();
}

void Settings::load()
{

    winningScore = saver->value("winningScore",3).toInt();
}

void Settings::save()
{
    saver->setValue("winningScore",winningScore);
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
