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
    numGames = saver->value("numGames",0).toInt();
}

int Settings::getWinningScore() const
{
    return winningScore;
}

void Settings::setWinningScore(int value)
{
    winningScore = value;
    saver->setValue("winningScore",winningScore);
}

int Settings::getRefreshInterval() const
{
    return refreshInterval;
}

void Settings::setRefreshInterval(int value)
{
    refreshInterval = value;
    saver->setValue("refreshInterval",refreshInterval);
}

int Settings::getNumGames() const
{
    return numGames;
}

void Settings::setNumGames(int value)
{
    numGames = value;
    saver->setValue("numGames",value);
}

void Settings::incrementNumGames()
{
    numGames = saver->value("numGames",0).toInt()+1;
    saver->setValue("numGames",numGames);
}
