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
    QList<DownloadInfo> downloadsList;

    //Maintenance data
    bool isDBOpened;
    QSqlDatabase dbase;

    //Default values
    static const quint8 DEFAULT_MAX_NUMER_OF_SIMULTANEOUS_DOWNLOADS = 3;

    void initFromDB();

    //Creates QErrorMessage dialog with specified message
    void showError(QString message) const;

    //Private constrictors for singleton
    Config();
    Config(const Config&);
    const Config& operator=(Config&);

public:
    static const Config& Instance();

    void saveToDB() const; //Can't be plased to destructor
};

#endif // CONFIG_H
