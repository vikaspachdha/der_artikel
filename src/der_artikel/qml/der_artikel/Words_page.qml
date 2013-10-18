import QtQuick 2.0

Rectangle {
    id: word_page_root
    anchors.fill: parent
    Flickable
    {
        id: wordsFrame
        anchors.fill: parent
        clip: true
        contentHeight: wordFlow.childrenRect.height
        Flow
        {
            id: wordFlow
            width:wordsFrame.width
            spacing: 6
        }

    }

    function appendWordToFlow(itemText)
    {
        var WordComponent = Qt.createComponent("Word_item.qml");
        if(WordComponent.status == Component.Ready) {
            var WordItem = WordComponent.createObject(wordFlow);
            WordItem.wordText = itemText;
        }

        return WordItem;
    }
}
