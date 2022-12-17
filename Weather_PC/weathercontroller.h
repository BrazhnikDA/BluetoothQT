#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include <QNetworkAccessManager>
#include <QMainWindow>
#include <QObject>


class WeatherController
{
public:
    WeatherController();
    void getWeather();

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
};

#endif // WEATHERCONTROLLER_H
