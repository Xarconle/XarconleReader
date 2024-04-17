import QtQuick
import QtQuick.Layouts
import ReaderBackend

Item {

    id:buttonRoot

    signal clicked()

    property alias label: buttonText
    property alias text: buttonText.text
    property alias fontSize: buttonText.font.pointSize

    property alias backgroundRect: backgroundRect

    property alias hover: mouseArea.enabled

    Layout.minimumWidth: 100
    Layout.minimumHeight: 30


    state: "Nofocus"
    states: [
        State {
            name: "Disabled"; when: !buttonRoot.enabled
            PropertyChanges { target: backgroundRect; border.color: ReaderBackend.mainColor(); color: "#D3D3D3" }
            PropertyChanges { target: buttonText; color: ReaderBackend.mainColor() }
        },
        State {
            name: "Nofocus"; when: !mouseArea.containsMouse && buttonRoot.enabled
            PropertyChanges { target: backgroundRect; border.color: ReaderBackend.mainColor(); color: ReaderBackend.mainBgColor() }
            PropertyChanges { target: buttonText; color: ReaderBackend.mainColor() }
        },
        State {
            name: "Highlight"; when: mouseArea.containsMouse && !mouseArea.pressed && buttonRoot.enabled
            PropertyChanges { target: backgroundRect; border.color: ReaderBackend.mainColor(); color: ReaderBackend.secondBgColor() }
            PropertyChanges { target: buttonText; color: ReaderBackend.mainColor() }
        },
        State {
            name: "Pressed"; when: mouseArea.pressed && buttonRoot.enabled
            PropertyChanges { target: backgroundRect; border.color: "#0481ae"; color: ReaderBackend.secondBgColor() }
            PropertyChanges { target: buttonText; color: "#0481ae" }
        }
    ]

    Rectangle {

        id: backgroundRect

        anchors.fill: parent
        radius: height / 2.5

        border {
            pixelAligned: true
            width: 2
        }

    }

    Text{

        id: buttonText

        anchors.centerIn: parent
        font.pointSize: 12
    }

    MouseArea{

        id: mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onClicked: buttonRoot.clicked()
    }

}
