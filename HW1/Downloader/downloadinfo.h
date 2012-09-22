#ifndef DOWNLOADINFO_H
#define DOWNLOADINFO_H

#include <QString>

class DownloadInfo
{   
    quint32 number;
    QString name;
    QString localAddress;
    QString internetAddress;
    quint8 priority;

    static qint32 maxNumber;

    DownloadInfo();

public:
    DownloadInfo(QString name, QString localAddress, QString internetAddress, quint8 priority);

    quint32 getNumber() const;
    const QString& getName() const;
    const QString& getLocalAddress() const;
    const QString& getInternetAddress() const;
    quint8 getPriority() const;

};

#endif // DOWNLOADINFO_H
