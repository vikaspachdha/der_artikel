import QtQuick 2.0

Rectangle {
    id: word_page_root

    Flickable
    {
        id: wordsFrame
        anchors.fill: word_page_root
        clip: true
        contentHeight: wordFlow.childrenRect.height
    }

    Flow
    {
        id: wordFlow
        anchors.left: wordsFrame.left
        anchors.right: wordsFrame.right
        anchors.top: wordsFrame.top
        spacing: 6
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
