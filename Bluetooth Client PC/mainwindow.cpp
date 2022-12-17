#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBluetoothLocalDevice>
#include <QBluetoothSocket>
#include <QBluetoothSocket>
#include <QBluetoothSocket>
#include <QThread>
#include <qbluetoothsocket.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    startDiscovery();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDiscovery()
{
    localDevice = new QBluetoothLocalDevice(this);

    if (localDevice->isValid()) {
        qDebug() << "Bluetooth is available on this device";
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        localDevice->powerOn();
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        qDebug() << "Local device: " << localDevice->name() << " ("
                 << localDevice->address().toString().trimmed() << ")";

        // Create a discovery agent and connect to its signals
        discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
        connect(discoveryAgent, SIGNAL(finished()),
                this, SLOT(deviceDiscoverFinished()));

        discoveryAgent->start();
        qDebug() << "Device discover started";
    }
    else {
        qDebug() << "Bluetooth is not available on this device";
    }
}

void MainWindow::deviceDiscoverFinished()
{
    qDebug() << "Device discover finished";
    listOfDevices = discoveryAgent->discoveredDevices();

    if (listOfDevices.isEmpty()) {
        qDebug() << "No devices found";
    }
    qDebug() << "Found new devices:";

    for (int i = 0; i < listOfDevices.size(); i++) {
        qDebug() << listOfDevices.at(i).name().trimmed()
                 << " ("
                 << listOfDevices.at(i).address().toString().trimmed()
                 << ")";
        if(listOfDevices.at(i).name().trimmed() == "ESP32_LED_Control") {
            selectedDevice = listOfDevices.at(i);
        }
    }
    deviceSelected();
}

void MainWindow::deviceSelected()
{
    qDebug() << "User select a device: " << selectedDevice.name() << " ("
             << selectedDevice.address().toString().trimmed() << ")";

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    socket->connectToService(QBluetoothAddress(selectedDevice.address()),
                             QBluetoothUuid(QBluetoothUuid::SerialPort),
                             QIODevice::ReadWrite);

    /*connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)),
            this, SLOT(socketError(QBluetoothSocket::SocketError)));*/

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));


}

void MainWindow::socketConnected() {
    qDebug() << "Connected!";
    socketWrite();
}

void MainWindow::socketDisconnected() {
     qDebug() << "socketDisconnected!";
}

void MainWindow::socketRead() {
     qDebug() << "soket get read!";
}

void MainWindow::socketWrite()
{
    QString str = "1";
    QByteArray byteArr = QByteArray(str.toUtf8());
    socket->write(byteArr);
    socket->write(byteArr);
    qDebug() << "Maybe sended!";
}
