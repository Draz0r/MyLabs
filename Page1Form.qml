import QtQuick 2.10
import QtQuick.Controls 2.3
Page {
    width: 600
    height: 400
    contentWidth: 2
    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }
    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }
    Button {
        id: button
        x: 100
        y: 50
        text: qsTr("Button")
    }
    Button {
        id: button1
        x: 220
        y: 90
        text: qsTr("Button")
    }
}
