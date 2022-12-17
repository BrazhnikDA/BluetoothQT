import QtQuick 2.0
import Sailfish.Silica 1.0
import LoadScreen 1.0

Page {
    id: weatherPage;
    objectName: "weatherPage";
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;


    // @disable-check M129
    Weather {
        id: weather
        text: weather.text
    }

    Rectangle {
       id: rectangleWeather
       width: 550; height: 50
       border.color: "white"
       border.width: 4
       radius: 8
       anchors.horizontalCenter: weatherPage.horizontalCenter;
       anchors.topMargin: 30


       Text {
           id: inputEmail
           anchors.fill: parent
           anchors.margins: 2
           font.pointSize: 22
           text: weather.text
       }
    }

    Button {
        id: buttonGetWeather;
        anchors.horizontalCenter: weatherPage.horizontalCenter;
        anchors.top: rectangleWeather.bottom
        text: "Get weather";
        anchors.topMargin: 30
        onClicked: {
            weather.showText();
            rectangleWeather.height = 180;
            buttonGetWeather.anchors.topMargin = 150;
            inputEmail.text = weather.text;
        }
    }

}
