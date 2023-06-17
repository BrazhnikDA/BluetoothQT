import QtQuick 2.0
import Sailfish.Silica 1.0
import LoadScreen 1.0

Page {
    id: btConnectionPage;
    objectName: "btConnectionPage";
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;


    Rectangle {
        id: rectangleMessage
        width: 400; height: 80
        color: "transparent"
        border.color: "#F8F8FF"
        border.width: 4
        anchors.left: btConnectionPage.left;
        anchors.bottom: btConnectionPage.bottom;

        TextInput {
            id: inputMessage
            anchors.fill: parent
            anchors.margins: 2
            font.pointSize: 22
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Button {
        id: buttonSendMessage
        backgroundColor: "white"
        anchors.left: rectangleMessage.right;
        anchors.bottom: btConnectionPage.bottom;

        onClicked: {
            bluetooth.socketWrite(inputMessage.text)
        }

        Text {
            text: "Отправить"
            color: "#0000FF"
            anchors.centerIn: buttonSendMessage
        }
    }
}
