#include "downloadinfo.h"

qint32 DownloadInfo::maxNumber = 0;

DownloadInfo::DownloadInfo(QString name, QString localAddress, QString internetAddress, quint8 priority) {
    number = ++maxNumber;
    this->name = name;
    this->localAddress = localAddress;
    this->internetAddress = internetAddress;
    this->priority = priority;
}


quint32 DownloadInfo::getNumber() const{
    return number;
}

const QString& DownloadInfo::getName() const{
    return name;
}

const QString& DownloadInfo::getLocalAddress() const{
    return localAddress;
}

const QString& DownloadInfo::getInternetAddress() const{
    return internetAddress;
}

quint8 DownloadInfo::getPriority() const{
    return priority;
}
