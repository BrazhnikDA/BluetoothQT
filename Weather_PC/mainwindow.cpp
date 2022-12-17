#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

#include <QNetworkAccessManager>
#include <WeatherModel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     connect(ui->buttonGetWeather, SIGNAL(clicked()),this,SLOT(getWeather()));

}

void MainWindow::getResponse(QNetworkReply *reply)
{
    if(!reply->error()) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();

        // WEATHER from text
        QJsonArray jsonArrayWeather = jsonObject["weather"].toArray();
        QJsonValue valueWeather = jsonArrayWeather[0];
        QJsonValue weather = valueWeather["main"];

        // FEELS LIKE, TEMPERATURE
        QJsonValue jsonValueMain = jsonObject["main"];
        double feels_like = jsonValueMain["feels_like"].toDouble() - 273.15;
        double temperature = jsonValueMain["temp"].toDouble() - 273.15;

        QString valueAsStringFeelsLike = QString::number(feels_like);
        QString valueAsStringTemperature = QString::number(temperature);

        // NAME CITY
        QJsonValue name = jsonObject["name"];

        qDebug() << name.toString() + "\n" + weather.toString() + "\n" + valueAsStringFeelsLike + "\n" + valueAsStringTemperature + "\n";

        ui->weatherLabel->setText("Город:" + name.toString() + "\n" +
                                  "Температура: " + valueAsStringTemperature + "°\n" +
                                  "Как ощущается: " + valueAsStringFeelsLike + "°\n" +
                                  "Погода: " + weather.toString() + "\n");

        WeatherModel model;
    } else
    {
        ui->weatherLabel->setText("ERROR: City not found\nOnly Russian city!");
    }
}

void MainWindow::getWeather() {
    QString city = ui->lineEditWeather->text();
    QNetworkRequest request(QUrl("http://api.openweathermap.org/data/2.5/weather?q=" + city + ",ru&APPID=5ba6d4e9b64a6355a8c8222fda310aeb"));
    mngr = new QNetworkAccessManager(this);
    connect(mngr, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));

    mngr->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
}

