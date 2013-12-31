import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    // Properties definition
    property alias wordText: label.text
    property string description_text:""
    property alias wordPixelSz: label.font.pixelSize
    property bool info_mode: words_page.info_mode

    // Signals
    signal wordClicked

    height: childrenRect.height
    width:childrenRect.width


    Image {
        id: left_image
        height: text_area.height
        width:sourceSize.width
        source: "qrc:/res/resources/paper_texture_2_left.png"
    }

    Image {
        id:text_area
        width:label.width
        height:label.height
        anchors.left: left_image.right
        source: "qrc:/res/resources/paper_texture_2_middle.png"
        fillMode: Image.TileHorizontally
    }

    Image {
        id: right_image
        height: text_area.height
        width:sourceSize.width
        anchors.left: text_area.right
        source: "qrc:/res/resources/paper_texture_2_right.png"
    }

    ColorOverlay {
        id:overlay
        anchors.fill: root
        source: root
        color: "#00000000"
    }
    // Child elements
    Text {
        id: label
        anchors.left: text_area.left
        font.family: command_font.name
        font.pixelSize: 22
    }

    MouseArea {
        anchors.fill: parent
        onClicked:
        {
            if(info_mode) {
                showMessage(wordText,description_text)
            } else {
                wordClicked()
                overlay.color = manager.current_word_color;
            }
        }
    }

}
