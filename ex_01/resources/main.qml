import QtQuick 2.15
import OpenGLUnderQML 1.0
import "components"

Item {
    width: 800
    height: 600

    // ── Render Area ─────────────────────────────────────────────────────────
    OpenGLScene {
        id: openglScene

        // Object A: movement in X/Y/Z (single phase => perfectly continuous motion).
        property real movePhase: 0.0

        onMovePhaseChanged: {
            objMoveX = 0.9 * Math.sin(movePhase)
            objMoveY = 0.6 * Math.sin(movePhase * 1.2)
            objMoveZ = 0.8 * Math.cos(movePhase * 0.7)
        }

        // Object B: chained rotation X -> Y -> Z.
        SequentialAnimation {
            loops: Animation.Infinite
            running: true

            NumberAnimation { target: openglScene; property: "obj0RotX"; from: 0; to: 360; duration: 1200; easing.type: Easing.Linear }
            NumberAnimation { target: openglScene; property: "obj0RotX"; to: 0; duration: 0 }
            NumberAnimation { target: openglScene; property: "obj0Animation"; from: 0; to: 360; duration: 1200; easing.type: Easing.Linear }
            NumberAnimation { target: openglScene; property: "obj0Animation"; to: 0; duration: 0 }
            NumberAnimation { target: openglScene; property: "obj0RotZ"; from: 0; to: 360; duration: 1200; easing.type: Easing.Linear }
            NumberAnimation { target: openglScene; property: "obj0RotZ"; to: 0; duration: 0 }
        }

        // Object C: scale in/out.
        SequentialAnimation on objScale {
            NumberAnimation { from: 0.0; to: 0.45; duration: 1200; easing.type: Easing.InOutSine }
            NumberAnimation { from: 0.45; to: -0.25; duration: 1200; easing.type: Easing.InOutSine }
            NumberAnimation { from: -0.25; to: 0.0; duration: 1200; easing.type: Easing.InOutSine }
            loops: Animation.Infinite
            running: true
        }

        // Object D: linear movement.
        SequentialAnimation on objLinearX {
            NumberAnimation { from: -1.5; to: 1.5; duration: 2500; easing.type: Easing.Linear }
            NumberAnimation { from: 1.5; to: -1.5; duration: 2500; easing.type: Easing.Linear }
            loops: Animation.Infinite
            running: true
        }

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - controlPanel.height
    }

    // ── Header ──────────────────────────────────────────────────────────────
    Text {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 20
        text: "Test template"
        color: "#F47A00"
        font.pixelSize: 18
        font.bold: true
    }

    ControlBtn {
        text: "Quit"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        width: 72
        onClicked: {
            if (openglScene.window) {
                openglScene.window.close()
            } else {
                Qt.quit()
            }
        }
    }

    // ── Control Panel ───────────────────────────────────────────────────────
    Rectangle {
        id: controlPanel
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 190
        color: "#1a1a1a"

        Column {
            anchors.centerIn: parent
            spacing: 14

            Row {
                spacing: 10
                Text {
                    text: "Camera"
                    color: "#F47A00"
                    font.pixelSize: 18
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                ControlBtn { text: "ISO"; onClicked: openglScene.cameraView = 0 }
                ControlBtn { text: "FR";  onClicked: openglScene.cameraView = 1 }
                ControlBtn { text: "SD";  onClicked: openglScene.cameraView = 2 }
                ControlBtn { text: "TOP"; onClicked: openglScene.cameraView = 3 }
                ControlBtn { text: "-";   onClicked: openglScene.cameraZoom = openglScene.cameraZoom + 0.1 }
                ControlBtn { text: "+";   onClicked: openglScene.cameraZoom = openglScene.cameraZoom - 0.1 }
            }

            Row {
                spacing: 10
                Text {
                    text: "Nudge XYZ"
                    color: "#F47A00"
                    font.pixelSize: 18
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                ControlBtn { text: "X-"; onClicked: openglScene.objMoveX -= 0.5 }
                ControlBtn { text: "X+"; onClicked: openglScene.objMoveX += 0.5 }
                ControlBtn { text: "Y-"; onClicked: openglScene.objMoveY -= 0.5 }
                ControlBtn { text: "Y+"; onClicked: openglScene.objMoveY += 0.5 }
                ControlBtn { text: "Z-"; onClicked: openglScene.objMoveZ -= 0.5 }
                ControlBtn { text: "Z+"; onClicked: openglScene.objMoveZ += 0.5 }
            }
        }
    }
}
