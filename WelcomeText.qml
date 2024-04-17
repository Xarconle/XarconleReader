import QtQuick
import ReaderBackend

Rectangle {
    id: textRoot

    radius: 10
    color: ReaderBackend.secondBgColor()

    border {
        pixelAligned: true
        width: 1
        color: ReaderBackend.mainColor()
    }

    Text {
        id: text

        anchors.fill: parent
        padding: ReaderBackend.padding()
        verticalAlignment: Qt.AlignVCenter
        wrapMode: Text.Wrap
        font.pointSize: 12
        text: "Для начала работы необходимо выбрать файл и запустить обработку. Перед запуском можно задать минимальную длину слов, которые мы хотим считать.\nДля получения детальной информации о количестве вхождений или конкретном слове, необходимо ненадолго задержать указатель над соответствующим элементом."
    }

}
