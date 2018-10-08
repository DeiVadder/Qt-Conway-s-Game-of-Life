import QtQuick 2.11
import QtQuick.Window 2.11

import QtQuick.Controls 2.2

Window {
    id: root
    visible: true
    width: 800
    height:width * (Gameboard.boardHeight / Gameboard.boardWidth)
    title: qsTr("Game of Life")

    Component.onCompleted:{
//        console.log(Gameboard.cellModel.size)
//        Gameboard.startGame()
    }

    Shortcut{
        sequence: "F5"
        onActivated: Gameboard.running = !Gameboard.running
    }

    GridView{
        id: gameView
        x: 4
        y: 4
        width: parent.width
        height: parent.height

        model: Gameboard.cellModel

        cellWidth: root.width /Gameboard.boardWidth
        cellHeight: root.height/Gameboard.boardHeight


        delegate: Item {
            width: parent.cellWidth
            height: parent.cellHeight

            CellDelegate{
                anchors.centerIn: parent
                width: gameView.cellWidth
                height: gameView.cellHeight
                onClicked:{
                    modelData.alive = !modelData.alive
                }

            alive: modelData.alive
            onAliveChanged: modelData.alive = alive
            }
        }
    }

    Controlls{
        id: controls
        x:root.x+ root.width
        y: root.y
        height: root.height
        width: 400

        visible: true
    }
}
