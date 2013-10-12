import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Item {
    id: rootItem;
    width: 360
    height: 360

    property color currentColor
    Header {
        id: headerItem
        height: 40
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Rectangle
    {
        id: articleFrame
        anchors.top: headerItem.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: childrenRect.width + 8;
        gradient: Gradient {
                  GradientStop { position: 0.0; color: "#8E9CA4" }
                  GradientStop { position: 0.10; color: "#9CAFB8" }
                  GradientStop { position: 0.90; color: "#9CAFB8" }
                  GradientStop { position: 1.0; color: "#8E9CA4" }
              }

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
                    if(checked) {
                        manager.selected_article = 1
                    }
                    currentColor = "red"
                }
            }
            RadioButton {
                text: "Die"
                exclusiveGroup: articleGroup
                onCheckedChanged: {
                    if(checked) {
                        manager.selected_article = 2
                    }
                    currentColor = "pink"
                }
            }
            RadioButton {
                text: "Das"
                exclusiveGroup: articleGroup
                onCheckedChanged: {
                    if(checked) {
                        manager.selected_article = 3
                    }
                    currentColor = "lightgray"
                }
            }
            RadioButton {
                text: "None"
                exclusiveGroup: articleGroup
                onCheckedChanged: {
                    if(checked) {
                        manager.selected_article = 4
                    }
                    currentColor = "lightgray"
                }
            }

        }
    }



    Flickable
    {
        id: wordsFrame
        anchors.top: headerItem.bottom
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

