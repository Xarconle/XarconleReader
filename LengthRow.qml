import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ReaderBackend

Rectangle {
    id: rowRoot

    readonly property alias length: rowTextInput.text

    radius: height / 2.5

    border {
        pixelAligned: true
        width: 1
        color: ReaderBackend.mainColor()
    }

    RowLayout {
        id: rowLayout

        anchors.fill: parent
        spacing: ReaderBackend.spacing()

        Text {
            id: rowTextLabel

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.leftMargin: ReaderBackend.margin()
            width: 20
            text: "Длина слова:"
        }

        TextInput {
            id: rowTextInput

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rightMargin: ReaderBackend.margin()
            inputMethodHints: Qt.ImhDigitsOnly
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            inputMask: "9"
            text: "0"
        }

    }

}
