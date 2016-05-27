#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>


class Settings
{
public:
    Settings();
    void load();

    int getWinningScore() const;
    void setWinningScore(int value);

    int getRefreshInterval() const;
    void setRefreshInterval(int value);

    int getNumGames() const;
    void setNumGames(int value);

    void incrementNumGames();

private:
    int refreshInterval;
    int winningScore;
    int numGames;
    QSettings* saver;
};

#endif // SETTINGS_H
