#ifndef BLUETOOTHCONNECTION_H
#define BLUETOOTHCONNECTION_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothSocket>
#include <sys/socket.h>

#define BLUEZ_DBUS_SERVICE "org.bluez"
#define BLUEZ_DBUS_PATH "/org/bluez/hci0"
#define BLUEZ_DBUS_IF "org.bluez.Adapter1"


class BluetoothConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QStringList data READ data CONSTANT)
public:
    BluetoothConnection(QObject *parent = 0);
    void startDiscovery();

    QString getText();
    void setText(QString &newText);

    QString text;
    QStringList data() const;

public slots:
    void deviceDiscoverFinished();
    void socketWrite(QString message);
    void socketConnected();
    void socketDisconnected();
    void socketRead();
    Q_INVOKABLE void deviceSelected();

    Q_INVOKABLE void startWork();
signals:
    void textChanged();

private:
    QBluetoothLocalDevice *localDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<QBluetoothDeviceInfo> listOfDevices;
    QBluetoothDeviceInfo selectedDevice;
    QBluetoothSocket *socket;

    QString listDevice;
};

#endif // BLUETOOTHCONNECTION_H
