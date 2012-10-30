#include "config.h"

Config::Config() {
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("DownloaderConfig.sqlite");
    maxNumberOfSimultaneousDownloads = DEFAULT_MAX_NUMER_OF_SIMULTANEOUS_DOWNLOADS;
    mainWindowLength = DEFAULT_MAIN_WINDOW_LENGTH;
    mainWindowHeight = DEFAULT_MAIN_WINDOW_HEIGHT;
    if (!dbase.open()) {
        isDBOpened = false;
        qDebug() << "Can't open DB";
        showError("Configuration stored in"
                  "DownloaderConfig.sqlite can't be opened."
                  "Configuration set to defaults and all "
                  "changes will NOT be saved.");
    } else {
        isDBOpened = true;
        initFromDB();
    }
}

void Config::initFromDB() {
    if (isDBOpened) {
        QSqlQuery selectParametersQuery("SELECT * FROM Parameters",dbase);
        QSqlQuery selectDownloadsListQuery("SELECT * FROM DownloadsList", dbase);

        bool selectParametersExecuted = false;
        bool selectDownloadsListExecuted = false;
        if (!selectParametersQuery.exec()) {
            qDebug() << "Can't select Parameters. Default values would be used.";
            selectParametersExecuted = false;
        } else {
            selectParametersExecuted = true;
        }
        if (!selectDownloadsListQuery.exec()) {
            qDebug() << "Can't select DownloadsList";
            selectDownloadsListExecuted = false;
        } else {
            selectDownloadsListExecuted = true;
        }
        qDebug() << "Selects executed";
        if (selectParametersExecuted) {
            if (selectParametersQuery.next()) {
                if (selectParametersQuery.size() >= 2) {
                    maxNumberOfSimultaneousDownloads = selectParametersQuery.value(1).toUInt();
                    if (selectParametersQuery.size() >= 3) {
                        mainWindowLength = selectParametersQuery.value(2).toUInt();
                        if (selectParametersQuery.size() >= 4) {
                            mainWindowHeight = selectParametersQuery.value(3).toUInt();
                            qDebug() << "All Parameters successfully selected.";
                        } else {
                            qDebug() << "There is less than 4 columns in record from Parameters table.";
                        }
                    } else {
                        qDebug() << "There is less than 3 columns in record from Parameters table.";
                    }
                } else {
                    qDebug() << "There is less than 2 columns in record from Parameters table.";
                }

            } else {
                qDebug() << "Parameters table is empty. Default values would be used.";
            }
        }
        if (selectDownloadsListExecuted) {
            while (selectDownloadsListQuery.next()) {
                if (selectDownloadsListQuery.size() >= 5) {
                    DownloadInfo info(
                                      selectDownloadsListQuery.value(1).toString(),
                                      selectDownloadsListQuery.value(2).toString(),
                                      selectDownloadsListQuery.value(3).toString(),
                                      selectDownloadsListQuery.value(4).toUInt()
                                      );
                    getDownloadsList().push_back(info);
                    qDebug() << "Download info inserted.";
                } else {
                    qDebug() << "There is less than 5 columns in record from DownloadsList table.";
                }
            }
        }
    }
}

void Config::saveToDB() const{
    if (isDBOpened) {
        QSqlQuery dropParametersQuery("DROP TABLE IF EXISTS Parameters",dbase);
        QSqlQuery dropDownloadsListQuery("DROP TABLE IF EXISTS DownloadsList", dbase);

        QSqlQuery createParametersQuery("CREATE TABLE IF NOT EXISTS Parameters ("
                                        "recordID INTEGER PRIMARY KEY NOT NULL, "
                                        "maxNumberOfSimultaneousDownloads INTEGER NOT NULL, "
                                        "mainWindowLength INTEGER NOT NULL, "
                                        "mainWindowHeight INTEGER NOT NULL"
                                        ");",dbase);
        QSqlQuery createDownloadsListQuery("CREATE TABLE IF NOT EXISTS DownloadsList ("
                                           "number INTEGER PRIMARY KEY NOT NULL, "
                                           "name TEXT, "
                                           "localAddress TEXT, "
                                           "internetAddress TEXT, "
                                           "priority INTEGER"
                                           ");", dbase);
        QString insertParametersQueryTemplate = "INSERT INTO "
                "Parameters(maxNumberOfSimultaneousDownloads, mainWindowLength, mainWindowHeight) "
                "VALUES (%1, %2, %3);";
        QSqlQuery insertParametersQuery(insertParametersQueryTemplate
                                        .arg(getMaxNumberOfSimultaneousDownloads())
                                        .arg(getMainWindowLength())
                                        .arg(getMainWindowHeight()),
                                        dbase);
        QString insertDownloadsListQueryTemplate = "INSERT INTO "
                "DownloadsList(number, name, localAddress, internetAddress, priority) "
                "VALUES (%1, '%2', '%3', '%4', %5);";
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

QList<DownloadInfo>& Config::getDownloadsList() const {
    return this->downloadsList;
}

quint32 Config::getMainWindowHeight() const {
    return this->mainWindowHeight;
}

quint32 Config::getMainWindowLength() const {
    return this->mainWindowLength;
}

quint8 Config::getMaxNumberOfSimultaneousDownloads() const {
    return this->maxNumberOfSimultaneousDownloads;
}

