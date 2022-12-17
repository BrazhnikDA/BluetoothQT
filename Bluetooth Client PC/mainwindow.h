#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBluetoothLocalDevice>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void startDiscovery();
    void deviceSelected();
public slots:
    void deviceDiscoverFinished();
    void socketWrite();
    void socketConnected();
    void socketDisconnected();
    void socketRead();
private:
    Ui::MainWindow *ui;
    QBluetoothLocalDevice *localDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<QBluetoothDeviceInfo> listOfDevices;
    QBluetoothDeviceInfo selectedDevice;
    QBluetoothSocket *socket;
};
#endif // MAINWINDOW_H
