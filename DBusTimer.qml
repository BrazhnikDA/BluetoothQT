import QtQuick 2.0
import Nemo.DBus 2.0
import Sailfish.Silica 1.0
import QtQml.Models 2.2

Page {
    id: page
    PageHeader { title: qsTr("D-Bus Timer") }
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;

    Row {
        id: row
        width: Screen.width;
        Button {
            text: "Старт"
            onClicked: {
                timerAdaptor.start()
            }
        }

        Button {
            text: "Стоп"
            onClicked: {
                timerAdaptor.stop()
            }
        }
    }

    Text {
        id: textTimer
        anchors.horizontalCenter: page.horizontalCenter;
        anchors.verticalCenter: page.verticalCenter;
        font.pointSize: 56
        text: '0'
    }

    Timer {
        id: timer

        interval: timerAdaptor.interval
        repeat: true

        onTriggered:  {
            textTimer.text = parseInt(textTimer.text) + 1
            timerAdaptor.emitSignal("triggered")
            console.log("triggered")
        }
        onRunningChanged: {
            timerAdaptor.emitSignal("runningChanged", [running])
            console.log(running)
        }
    }

    DBusAdaptor {
        id: timerAdaptor

        property int interval: 1000
        readonly property bool runing: timer.running

        function start() { timer.start() }
        function stop() { timer.stop() }

        service: "ru.auroraos.DBusTimer"
        path:    "/ru/auroraos/DBusTimer"
        iface:   "ru.auroraos.DBusTimer"
        xml: ' <interface name="ru.auroraos.DBusTimer">\n'

    }
}
