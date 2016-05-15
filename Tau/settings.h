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

private:
    int winningScore;
    QSettings* saver;
};

#endif // SETTINGS_H
