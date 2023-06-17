import QtQuick 2.2

  Rectangle {
      property bool animationRunning: true

      function appendText(newText) {
          searchText.text += newText
      }

      width: searchText.width + 40;
      height: searchText.height + bluetoothImage.height + 40;
      color: "#d7d6d5"
      border.color: "black"
      border.width: 1
      radius: 5

      Behavior on height {
          NumberAnimation { duration: 300 }
      }

      Image {
          id: bluetoothImage
          source: Qt.resolvedUrl("../icons/bluetooth.png")
          anchors.top: parent.top
          anchors.topMargin: 10
          anchors.horizontalCenter: parent.horizontalCenter

          RotationAnimation on rotation{
              id: ranimation
              target: bluetoothImage
              easing.type: Easing.InOutBack
              property: "rotation"
              from: 0
              to: 360
              duration: 2000
              loops: Animation.Infinite
              alwaysRunToEnd: true
              running: animationRunning
          }
      }

      Text {
          id: searchText

          anchors.top: bluetoothImage.bottom
          //anchors.bottom: parent.bottom
          anchors.topMargin: 10
          anchors.horizontalCenter: parent.horizontalCenter
          text: qsTr("Searching for chat service...");
          color: "black"

      }
  }
