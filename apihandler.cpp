#include "apihandler.h"

ApiHandler::ApiHandler()
{
    mManager = new QNetworkAccessManager();
}

void ApiHandler::getData(QString pCityname, QString pCountryCode)
{
    sendGeoRequest(pCityname, pCountryCode);
}


void ApiHandler::sendGeoRequest(QString pCityname, QString pCountryCode)
{
    QUrl lUrl( "http://api.openweathermap.org/geo/1.0/direct" );
    QUrlQuery lQuery;
    lQuery.addQueryItem( "q", QString( "%1,%2" ).arg( pCityname ).arg( pCountryCode ) );
    lQuery.addQueryItem( "limit", "1" );
    lQuery.addQueryItem( "appid", mAPIkey );
    lUrl.setQuery( lQuery );
    QNetworkRequest lRequest( lUrl );
    connect( mManager, &QNetworkAccessManager::finished, this, &ApiHandler::sendWeatherRequest );
    mManager->get( lRequest );
}

void ApiHandler::sendWeatherRequest(QNetworkReply *pReply)
{
    disconnect(mManager, &QNetworkAccessManager::finished, this, &ApiHandler::sendWeatherRequest);
    if (pReply->error() == QNetworkReply::NoError)
    {
        QByteArray lResponseRaw = pReply->readAll();
        QString lData = QString::fromUtf8(lResponseRaw);
        QJsonDocument lDoc = QJsonDocument::fromJson(lData.toUtf8());
        if (lDoc.isArray())
        {
            QJsonArray lJsonArray =lDoc.array();
            QJsonObject lObject = lJsonArray.first().toObject();
            QString lLat =  QString::number(lObject["lat"].toDouble());
            QString lLon = QString::number(lObject["lon"].toDouble());
            QUrl lUrl("https://api.openweathermap.org/data/2.5/weather");
            QUrlQuery lQuery;
            if (!(lLat == "0"&&lLon == "0"))
            {
                lQuery.addQueryItem("lat", lLat);
                lQuery.addQueryItem("lon", lLon);
                lQuery.addQueryItem("appid", mAPIkey);
                lQuery.addQueryItem("units", "metric");
                lUrl.setQuery(lQuery);
                QNetworkRequest lRequest(lUrl);
                connect(mManager, &QNetworkAccessManager::finished, this, &ApiHandler::processDone);
                mManager->get(lRequest);
            }
            else
            {
                emit sendErrorMessage("Invalid City Name");
            }

        }
        else
        {
            emit sendErrorMessage("Error While Parsing Json");

        }

    }
    else
    {
        emit sendErrorMessage(pReply->errorString());
    }

}

void ApiHandler::processDone(QNetworkReply *pReply)
{
    disconnect(mManager, &QNetworkAccessManager::finished, this, &ApiHandler::processDone);
    if (pReply->error() == QNetworkReply::NoError)
    {
        QByteArray lResponseRaw = pReply->readAll();
        QString lData = QString::fromUtf8(lResponseRaw);
        QJsonDocument lDocument = QJsonDocument::fromJson(lData.toUtf8());
        if (!lDocument.isNull())
        {
            QJsonObject lObject = lDocument.object();
            QString lDescription = lObject["weather"].toArray().first().toObject()["description"].toString();
            QString lTemperature = QString::number(lObject["main"].toObject().value("temp").toDouble());
            Data lData;
            lData.mTemperature = lTemperature;
            lData.mWeather = lDescription;
            emit sendDoneMessage(lData);
        }
        else
        {
            emit sendErrorMessage("Error while Parsing Json");

        }
    }
    else
    {
        emit sendErrorMessage(pReply->errorString());
    }
}



