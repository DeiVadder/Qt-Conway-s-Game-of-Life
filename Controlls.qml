import QtQuick 2.11
import QtQuick.Window 2.11

import QtQuick.Controls 2.2

Window {
    Rectangle{
        id: boradWidth
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 5

        width: parent.width/2

        height: txtWidth.contentHeight * 1.5

        Text{
            id:txtWidth
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: contentWidth

            text: "Board width"

            verticalAlignment: Qt.AlignVCenter
        }
        SpinBox{
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: txtWidth.right

            editable: true

            from: 0
            to: 800

            value: Gameboard.boardWidth
            onValueChanged: Gameboard.boardWidth = value
        }
    }

    Rectangle{
        id: boradHeight
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5

        width: parent.width/2

        height: txtHeight.contentHeight * 1.5

        Text{
            id:txtHeight
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: contentWidth

            text: "Board height"
            verticalAlignment: Qt.AlignVCenter
        }

        SpinBox{
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: txtHeight.right

            editable: true

            from: 0
            to: 800

            value: Gameboard.boardHeight
            onValueChanged: Gameboard.boardHeight = value
        }
    }

    Rectangle{
        id: chanceToBeAlive
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: boradHeight.bottom
        anchors.margins: 5

        height: boradHeight.height

        Text{
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            text: "Chance for a cell to be alive:"
            wrapMode: Text.Wrap
            verticalAlignment: Qt.AlignVCenter
        }

        SpinBox{
            anchors.left: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            from: 0
            to: 100

            editable: true
            value:  Gameboard.chanceToBeAlive
            onValueChanged: Gameboard.chanceToBeAlive = value
        }
    }

    Rectangle{
        id:borderBehaviour
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: chanceToBeAlive.bottom
        height: chanceToBeAlive.height

        anchors.margins: 5

        Text{
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter

            text: "Border behaviour"
        }

        ComboBox{
            anchors.left: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            model: ["Alive","Dead", "Loop"]

            currentIndex: Gameboard.borderBehaviour
            onCurrentIndexChanged:{
                console.log(currentIndex)
                Gameboard.borderBehaviour = currentIndex
            }
        }
    }

    Item {
        id: frameButtons
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: borderBehaviour.bottom
        height: borderBehaviour.height

        anchors.margins: 5

        Button{
            id: btnCreate
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter
            anchors.leftMargin: 20
            anchors.rightMargin: 20


            text: "Create Board"
            onClicked: Gameboard.setupBoard()
        }

        Button{
            id: btnStartStop
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.horizontalCenter
            anchors.leftMargin: 20
            anchors.rightMargin: 20


            text: Gameboard.running ? "Stop" : "Start"
            onClicked: Gameboard.running = !Gameboard.running
        }
    }
}
