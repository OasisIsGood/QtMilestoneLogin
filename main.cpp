#include <QCoreApplication>
#include <QDebug>

#include "milestonemanager.h"

#include <QDomDocument>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString lServer = "192.168.100.1";

    QStringList applicationArguments = a.arguments();
    if (applicationArguments.count()>1)
        lServer = applicationArguments.at(1);
    else
        qInfo() << "Usage: appName <server ip/name>";

    MilestoneManager *lMilestoneManager = new MilestoneManager;
    lMilestoneManager->initialize(lServer);
    lMilestoneManager->getVersion();
    lMilestoneManager->login("");

    return a.exec();
}
