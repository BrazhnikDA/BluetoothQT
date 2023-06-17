#include "BluetoothConnection.h"

#include <QDebug>
#include <QBluetoothLocalDevice>
#include <QtDBus>
#include <QDBusConnection>
#include <QDBusPendingReply>

BluetoothConnection::BluetoothConnection(QObject *parent) : QObject(parent)
{
    listDevice = QString("TEXT");

    QDBusInterface bluetoothInterface("net.connman", "/net/connman/technology/bluetooth",
                                      "net.connman.Technology", QDBusConnection::systemBus(), this);
    bluetoothInterface.call("SetProperty", "Powered", QVariant::fromValue(QDBusVariant(true)));
    QDBusConnection bus = QDBusConnection::systemBus();
       if (!bus.isConnected())
       {
         qFatal("Cannot connect to the D-Bus session bus.");
         return;
       }
    startWork();
}

void BluetoothConnection::startWork()
{
    startDiscovery();
}

QString BluetoothConnection::getText()
{
    return text;
}

void BluetoothConnection::setText(QString &newText)
{
    text = newText;
    emit textChanged();
}

void BluetoothConnection::startDiscovery()
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

void BluetoothConnection::deviceDiscoverFinished()
{
    qDebug() << "Device discover finished";
    listOfDevices = discoveryAgent->discoveredDevices();

    if (listOfDevices.isEmpty()) {
        qDebug() << "No devices found";
    }
    qDebug() << "Found new devices:";

    for (int i = 0; i < listOfDevices.size(); i++) {
        listDevice.append(listOfDevices.at(i).name().trimmed() + "\n");
        text += listOfDevices.at(i).name().trimmed() + "\n";
        qDebug() << listOfDevices.at(i).name().trimmed()
                 << " ("
                 << listOfDevices.at(i).address().toString().trimmed()
                 << ")";
        if(listOfDevices.at(i).name().trimmed() == "ESP32test") {
            selectedDevice = listOfDevices.at(i);
            deviceSelected();
        }
    }
    setText(text);

    emit textChanged();
}

void BluetoothConnection::deviceSelected()
{
    qDebug() << "User select a device: " << selectedDevice.name() << " ("
             << selectedDevice.address().toString().trimmed() << ")";
    if(socket->open(QIODevice::OpenMode())) {
        qDebug() << "OPEN!!!";
    } else { qDebug() << "NOT OPEN"; }
    socket->openMode();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    socket->connectToService(QBluetoothAddress(selectedDevice.address()),
                             QBluetoothUuid(QBluetoothUuid::SerialPort),
                             QIODevice::ReadWrite);

    //connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)),
      //      this, SLOT(socketError(QBluetoothSocket::SocketError)));

    connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketRead()));

}

void BluetoothConnection::socketConnected() {
    qDebug() << "Connected!";
    socketWrite("1");
}

void BluetoothConnection::socketDisconnected() {
     qDebug() << "socketDisconnected!";
}

void BluetoothConnection::socketRead() {
     qDebug() << "soket get read!";
     qDebug() << socket->readAll();
}

QStringList BluetoothConnection::data() const
{
    return QStringList() << "orange" << "skyblue";
}

void BluetoothConnection::socketWrite(QString message)
{
    QByteArray byteArr = QByteArray(message.toUtf8());
    socket->write(byteArr);
    qDebug() << "Maybe sended! " << message;
}
