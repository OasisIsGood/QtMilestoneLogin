#include "milestonemanager.h"

#include <QDomDocument>
#include <QUuid>

MilestoneManager::MilestoneManager(QObject *parent) : QObject(parent),
    m_server("")
{
}

void MilestoneManager::initialize(QString server)
{
    qDebug() << Q_FUNC_INFO << server;
    m_server = server;
}

void MilestoneManager::getVersion()
{
    qDebug() << Q_FUNC_INFO;
    QString xmlData =
            QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>") +
            QString("<soap:Envelope ") +
            QString("xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">") +
            QString("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"") +
            QString("xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"") +
            QString("<soap:Body>") +
            QString("<GetVersion ") +
            QString("xmlns=\"http://videoos.net/2/XProtectCSServerCommand\">") +
            QString("</GetVersion>") +
            QString("</soap:Body>") +
            QString("</soap:Envelope>");

    QString xmlResult = lSoapConnectionManager.httpcall(m_server, xmlData,
                                    "http://videoos.net/2/XProtectCSServerCommand/GetVersion");
    QDomDocument xmlDomDoc;
    if (!xmlDomDoc.setContent(xmlResult))
        {
            qWarning() << "Error: Cannot parse data xml result";
            return;
        }
     QDomNodeList nodes = xmlDomDoc.elementsByTagName("GetVersionResult");
     for (int i= 0; i<nodes.count(); i++)
     {
         QDomNode lNode = nodes.at(i);
         qDebug() << "GetVersionResult:" << lNode.toElement().firstChild().nodeValue();
     }
}

void MilestoneManager::login(const QString &token)
{
    qDebug() << Q_FUNC_INFO;
    QString xmlData =
            QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>") +
            QString("<soap:Envelope ") +
            QString("xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">") +
            QString("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"") +
            QString("xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"") +
            QString("<soap:Body>") +
            QString("<Login xmlns=\"http://videoos.net/2/XProtectCSServerCommand\">") +
            QString("<instanceId>" + QUuid::createUuid().toString() + "</instanceId><currentToken>" + token + "</currentToken>") +
            QString("</Login>") +
            QString("</soap:Body>") +
            QString("</soap:Envelope>");

    QString xmlResult = lSoapConnectionManager.httpcall(m_server, xmlData,
                                    "http://videoos.net/2/XProtectCSServerCommand/Login");
    QDomDocument xmlDomDoc;
    if (!xmlDomDoc.setContent(xmlResult))
        {
            qWarning() << "Error: Cannot parse data xml result";
            return;
        }
     QDomNodeList nodes = xmlDomDoc.elementsByTagName("Token");
     for (int i= 0; i<nodes.count(); i++)
     {
         QDomNode lNode = nodes.at(i);
         qDebug() << "Token:" << lNode.toElement().firstChild().nodeValue();
     }
     nodes = xmlDomDoc.elementsByTagName("MicroSeconds");
     for (int i= 0; i<nodes.count(); i++)
     {
         QDomNode lNode = nodes.at(i);
         qDebug() << "MicroSeconds:" << lNode.toElement().firstChild().nodeValue();
     }
}
