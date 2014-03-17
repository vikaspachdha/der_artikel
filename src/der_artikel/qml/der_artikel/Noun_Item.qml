import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
Item {
    id: item_root
    property int article: Article.INVALID
    property alias text: label.text
    height: childrenRect.height
    width:childrenRect.width
    Image {
        id: left_image
        height: text_area.height
        width:sourceSize.width
        source: {
            switch(item_root.article) {
            case Article.DER:return "qrc:/res/resources/paper_texture_left_der.png";
            case Article.DIE:return "qrc:/res/resources/paper_texture_left_die.png";
            case Article.DAS:return "qrc:/res/resources/paper_texture_left_das.png";
            default:return "qrc:/res/resources/paper_texture_left.png";
            }
        }
    }

    Image {
        id:text_area
        width:label.width
        height:label.height
        anchors.left: left_image.right
        source: {
            switch(item_root.article) {
            case Article.DER:return "qrc:/res/resources/paper_texture_middle_der.png";
            case Article.DIE:return "qrc:/res/resources/paper_texture_middle_die.png";
            case Article.DAS:return "qrc:/res/resources/paper_texture_middle_das.png";
            default:return "qrc:/res/resources/paper_texture_middle.png";
            }
        }
        fillMode: Image.TileHorizontally
    }

    Image {
        id: right_image
        height: text_area.height
        width:sourceSize.width
        anchors.left: text_area.right
        source: {
            switch(item_root.article) {
            case Article.DER:return "qrc:/res/resources/paper_texture_right_der.png";
            case Article.DIE:return "qrc:/res/resources/paper_texture_right_die.png";
            case Article.DAS:return "qrc:/res/resources/paper_texture_right_das.png";
            default:return "qrc:/res/resources/paper_texture_right.png";
            }
        }
    }

    Text {
        id: label
        anchors.left: text_area.left
        font.family: command_font.name
        font.pixelSize: 22
    }
}
