import QtQuick 2.0
import Sailfish.Silica 1.0
import LoadScreen 1.0

Page {
    id: page

    /**
    ListView {
        id: model
        width: parent.width;
        height: parent.height
        model: bluetooth.data

        delegate: Rectangle {
            width: parent.width
            height: Theme.itemSizeMedium
            Label {
                text: bluetooth.data
                font.pixelSize: Theme.fontSizeMedium
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: Theme.paddingLarge
                }
            }
        }
    }
    **/

    Label {
        id: listBluetooth
        text: bluetooth.text
        anchors.horizontalCenter: page.horizontalCenter
        anchors.verticalCenter: page.verticalCenter
    }

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
}


