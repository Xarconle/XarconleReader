import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import ReaderBackend

RowLayout {
    id: buttonRowRoot

    signal open(string file)
    signal start()

    spacing: ReaderBackend.spacing()

    BetterButton {
        id: openButton

        text: "Открыть"
        Layout.fillWidth: true
        Layout.leftMargin: ReaderBackend.margin()
        onClicked: fileDialog.open()
    }

    BetterButton {
        id: startButton

        enabled: false
        text: "Запустить"
        Layout.fillWidth: true
        Layout.rightMargin: ReaderBackend.margin()
        onClicked: buttonRowRoot.start()
    }

    FileDialog {
        id: fileDialog

        onAccepted: {
            var path = fileDialog.currentFile.toString();
            path = path.replace(/^(file:\/{3})/, "");
            path = decodeURIComponent(path);
            buttonRowRoot.open(path);
            startButton.enabled = true;
        }
    }

}
