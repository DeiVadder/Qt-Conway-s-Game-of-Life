import QtQuick 2.0

Rectangle {
    id:root

    property bool alive: false
    signal clicked();

    border.width: 1
    border.color: "lightgrey"

    color: alive ? "black" : "white"

    MouseArea{
        anchors.fill: parent
        onClicked: /*alive = !alive*/root.clicked()
    }
}
