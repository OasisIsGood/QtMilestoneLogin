#ifndef MILESTONEMANAGER_H
#define MILESTONEMANAGER_H

#include "soapconnectionmanager.h"

#include <QObject>

class MilestoneManager : public QObject
{
    Q_OBJECT
public:
    explicit MilestoneManager(QObject *parent = 0);

    void initialize(QString server);
    void getVersion();
    void login(const QString &token);

private:
    QString m_server;
    SoapConnectionManager lSoapConnectionManager;
};

#endif // MILESTONEMANAGER_H
