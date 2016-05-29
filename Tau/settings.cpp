#include "settings.h"
#include <constants.h>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

Settings::Settings()
{
    saver = new QSettings();
    manager = new QNetworkAccessManager(this);
}

void Settings::load()
{
    refreshInterval = saver->value("refreshInterval",defaultRefreshInterval).toInt();
    winningScore = saver->value("winningScore",3).toInt();
    numGames = saver->value("numGames",0).toInt();
    AIModeEnabled = saver->value("AIModeEnabled",true).toBool();
    loaded = true;
}

int Settings::getWinningScore()
{
    if(!loaded){
        load();
    }
    return winningScore;
}

void Settings::setWinningScore(int value)
{
    winningScore = value;
    saver->setValue("winningScore",winningScore);
}

int Settings::getRefreshInterval()
{
    if(!loaded){
        load();
    }
    return refreshInterval;
}

void Settings::setRefreshInterval(int value)
{
    refreshInterval = value;
    saver->setValue("refreshInterval",refreshInterval);
}

int Settings::getNumGames()
{
    if(!loaded){
        load();
    }
    return numGames;
}

void Settings::setNumGames(int value)
{
    numGames = value;
    saver->setValue("numGames",value);
}

void Settings::incrementNumGames()
{
    if(!loaded){
        load();
    }
    numGames++;
    saver->setValue("numGames",numGames);

    manager->get(QNetworkRequest(QUrl("http://garrett.comze.com/Tau_counter/update.php")));
}

bool Settings::getAIModeEnabled()
{
    if(!loaded){
        load();
    }
    return AIModeEnabled;
}

void Settings::setAIModeEnabled(bool value)
{
    AIModeEnabled = value;
    saver->setValue("AIModeEnabled",value);
}

bool Settings::isLoaded() const
{
    return loaded;
}
