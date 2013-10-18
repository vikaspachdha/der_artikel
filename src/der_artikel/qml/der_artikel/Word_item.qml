import QtQuick 2.0

Rectangle {

    // Properties definition
    property alias wordText: label.text
    property int wordPtSz: 12
    property color bkColor: "gray";

    // Signals
    signal wordClicked

    // Properties initilization
    color: bkColor
    radius: 8.0

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
            wordClicked()
            color = manager.current_word_color;
        }
    }

}
