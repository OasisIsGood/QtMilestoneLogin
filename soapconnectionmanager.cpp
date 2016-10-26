#include "soapconnectionmanager.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

SoapConnectionManager::SoapConnectionManager(QObject *parent) : QObject(parent),
    m_manager(new QNetworkAccessManager)
{
    // NOTE: no connect: we want synchronous actions
    //connect(m_manager,SIGNAL(finished(QNetworkReply*)),this, SLOT(httpdown(QNetworkReply*)));

    m_manager->setNetworkAccessible(QNetworkAccessManager::Accessible);
}

QString SoapConnectionManager::httpcall(QString server, QString data, QString soapAction)
{
    qDebug() << Q_FUNC_INFO
             << QUrl::fromUserInput(server + "/servercommandservice/servercommandservice.asmx")
             << data;
    QByteArray arr;
    arr.append(data);
    QNetworkRequest request;
    QUrl lUrl(QUrl::fromUserInput(server + "/servercommandservice/servercommandservice.asmx"));
    lUrl.setPort(80);
    qDebug() << lUrl.host() << lUrl.port();
    request.setUrl(lUrl);
    request.setHeader( QNetworkRequest::ContentTypeHeader, QVariant( QString("text/xml;charset=utf-8")));
    request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant( qulonglong(arr.size()) ));
    request.setRawHeader("SOAPAction", soapAction.toLatin1());
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QVariant( int(QNetworkRequest::AlwaysNetwork) ));
    QNetworkReply *result = m_manager->post(request,arr);

    QEventLoop loop;
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();

    if (result->error() != QNetworkReply::NoError)
    {
        QString errorMessage = "Connection error: ";
        switch (result->error()) {
        case QNetworkReply::ConnectionRefusedError:
            qWarning() << "ConnectionRefusedError";
            errorMessage += "ConnectionRefusedError";
            break;
        case QNetworkReply::TimeoutError:
            qWarning() << "TimeoutError";
            errorMessage += "TimeoutError";
            break;
        case QNetworkReply::NetworkSessionFailedError:
            qWarning() << "NetworkSessionFailedError";
            errorMessage += "NetworkSessionFailedError";
            break;
        case QNetworkReply::ContentNotFoundError:
            qWarning() << "ContentNotFoundError";
            errorMessage += "ContentNotFoundError";
            break;
        case QNetworkReply::AuthenticationRequiredError:
            qWarning() << "AuthenticationRequiredError";
            errorMessage += "AuthenticationRequiredError";
            break;
        default:
            qWarning() << result->error();
            errorMessage += result->error();
            break;
        }
        result->deleteLater();
        result = Q_NULLPTR;
        return errorMessage;
    }

    QString dataResult = result->readAll();
    qDebug() << Q_FUNC_INFO << dataResult;

    result->deleteLater();
    result = Q_NULLPTR;

    return dataResult;
}
