import QtQuick 2.0
import OpenGLUnderQML 1.0

// Kořenný item definuje velikost obsahu okna.
Item {
    width: 1024
    height: 1024

    // TODO 13 ANIMATION: OpenGL scéna s animační podporou
    OpenGLScene {
        id: openglScene
        
        // TODO 14 ANIMATION: Animace prvního objektu - rotace
        SequentialAnimation on obj0Animation {
            loops: Animation.Infinite
            NumberAnimation { to: 360; duration: 3000; easing.type: Easing.Linear }
            NumberAnimation { to: 0; duration: 0 }
        }

        SequentialAnimation on obj0RotX {
            loops: Animation.Infinite
            NumberAnimation { from: 0; to: 360; duration: 4500; easing.type: Easing.Linear }
        }

        SequentialAnimation on obj0RotZ {
            loops: Animation.Infinite
            NumberAnimation { from: 0; to: 360; duration: 6000; easing.type: Easing.Linear }
        }

        SequentialAnimation on objScale {
            loops: Animation.Infinite
            NumberAnimation { from: 0.0; to: 0.35; duration: 1200; easing.type: Easing.InOutSine }
            NumberAnimation { from: 0.35; to: -0.20; duration: 1200; easing.type: Easing.InOutSine }
            NumberAnimation { from: -0.20; to: 0.0; duration: 1200; easing.type: Easing.InOutSine }
        }
        
        // TODO 14b ANIMATION: Animace druhého objektu - pomalejší rotace
        SequentialAnimation on obj1Animation {
            loops: Animation.Infinite
            NumberAnimation { to: 360; duration: 5000; easing.type: Easing.Linear }
            NumberAnimation { to: 0; duration: 0 }
        }
    }

    // Pozadi pro spodni popisek.
    Rectangle {
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -10
    }

    // Jednoduche tlacitko Quit vlevo nahore.
    Rectangle {
        width: 80
        height: 30
        x: 10
        y: 10
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 10
        border.width: 1
        border.color: "white"

        Text {
            text: qsTr("Quit")
            anchors.centerIn: parent
            color: "black"
        }

        // Oblast pro touch/mouse udalosti.
        MultiPointTouchArea {
            anchors.fill: parent
        }
    }

    // Spodni popisek zobrazeny nad OpenGL scenou.
    Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "OpenGL scéna s QML překryvem - Každý objekt se animuje jinak!"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}
