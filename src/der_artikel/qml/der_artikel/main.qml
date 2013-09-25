import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Item {
    id: rootItem;
    width: 360
    height: 360

    property color currentColor
    Rectangle
    {
        id: articleFrame
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: childrenRect.width + 8;
        color:"lightblue"

        ExclusiveGroup {
            id: articleGroup
        }


        Column {
            id: articleCol
            anchors.verticalCenter: parent.verticalCenter
            spacing: 16
            RadioButton {
                id: mannlisch
                text: "Der"
                exclusiveGroup: articleGroup
                checked: true
                onCheckedChanged: {
                    currentColor = "red"
                }
            }
            RadioButton {
                text: "Die"
                exclusiveGroup: articleGroup
                onCheckedChanged: {
                    currentColor = "pink"
                }
            }
            RadioButton {
                text: "Das"
                exclusiveGroup: articleGroup
                onCheckedChanged: {
                    currentColor = "lightgray"
                }
            }
        }
    }



    Flickable
    {
        id: wordsFrame
        anchors.top: rootItem.top
        anchors.bottom: rootItem.bottom
        anchors.left: articleFrame.right
        anchors.right: rootItem.right
        anchors.margins:4
        clip: true
        contentHeight: wordFlow.childrenRect.height
        Flow
        {
            id: wordFlow
            width:wordsFrame.width
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
}

