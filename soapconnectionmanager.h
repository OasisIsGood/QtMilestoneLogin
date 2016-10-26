#ifndef SOAPCONNECTIONMANAGER_H
#define SOAPCONNECTIONMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class SoapConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit SoapConnectionManager(QObject *parent = 0);

    QString httpcall(QString server, QString data, QString soapAction);

private:
    QNetworkAccessManager *m_manager;
};

#endif // SOAPCONNECTIONMANAGER_H
