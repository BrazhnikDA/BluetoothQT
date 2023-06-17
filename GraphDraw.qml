import QtQuick 2.0
import Sailfish.Silica 1.0
import LoadScreen 1.0

Page {
    id: graphDrawPage;
    objectName: "graphDrawPage";
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;

    RandomPulse {
        id: pulseRandom
        pulse: "70"
    }

    Text {
        id: textPulse
        text: pulseRandom.pulse
    }

    Timer {
        interval: 1000
        repeat: true
        running: true

        onTriggered: {
             pulseRandom.generatePulse(PulseMode.StateOfRest, textPulse.text)
        }
    }

}
