#include "weather.h"
#include <QTextCodec>
#include <QNetworkAccessManager>
#include <QDebug>

Weather::Weather() : QObject()
{

}

QString Weather::getText()
{
    return text;
}

void Weather::setText(QString &newText)
{
    text = newText;
}

void Weather::showText()
{
    getWeather();
    qDebug() << text;
}

void Weather::getResponse(QNetworkReply *reply)
{
    if(!reply->error()) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();

        double fl = jsonObject["main"].toObject().value("feels_like").toDouble() - 273.15;
        double temp = jsonObject["main"].toObject().value("temp").toDouble() - 273.15;

        QString valueAsStringFeelsLike = QString::number(fl);
        QString valueAsStringTemperature = QString::number(temp);

        // NAME CITY
        QJsonValue name = jsonObject["name"];

        text = "Город:" + name.toString() + "\n" +
                "Температура: " + valueAsStringTemperature + "°\n" +
                "Как ощущается: " + valueAsStringFeelsLike + "°\n";

        qDebug() << text;

    } else
    {
        text = "ERROR: City not found\nOnly Russian city!";
    }
}

void Weather::getWeather()
{
    QString city = "moscow";
    QNetworkRequest request(QUrl("http://api.openweathermap.org/data/2.5/weather?q=" + city + ",ru&APPID=5ba6d4e9b64a6355a8c8222fda310aeb"));
    mngr = new QNetworkAccessManager();

    connect(mngr, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));

    mngr->get(request);
}
