#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMainWindow>
#include <QNetworkReply>
#include <qnetworkreply.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getResponse(QNetworkReply *reply);
private slots:
    void getWeather();
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *mngr;
};
#endif // MAINWINDOW_H
