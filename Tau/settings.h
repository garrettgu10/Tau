#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>


class Settings
{
public:
    Settings();
    void load();
    void save();

    int getWinningScore() const;
    void setWinningScore(int value);

    int getRefreshInterval() const;
    void setRefreshInterval(int value);

private:
    int refreshInterval;
    int winningScore;
    QSettings* saver;
};

#endif // SETTINGS_H
