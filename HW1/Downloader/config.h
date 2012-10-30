#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>
#include <QList>
#include <QtSql>
#include <QErrorMessage>

#include "downloadinfo.h"

class Config
{
    //Data to store in DB
    quint8 maxNumberOfSimultaneousDownloads;
    quint32 mainWindowLength;
    quint32 mainWindowHeight;
    mutable QList<DownloadInfo> downloadsList;

    //Maintenance data
    bool isDBOpened;
    QSqlDatabase dbase;

    //Default values
    static const quint8 DEFAULT_MAX_NUMER_OF_SIMULTANEOUS_DOWNLOADS = 3;
    static const quint32 DEFAULT_MAIN_WINDOW_LENGTH = 500;
    static const quint32 DEFAULT_MAIN_WINDOW_HEIGHT = 300;

    void initFromDB();

    //Creates QErrorMessage dialog with specified message
    void showError(QString message) const;

    //Private constrictors for singleton
    Config();
    Config(const Config&);
    const Config& operator=(Config&);

public:
    static const Config& Instance();

    void saveToDB() const; //Can't be placed to destructor

    quint8 getMaxNumberOfSimultaneousDownloads() const;
    quint32 getMainWindowLength() const;
    quint32 getMainWindowHeight() const;
    QList<DownloadInfo>& getDownloadsList() const;


};

#endif // CONFIG_H
