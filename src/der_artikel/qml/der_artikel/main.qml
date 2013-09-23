import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Rectangle {
    width: 360
    height: 360

    Rectangle
    {
        id: articleFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins:4
        width: 80;

        ExclusiveGroup {
            id: articleGroup
        }

        Column {
            anchors.fill: parent
            spacing: 8
            RadioButton {
                text: "Der"
                exclusiveGroup: articleGroup
            }
            RadioButton {
                text: "Die"
                exclusiveGroup: articleGroup
            }
            RadioButton {
                text: "Das"
                exclusiveGroup: articleGroup
            }
        }
    }

    Flickable
    {
        id: wordsFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: articleFrame.right
        anchors.right: parent.right
        anchors.margins:4
        contentHeight: wordFlow.height
        Flow
        {
            id: wordFlow
            anchors.fill: parent
            spacing: 6
        }
    }

    function addWord(itemText)
    {
        var WordComponent = Qt.createComponent("WordItem.qml");
        if(WordComponent.status == Component.Ready) {
            var WordItem = WordComponent.createObject(wordFlow);
            WordItem.wordText = itemText;
        }

        return WordItem;
    }

    Component.onCompleted:
    {
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
        addWord("Wohnung")
        addWord("Hause")
        addWord("Bleistift")
        addWord("Kuli")
    }

}

