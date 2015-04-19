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
        // This selects a color for for tile according to its value
        value = parseInt(value, 10);
        if (value === 0) {
            return "lightblue";
        }
        else {
            var colorAr = ["steelblue", "green", "orange", "brown", "red", "pink", "voilet", "indigo", "maroon", "magenta"];
            return colorAr[(Math.log(value)/Math.log(2) - 1) % colorAr.length];
        }
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
