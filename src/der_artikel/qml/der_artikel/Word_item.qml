import QtQuick 2.0
//import QtGraphicalEffects 1.0
import com.vystosi.qmlcomponents 1.0

Item {
    id: root
    // Properties definition
    property alias wordText: label.text
    property string description_text:""
    property alias wordPixelSz: label.font.pixelSize
    property bool info_mode: words_page.info_mode
    property QtObject word
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

//    ColorOverlay {
//        id:overlay
//        anchors.fill: root
//        source: root
//        color: getArticleColor(word == null ? Article.INVALID :word.user_article)
//    }
    // Child elements
    Text {
        id: label
        anchors.left: text_area.left
        font.family: command_font.name
        font.pixelSize: 22
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(info_mode) {
                showMessage(wordText,description_text,settings.word_msg_time)
            } else {
                wordClicked()
                //overlay.color = getArticleColor(words_page.selected_article)
            }
        }
    }

    function getArticleColor(article) {
        switch(article) {
            case Article.DER:return colorOpacity(color_palette.color_der,0.4);
            case Article.DIE:return colorOpacity(color_palette.color_die,0.4);
            case Article.DAS:return colorOpacity(color_palette.color_das,0.4);
            default:return "#00000000";
        }
    }

}
