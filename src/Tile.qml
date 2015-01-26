import QtQuick 2.4

Rectangle {
    id: tile
    property string value: ""
    property int tileWidth: 70

    function handleZero(value) {
        if (parseInt(value, 10) ===0) {
            return "";
        }
        return value;
    }

    color: "orange"
    width: 80
    height: 80

    Text {
        text: handleZero(value)
        font.pointSize: 20
        color: "black"
    }
}
