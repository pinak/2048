import QtQuick 2.4

Rectangle {
    id: tile
    property string value: ""
    property int tileWidth: 70

    function handleZero(value) {
        if (parseInt(value, 10) === 0) {
            return "";
        }
        return value;
    }

    function setColor(value) {
        if (parseInt(value, 10) === 0) {
            return "lightblue"
        }
        else
            return "steelblue"
    }

    color: setColor(value)
    width: 80
    height: 80
    radius: 10

    Text {
        text: handleZero(value)
        anchors.centerIn: parent
        font.pointSize: 20
        color: "yellow"
    }
}
