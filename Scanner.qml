import QtQuick 2.0
import QtBluetooth 5.2
import Sailfish.Silica 1.0

Page {
    id: scannerPage;
    objectName: "scannerPage";
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;

    PageHeader { title: qsTr("Scanner bluetooth QML") }

    Item {
        id: top
        width: Screen.width; height: Screen.height;

        property BluetoothService currentService

        BluetoothDiscoveryModel {
            id: btModel
            running: true
            discoveryMode: BluetoothDiscoveryModel.DeviceDiscovery
            onDiscoveryModeChanged: console.log("Discovery mode: " + discoveryMode)
            onServiceDiscovered: console.log("Found new service " + service.deviceAddress + " " + service.deviceName + " " + service.serviceName);
            onDeviceDiscovered: console.log("New device: " + device)
            onErrorChanged: {
                switch (btModel.error) {
                case BluetoothDiscoveryModel.PoweredOffError:
                    console.log("Error: Bluetooth device not turned on"); break;
                case BluetoothDiscoveryModel.InputOutputError:
                    console.log("Error: Bluetooth I/O Error"); break;
                case BluetoothDiscoveryModel.InvalidBluetoothAdapterError:
                    console.log("Error: Invalid Bluetooth Adapter Error"); break;
                case BluetoothDiscoveryModel.NoError:
                    break;
                default:
                    console.log("Error: Unknown Error"); break;
                }
            }
        }

        Rectangle {
            id: busy

            width: top.width * 0.7;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: top.top;
            height: text.height*1.2;
            radius: 5
            color: "#1c56f3"
            visible: btModel.running

            Text {
                id: text
                text: "Scanning"
                font.bold: true
                font.pointSize: 20
                anchors.centerIn: parent
            }

            SequentialAnimation on color {
                id: busyThrobber
                ColorAnimation { easing.type: Easing.InOutSine; from: "#1c56f3"; to: "white"; duration: 1000; }
                ColorAnimation { easing.type: Easing.InOutSine; to: "#1c56f3"; from: "white"; duration: 1000 }
                loops: Animation.Infinite
            }
        }

        ListView {
            id: mainList
            width: top.width
            anchors.top: busy.bottom
            anchors.bottom: buttonGroup.top
            anchors.bottomMargin: 10
            anchors.topMargin: 10
            clip: true

            model: btModel
            delegate: Rectangle {
                id: btDelegate
                width: parent.width
                height: column.height + 30

                property bool expended: false;
                clip: true
                Image {
                    id: bticon
                    source: Qt.resolvedUrl("../icons/bluetooth.png")
                    width: bttext.height;
                    height: bttext.height;
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.margins: 5
                }

                Column {
                    id: column
                    anchors.left: bticon.right
                    anchors.leftMargin: 5
                    Text {
                        id: bttext
                        text: deviceName ? deviceName : name
                        font.family: "FreeSerif"
                        font.pointSize: 22
                    }

                    Text {
                        id: details
                        function get_details(s) {
                            if (btModel.discoveryMode == BluetoothDiscoveryModel.DeviceDiscovery) {
                                //We are doing a device discovery
                                var str = "Address: " + remoteAddress;
                                return str;
                            } else {
                                str = "Address: " + s.deviceAddress;
                                if (s.serviceName) { str += "<br>Service: " + s.serviceName; }
                                if (s.serviceDescription) { str += "<br>Description: " + s.serviceDescription; }
                                if (s.serviceProtocol) { str += "<br>Protocol: " + s.serviceProtocol; }
                                return str;
                            }
                        }
                        visible: opacity !== 0
                        opacity: btDelegate.expended ? 1 : 0.0
                        text: get_details(service)
                        font.family: "FreeSerif"
                        font.pointSize: 18
                        Behavior on opacity {
                            NumberAnimation { duration: 200}
                        }
                    }
                }
                Behavior on height { NumberAnimation { duration: 200} }

            }
            focus: true
        }

        Row {
            id: buttonGroup
            property var activeButton: devButton

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 5
            spacing: 10

            Button {
                id: fdButton
                width: top.width/3*0.9
                //mdButton has longest text
                height: mdButton.height
                text: "Full Discovery"
                onClicked: btModel.discoveryMode = BluetoothDiscoveryModel.FullServiceDiscovery
            }
            Button {
                id: mdButton
                width: top.width/3*0.9
                text: "Minimal Discovery"
                onClicked: btModel.discoveryMode = BluetoothDiscoveryModel.MinimalServiceDiscovery
            }
            Button {
                id: devButton
                width: top.width/3*0.9
                //mdButton has longest text
                height: mdButton.height
                text: "Device Discovery"
                onClicked: btModel.discoveryMode = BluetoothDiscoveryModel.DeviceDiscovery
            }

            Button {
                id: send
                width: top.width/3*0.9
                height: mdButton.height
                text: "send"
                onClicked: btModel.
            }
        }

    }
}
