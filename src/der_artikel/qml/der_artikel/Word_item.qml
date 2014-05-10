import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Item {
    id: root
    // Properties definition
    property alias wordText: noun_item.text
    property string description_text:""
    property bool info_mode: words_page.info_mode
    property QtObject word

    // Signals
    signal wordClicked

    height: childrenRect.height
    width:childrenRect.width

    Noun_Item {
        id:noun_item
        article: word == null ? Article.INVALID : word.user_article
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            wordClicked()
            switch(word.user_article) {
                case Article.DER:derSnd.play();break;
                case Article.DIE:dieSnd.play();break;
                case Article.DAS:dasSnd.play();break;
            }
        }
    }
}
