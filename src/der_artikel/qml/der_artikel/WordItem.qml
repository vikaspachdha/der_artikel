import QtQuick 2.0

Rectangle {

    // Properties definition
    property alias wordText: label.text
    property int wordPtSz: 12
    property color bkColor: "gray";
    property bool selected: false

    // Signals
    signal wordClicked

    // Properties initilization
    color: bkColor
    radius: 8.0

    onSelectedChanged:
    {
        color = manager.current_word_color;
    }

    // Child elements
    Text {
        id: label
        anchors.centerIn: parent
        font.pointSize : wordPtSz
        Component.onCompleted:
        {
            parent.width = paintedWidth +4
            parent.height = paintedHeight +4
        }
        onTextChanged:
        {
            parent.width = paintedWidth +4
            parent.height = paintedHeight +4
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked:
        {
            parent.selected = parent.selected == true ? false: true;
        }
    }

}
