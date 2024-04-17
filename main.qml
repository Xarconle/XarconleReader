import HorizontalHistogramCpp
import QtCharts
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ReaderBackend

ApplicationWindow {
    id: root

    title: ReaderBackend.getAppName()
    height: 600
    width: 400
    minimumHeight: 600
    minimumWidth: 400
    visible: true
    color: ReaderBackend.mainBgColor()

    ColumnLayout {
        id: rootLayout

        anchors.fill: parent
        state: "begin"
        states: [
            State {
                name: "begin"

                PropertyChanges {
                    target: fileRow
                    visible: false
                }

                PropertyChanges {
                    target: welcomeText
                    visible: true
                }

                PropertyChanges {
                    target: histogram
                    visible: false
                }

                PropertyChanges {
                    target: progressBar
                    visible: false
                }

                PropertyChanges {
                    target: lengthRow
                    visible: false
                }

                PropertyChanges {
                    target: openStartRow
                    visible: true
                }

                PropertyChanges {
                    target: pauseCancleRow
                    visible: false
                }

            },
            State {
                name: "open"

                PropertyChanges {
                    target: fileRow
                    visible: true
                }

                PropertyChanges {
                    target: welcomeText
                    visible: false
                }

                PropertyChanges {
                    target: histogram
                    visible: true
                }

                PropertyChanges {
                    target: progressBar
                    visible: false
                }

                PropertyChanges {
                    target: lengthRow
                    visible: true
                }

                PropertyChanges {
                    target: openStartRow
                    visible: true
                }

                PropertyChanges {
                    target: pauseCancleRow
                    visible: false
                }

            },
            State {
                name: "start"

                PropertyChanges {
                    target: fileRow
                    visible: true
                }

                PropertyChanges {
                    target: welcomeText
                    visible: false
                }

                PropertyChanges {
                    target: histogram
                    visible: true
                }

                PropertyChanges {
                    target: progressBar
                    visible: true
                }

                PropertyChanges {
                    target: lengthRow
                    visible: false
                }

                PropertyChanges {
                    target: openStartRow
                    visible: false
                }

                PropertyChanges {
                    target: pauseCancleRow
                    visible: true
                }

            },
            State {
                name: "pause"

                PropertyChanges {
                    target: fileRow
                    visible: true
                }

                PropertyChanges {
                    target: welcomeText
                    visible: false
                }

                PropertyChanges {
                    target: histogram
                    visible: true
                }

                PropertyChanges {
                    target: progressBar
                    visible: true
                }

                PropertyChanges {
                    target: lengthRow
                    visible: false
                }

                PropertyChanges {
                    target: openStartRow
                    visible: false
                }

                PropertyChanges {
                    target: pauseCancleRow
                    visible: true
                }

            }
        ]

        FileRow {
            id: fileRow

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
        }

        WelcomeText {
            id: welcomeText

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
        }

        HorizontalHistogramCpp {
            id: histogram

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
        }

        LengthRow {
            id: lengthRow

            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
            height: ReaderBackend.secondHeight()
        }

        ProgressBar {
            id: progressBar

            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
            padding: 2
            from: 0
            to: 100

            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 6
                color: "#e6e6e6"
                radius: 3

                border {
                    pixelAligned: true
                    width: 1
                    color: ReaderBackend.borderColor()
                }

            }

            contentItem: Item {
                implicitWidth: 200
                implicitHeight: 4

                Rectangle {
                    width: progressBar.visualPosition * parent.width
                    height: parent.height
                    radius: 2
                    color: ReaderBackend.mainColor()
                }

            }

        }

        OpenStartRow {
            id: openStartRow

            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
            height: ReaderBackend.mainHeight()
            onOpen: (fileName) => {
                fileRow.fileName = fileName;
                ReaderBackend.openFile(fileName);
                histogram.clear();
                rootLayout.state = "open";
            }
            onStart: {
                ReaderBackend.processFile(lengthRow.length);
                histogram.clear();
                rootLayout.state = "start";
            }
        }

        PauseCancleRow {
            id: pauseCancleRow

            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.margins: ReaderBackend.margin()
            height: ReaderBackend.mainHeight()
            onPropel: {
                ReaderBackend.propel();
            }
            onPause: {
                ReaderBackend.pause();
                rootLayout.state = "pause";
            }
            onCancle: {
                progressBar.value = 0;
                ReaderBackend.stop();
                rootLayout.state = "open";
            }
        }

        Connections {
            function onFinished() {
                rootLayout.state = "open";
            }

            target: ReaderBackend
        }

        Connections {
            function onUpdateStatus() {
                progressBar.value = ReaderBackend.status();
                histogram.updateTop(ReaderBackend.getTop15());
            }

            target: ReaderBackend
        }

    }

}
