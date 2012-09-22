#include "config.h"

Config::Config() {
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("DownloaderConfig.sqlite");
    if (!dbase.open()) {
        isDBOpened = false;
        qDebug() << "Can't open DB";
        showError("Configuration stored in"
                  "DownloaderConfig.sqlite can't be opened."
                  "Configuration set to defaults and all "
                  "changes will NOT be saved.");
        maxNumberOfSimultaneousDownloads = DEFAULT_MAX_NUMER_OF_SIMULTANEOUS_DOWNLOADS;
    } else {
        isDBOpened = true;
        initFromDB();
    }
}

void Config::initFromDB() {
    if (isDBOpened) {
        QSqlQuery selectParametersQuery("SELECT * FROM Parameters",dbase);
        QSqlQuery selectDownloadsListQuery("SELECT * FROM DownloadsList", dbase);
    }
}

void Config::saveToDB() const{
    if (isDBOpened) {
        QSqlQuery dropParametersQuery("DROP TABLE IF EXISTS Parameters",dbase);
        QSqlQuery dropDownloadsListQuery("DROP TABLE IF EXISTS DownloadsList", dbase);

        QSqlQuery createParametersQuery("CREATE TABLE IF NOT EXISTS Parameters ("
                                        "recordID INTEGER PRIMARY KEY NOT NULL, "
                                        "maxNumberOfSimultaneousDownloads INTEGER NOT NULL"
                                        ");",dbase);
        QSqlQuery createDownloadsListQuery("CREATE TABLE IF NOT EXISTS DownloadsList ("
                                           "number INTEGERPRIMARY KEY NOT NULL, "
                                           "name TEXT, "
                                           "localAddress TEXT, "
                                           "internetAddress TEXT, "
                                           "priority INTEGER"
                                           ");", dbase);
        QString insertParametersQueryTemplate = "INSERT INTO "
                "Parameters(maxNumberOfSimultaneousDownloads) "
                "VALUES (%1);";
        QSqlQuery insertParametersQuery(insertParametersQueryTemplate
                                        .arg(maxNumberOfSimultaneousDownloads),
                                        dbase);
        QString insertDownloadsListQueryTemplate = "INSERT INTO "
                "DownloadsList(number, name, localAddress, internetAddress, priority) "
                "VALUES (%1, '%2', '%3', '%4', %5);";
        QSqlQuery insertDownloadsListQuery(insertDownloadsListQueryTemplate
                                           .arg(maxNumberOfSimultaneousDownloads),
                                           dbase);
        if (!dropParametersQuery.exec()) {
            qDebug() << "Can't drop Parameters";
            showError("Have DB issues. Current state will NOT be saved."
                      "(Can't drop Parameters table)");
        } else if (!dropDownloadsListQuery.exec()) {
            qDebug() << "Can't drop DownloadsList";
            showError("Have DB issues. Current state will NOT be saved."
                      "(Can't drop DownloadsList table)");
        } else if (!dropParametersQuery.exec()) {
            qDebug() << "Can't drop Parameters";
            showError("Have DB issues. Current state will NOT be saved."
                      "(Can't drop Parameters table)");
        } else if (!createParametersQuery.exec()) {
            qDebug() << "Can't create Parameters";
            showError("Have DB issues. Current state will NOT be saved."
                      "(Can't create Parameters table)");
        } else if (!createDownloadsListQuery.exec()) {
            qDebug() << "Can't create DownloadsList";
            showError("Have DB issues. Current state will NOT be saved."
                      "(Can't create DownloadsList table)");
        } else if (!insertParametersQuery.exec()){
            qDebug() << "Can't insert to Parameters table";
            showError("Have DB issues. Current state will NOT be saved."
                      "(Can't insert to Parameters table");
        } else {
            qDebug() << "Start to save Downloads";
            for (QList<DownloadInfo>::const_iterator i = downloadsList.begin(); i != downloadsList.end(); ++i) {
                QSqlQuery insertDownloadsListQuery(insertDownloadsListQueryTemplate
                                                   .arg(i->getNumber())
                                                   .arg(i->getName())
                                                   .arg(i->getLocalAddress())
                                                   .arg(i->getInternetAddress())
                                                   .arg(i->getPriority()),
                                                   dbase);
                if (!insertDownloadsListQuery.exec()) {
                    qDebug() << "Can't insert to DownloadsList table";
                    showError("Have DB issues. Current state will NOT be saved."
                              "(Can't insert to DownloadsList table");
                    break;
                }
            }
            qDebug() << "Configuration saved";
        }
    }
}

void Config::showError(QString message) const{
    qDebug() << "Creating dialog.";
    QErrorMessage* dBMessage = new QErrorMessage();
    dBMessage->showMessage(message);
    dBMessage->exec();
    qDebug() << "Dialog closed.";
}

const Config& Config::Instance() {
    static Config myInstance;
    return myInstance;
}

