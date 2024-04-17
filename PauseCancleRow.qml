import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import ReaderBackend

RowLayout {
    id: buttonRowRoot

    signal pause()
    signal propel()
    signal cancle()

    spacing: ReaderBackend.spacing()
    state: "propel"
    states: [
        State {
            name: "propel"

            PropertyChanges {
                target: pauseButton
                visible: true
            }

            PropertyChanges {
                target: propelButton
                visible: false
            }

            PropertyChanges {
                target: cancleButton
                visible: true
            }

        },
        State {
            name: "pause"

            PropertyChanges {
                target: pauseButton
                visible: false
            }

            PropertyChanges {
                target: propelButton
                visible: true
            }

            PropertyChanges {
                target: cancleButton
                visible: true
            }

        }
    ]

    BetterButton {
        id: pauseButton

        text: "Остановить"
        Layout.fillWidth: true
        Layout.leftMargin: ReaderBackend.margin()
        onClicked: {
            buttonRowRoot.state = "pause";
            buttonRowRoot.pause();
        }
    }

    BetterButton {
        id: propelButton

        text: "Продолжить"
        Layout.fillWidth: true
        Layout.leftMargin: ReaderBackend.margin()
        onClicked: {
            buttonRowRoot.state = "propel";
            buttonRowRoot.propel();
        }
    }

    BetterButton {
        id: cancleButton

        text: "Отменить"
        Layout.fillWidth: true
        Layout.rightMargin: ReaderBackend.margin()
        onClicked: {
            buttonRowRoot.state = "propel";
            buttonRowRoot.cancle();
        }
    }

}
