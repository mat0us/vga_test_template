import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: btn

    signal clicked

    property color accentColor:  "#F47A00"
    property color bgColor:      "#1a1a1a"
    property real  cornerRadius: 16
    property int   fontSize:     22
    property real  pressScale:   0.96
    property string text:        ""

    width:  48
    height: 48
    radius: cornerRadius
    color:  bgColor
    border.color: accentColor
    border.width: 1.5

    Text {
        anchors.centerIn:    parent
        text:                btn.text
        color:               btn.accentColor
        font.pixelSize:      btn.fontSize
        font.bold:           true
        verticalAlignment:   Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    scale: mouseArea.pressed ? btn.pressScale : 1.0
    Behavior on scale {
        NumberAnimation { duration: 120 }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: btn.clicked()
    }
}
