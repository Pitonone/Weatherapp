#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QObject>
#include <QDebug>



class ApiHandler : public QObject
{
     Q_OBJECT
public:
    ApiHandler();
    void  getData(QString pCityname, QString pCountryCode);
    struct Data
    {
        QString mTemperature;
        QString mWeather;
    };

private:
    void checkForInternet();
    QString mCityName;
    QString mCountryCode;
    QNetworkAccessManager* mManager = nullptr;
    const QString mAPIkey = "c470132e1097047341c778190cfe9612";
    void sendGeoRequest(QString pCityname, QString pCountryCode);


private slots:
    void sendWeatherRequest(QNetworkReply *pReply);
    void processDone(QNetworkReply *pReply);

signals:
   void sendDoneMessage(Data pData);
   void sendErrorMessage(QString pErrorString);

};


#endif // APIHANDLER_H
