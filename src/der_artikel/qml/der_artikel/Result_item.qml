import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    property alias left_text: incorrect_noun.text
    property alias right_text: correct_noun.text
    property alias correct_article:correct_noun.article
    width:parent.width

    Item {
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        height:parent.height
        Noun_Item {
            id:incorrect_noun
            anchors.right: parent.right
            anchors.rightMargin: 4
            article: Article.INVALID
        }
    }

    Item {
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        height:parent.height
        Noun_Item {
            id:correct_noun
            anchors.left: parent.left
            anchors.leftMargin: 4
        }
    }

}
