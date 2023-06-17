import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: mainPage;
    objectName: "mainPage";
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;

    PageHeader { title: qsTr("Menu") }
    Column {
        id: row
        anchors.centerIn: parent
        spacing: 32


        Button {
            id: buttonMainPage
            backgroundColor: "white"
            anchors.horizontalCenter: mainPage.horizontalCenter;
            anchors.top: rectanglePassword.bottom;
            anchors.topMargin: 40

            onClicked: {
                bluetooth.startWork();
                pageStack.push(Qt.resolvedUrl("MainPage.qml"))
            }
            Text {
                text: "Авторизация"
                color: "#0000FF"
                anchors.centerIn: buttonMainPage
            }
        }

        Button {
            id: buttonWeather
            backgroundColor: "white"
            anchors.horizontalCenter: mainPage.horizontalCenter;
            anchors.top: rectanglePassword.bottom;
            anchors.topMargin: 40

            onClicked: {
                bluetooth.startWork();
                pageStack.push(Qt.resolvedUrl("Weather.qml"))
            }
            Text {
                text: "Погода"
                color: "#0000FF"
                anchors.centerIn: buttonWeather
            }
        }

        Button {
            id: buttonBluetoothScanner
            backgroundColor: "white"
            anchors.horizontalCenter: mainPage.horizontalCenter;
            anchors.top: rectanglePassword.bottom;
            anchors.topMargin: 40

            onClicked: {
                bluetooth.startWork();
                pageStack.push(Qt.resolvedUrl("BluetoothScanner.qml"))
            }
            Text {
                text: "Сканнер"
                color: "#0000FF"
                anchors.centerIn: buttonBluetoothScanner
            }
        }

        Button {
            id: buttonBluetoothScannerQML
            backgroundColor: "white"
            anchors.horizontalCenter: mainPage.horizontalCenter;
            anchors.top: rectanglePassword.bottom;
            anchors.topMargin: 40

            onClicked: {
                bluetooth.startWork();
                pageStack.push(Qt.resolvedUrl("Scanner.qml"))
            }
            Text {
                text: "Сканер QML"
                color: "#0000FF"
                anchors.centerIn: buttonBluetoothScannerQML
            }
        }

        Button {
            id: buttonTimer
            backgroundColor: "white"
            anchors.horizontalCenter: mainPage.horizontalCenter;
            anchors.top: rectanglePassword.bottom;
            anchors.topMargin: 40

            onClicked: {
                bluetooth.startWork();
                pageStack.push(Qt.resolvedUrl("DBusTimer.qml"))
            }
            Text {
                text: "Таймер"
                color: "#0000FF"
                anchors.centerIn: buttonTimer
            }
        }
    }
}
