import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.WORDS_PAGE
    id: word_page_root

    Flickable
    {
        id: wordsFrame
        anchors.fill: word_page_root
        clip: true
        contentHeight: wordFlow.childrenRect.height
        Flow
        {
            id: wordFlow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: 6
        }
    }


    function addWord(word_object,itemText,desc)
    {
        var wordComponent = Qt.createComponent("Word_item.qml");
        if(wordComponent.status == Component.Ready) {
            var wordItem = wordComponent.createObject(wordFlow);
            wordItem.word = word_object;
            wordItem.wordText = itemText;
            wordItem.description_text = desc;
        }

        return wordItem;
    }
}
