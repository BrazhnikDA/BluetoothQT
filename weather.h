#ifndef WEATHER_H
#define WEATHER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <qnetworkreply.h>
#include <QObject>
#include <QEventLoop>

class Weather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
public:
    Weather();
    QString getText();
    void setText(QString &newText);
    Q_INVOKABLE void showText();

    QString text;

public slots:
    void getResponse(QNetworkReply *reply);

private slots:
    void getWeather();

signals:
    void textChanged();

private:
    QNetworkAccessManager *mngr;

};

#endif // WEATHER_H
