/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Моё приложение для ОС Аврора project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: mainPage;
    objectName: "mainPage";
    allowedOrientations: Orientation.All;
    width: Screen.width; height: Screen.height;

    Rectangle {
        width: Screen.width; height: Screen.height;
        anchors.fill: parent;
        anchors.horizontalCenter: mainPage.horizontalCenter;
        anchors.verticalCenter: mainPage.verticalCenter;

        gradient: Gradient {
         GradientStop {
             position: 0.0; color: "#08e8de"
         }
         GradientStop {
             position: 1.0; color: "#1E90FF"
         }
        }
    }

    Image {
        width: 250; height: 250;
        id: imagePhoenix
        source: Qt.resolvedUrl("../icons/phoenix.svg")
        anchors.horizontalCenter: mainPage.horizontalCenter;
        y:275
    }

     Rectangle {
        id: rectangleEmail
        width: 550; height: 80
        color: "transparent"
        border.color: "#F8F8FF"
        border.width: 4
        radius: 25
        anchors.horizontalCenter: mainPage.horizontalCenter;
        anchors.top: imagePhoenix.bottom;
        anchors.topMargin: 30

        TextInput {
            id: inputEmail
            anchors.fill: parent
            anchors.margins: 2
            font.pointSize: 22
            text: "your_email@mail.com"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
     }

     Rectangle {
        id: rectanglePassword
        width: 550; height: 80
        color: "transparent"
        border.color: "#F8F8FF"
        border.width: 4
        radius: 25
        anchors.horizontalCenter: mainPage.horizontalCenter;
        anchors.top: rectangleEmail.bottom;
        anchors.topMargin: 30

        TextInput {
            id: inputPassword
            anchors.fill: parent
            anchors.margins: 2
            font.pointSize: 22
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "password"
        }
     }


    Button {
        id: buttonLogin
        backgroundColor: "white"
        anchors.horizontalCenter: mainPage.horizontalCenter;
        anchors.top: rectanglePassword.bottom;
        anchors.topMargin: 40

        onClicked: {
            bluetooth.startWork();
            pageStack.push(Qt.resolvedUrl("BluetoothScanner.qml"))
        }
        Text {
            text: "Вход"
            color: "#0000FF"
            anchors.centerIn: buttonLogin
        }
    }


    Button {
        id: buttonRegistration
        backgroundColor: "white"
        anchors.horizontalCenter: mainPage.horizontalCenter;
        anchors.top: buttonLogin.bottom;
        anchors.topMargin: 20

        Text {
            text: "Регистрация"
            color: "#0000FF"
            anchors.centerIn: buttonRegistration
        }
    }


    Component.onCompleted: {

    }
}
