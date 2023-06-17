#include "BluetoothMessengerClient.h"
#include <QDebug>
#include <QBluetoothLocalDevice>
#include <QtDBus>

BluetoothMessengerClient::BluetoothMessengerClient(QObject *parent) : QObject(parent) {
    QDBusInterface bluetoothInterface("net.connman", "/net/connman/technology/bluetooth",
                                      "net.connman.Technology", QDBusConnection::systemBus(), this);
    bluetoothInterface.call("SetProperty", "Powered", QVariant::fromValue(QDBusVariant(true)));
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(localDevice.address());
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BluetoothMessengerClient::deviceDiscovered);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BluetoothMessengerClient::deviceSearchFinished);
    connect(&localDevice, &QBluetoothLocalDevice::pairingFinished,
            this, &BluetoothMessengerClient::pairingFinished);
    connect(&localDevice, &QBluetoothLocalDevice::error, this, &BluetoothMessengerClient::pairingError);
}

BluetoothMessengerClient::~BluetoothMessengerClient() {
    stopClient();
}

void BluetoothMessengerClient::startDiscovery(const QString &messageToSend) {
    if (socket != NULL) stopClient();
    qDebug() << "startDiscovery()";
    this->message = messageToSend;
    discoveryAgent->start();
    emit clientStatusChanged("Searching for device");
}

void BluetoothMessengerClient::stopDiscovery() {
    qDebug() << "stopDiscovery()";
    discoveryAgent->stop();
}

void BluetoothMessengerClient::deviceSearchFinished() {
    qDebug() << "deviceSearchFinished()";
    if (socket == NULL) emit clientStatusChanged("Device not found");
}

void BluetoothMessengerClient::deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo) {
    qDebug() << "deviceDiscovered()";
    qDebug() << deviceInfo.name();
    if (deviceInfo.serviceUuids().contains(QBluetoothUuid(SERVICE_UUID))) {
        emit clientStatusChanged("Device found");
        discoveryAgent->stop();
        requestPairing(deviceInfo.address());
    }
}

void BluetoothMessengerClient::pairingFinished(const QBluetoothAddress &address,
                                      QBluetoothLocalDevice::Pairing pairing) {
    qDebug() << "pairingFinished()";
    startClient(address);
}

void BluetoothMessengerClient::pairingError(QBluetoothLocalDevice::Error error) {
    qDebug() << "pairingError()";
    emit clientStatusChanged("Unable to pair devices");
}

void BluetoothMessengerClient::requestPairing(const QBluetoothAddress &address) {
    qDebug() << "requestPairing()";
    emit clientStatusChanged("Pairing devices");
    if (localDevice.pairingStatus(address) == QBluetoothLocalDevice::Paired) {
        startClient(address);
    } else {
        localDevice.requestPairing(address, QBluetoothLocalDevice::Paired);
    }
}

void BluetoothMessengerClient::startClient(const QBluetoothAddress &address) {
    qDebug() << "startClient()";
    if (socket != NULL) {
        socket->disconnectFromService();
        delete socket;
    }
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(socket, &QBluetoothSocket::connected, this, &BluetoothMessengerClient::socketConnected);
    connect(socket, &QBluetoothSocket::readyRead, this, &BluetoothMessengerClient::readSocket);
    socket->connectToService(address, 1);
}

void BluetoothMessengerClient::socketConnected() {
    qDebug() << "socketConnected()";
    emit clientStatusChanged("Connected to socket");
    socket->write(message.toUtf8());
}

void BluetoothMessengerClient::stopClient() {
    qDebug() << "stopClient()";
    if (socket != NULL) {
        socket->disconnectFromService();
        delete socket;
    }
    socket = NULL;
}

void BluetoothMessengerClient::readSocket() {
    qDebug() << "readSocket()";
    QString receivedMessage = QString::fromUtf8(socket->readLine().trimmed());
    emit messageReceived(receivedMessage);
    emit clientStatusChanged("Message received");
}
