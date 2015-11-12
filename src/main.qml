import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Window {
    id: main
    visible: true
    height: 360
    width: 360

    Rectangle {
        id: gameBoard
        color: "grey"
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

        ColumnLayout {
            spacing: 5
            anchors.fill: parent

            Label {
                text: "Score: " + game.score
                color: "darkgrey"
                font.pixelSize: 22
            }

            Grid {
                rows: 4
                columns: 4
                spacing: 4

                Layout.alignment: Qt.AlignHCenter

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
