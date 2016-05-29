#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QNetworkReply>

class Settings: public QObject
{
    Q_OBJECT
public:
    Settings();
    void load();

    int getWinningScore();
    void setWinningScore(int value);

    int getRefreshInterval();
    void setRefreshInterval(int value);

    int getNumGames();
    void setNumGames(int value);

    void incrementNumGames();

    bool getAIModeEnabled();
    void setAIModeEnabled(bool value);

    bool isLoaded() const;

private:
    int refreshInterval;
    int winningScore;
    int numGames;
    bool AIModeEnabled;
    bool loaded = false;
    QSettings* saver;
    QNetworkAccessManager* manager;
};

#endif // SETTINGS_H
