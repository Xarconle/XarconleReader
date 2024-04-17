import QtQuick
import QtQuick.Layouts
import ReaderBackend

Rectangle {
    id: fileRoot

    property alias fileName: fileNameLabel.text

    height: fileNameLabel.height
    radius: height / 2.5
    color: ReaderBackend.secondBgColor()

    border {
        pixelAligned: true
        width: 1
        color: ReaderBackend.mainColor()
    }

    RowLayout {
        id: fileLayout

        anchors.fill: parent
        spacing: ReaderBackend.spacing()

        Text {
            id: fileTextLabel

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.leftMargin: ReaderBackend.margin()
            width: 20
            text: "Файл:"
        }

        Text {
            id: fileNameLabel

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.rightMargin: ReaderBackend.margin()
            height: ReaderBackend.secondHeight()
            wrapMode: Text.Wrap
            text: ""
            maximumLineCount: 1
        }

    }

}
