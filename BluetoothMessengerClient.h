#ifndef BLUETOOTHMESSENGERCLIENT_H
#define BLUETOOTHMESSENGERCLIENT_H

#include <QObject>

#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QBluetoothSocket>

class BluetoothMessengerClient : public QObject {
    Q_OBJECT
public:
    explicit BluetoothMessengerClient(QObject *parent = 0);
    ~BluetoothMessengerClient();
    Q_INVOKABLE void startDiscovery(const QString &messageToSend);
    Q_INVOKABLE void stopDiscovery();
private:
    const QString SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
    QString message;
    QBluetoothSocket *socket = NULL;
    QBluetoothDeviceDiscoveryAgent* discoveryAgent;
    QBluetoothDeviceInfo device;
    QBluetoothLocalDevice localDevice;
    void requestPairing(const QBluetoothAddress &address);
    void startClient(const QBluetoothAddress &address);
    void stopClient();
signals:
    void messageReceived(QString message);
    void clientStatusChanged(QString text);
private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);
    void pairingError(QBluetoothLocalDevice::Error error);
    void socketConnected();
    void deviceSearchFinished();
    void readSocket();
};

#endif // BLUETOOTHMESSENGERCLIENT_H
