import QtQuick 2.0
import Sailfish.Silica 1.0
import LoadScreen 1.0

Page {
    id: page

    BluetoothConnection {
        id: bluetooth
    }

    Label {
        id: listBluetooth
        text: bluetooth.text
        anchors.horizontalCenter: page.horizontalCenter
        anchors.verticalCenter: page.verticalCenter
    }

    Row {

        Button {
            id: buttonOpenConsole
            backgroundColor: "white"
            anchors.bottom: page.bottom;
            anchors.horizontalCenter: page.horizontalCenter
            onClicked: {
                bluetooth.deviceSelected();
                pageStack.push(Qt.resolvedUrl("ConsoleSenderBT.qml"))
            }

            Text {
                text: "Подключиться"
                color: "#0000FF"
                anchors.centerIn: buttonOpenConsole
            }
        }

        Button {
            id: buttonOpenConsole2
            backgroundColor: "white"
            anchors.bottom: page.bottom;
            anchors.horizontalCenter: page.horizontalCenter
            onClicked: {
                bluetooth.startDiscovery();
            }

            Text {
                text: "Сканировать"
                color: "#0000FF"
                anchors.centerIn: buttonOpenConsole2
            }
        }
    }
}
