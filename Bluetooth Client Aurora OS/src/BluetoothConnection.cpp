#include "BluetoothConnection.h"

BluetoothConnection::BluetoothConnection(QObject *parent) : QObject(parent)
{
    listDevice = QString("TEXT");
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
        if(listOfDevices.at(i).name().trimmed() == "ESP32_LED_Control") {
            selectedDevice = listOfDevices.at(i);
        }
    }
    setText(text);

    emit textChanged();
}

void BluetoothConnection::deviceSelected()
{
    qDebug() << "User select a device: " << selectedDevice.name() << " ("
             << selectedDevice.address().toString().trimmed() << ")";

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
