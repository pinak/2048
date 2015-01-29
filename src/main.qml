import QtQuick 2.4
import QtQuick.Window 2.0

Window {
    id: main
    visible: true
    height: 360
    width: 360

    Rectangle {
        color: "yellow"
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_Up:
                    game.moveUp();
                    break;
                case Qt.Key_Down:
                    game.moveDown();
                    break;
                case Qt.Key_Left:
                    game.moveLeft();
                    break;
                case Qt.Key_Right:
                    game.moveRight();
                    break;
            }
        }

        Rectangle {
            id: gameBoard
            anchors.fill: parent
            color: "grey"

            Grid {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                rows: 4
                columns: 4
                spacing: 4

                Repeater {
                    id: boardRepeater
                    model: game
                    delegate: Tile {
                        value: display
                        tileWidth: gameBoard / 4
                    }
                }
            }
        }
    }
}
