import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0

Item {
    id: rootItem;
    width: 360
    height: 360

    property color currentColor
    Title_bar {
        id: title_item
        height: rootItem.height*0.2
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Rectangle
    {
        id: articleFrame
        anchors.top: title_item.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: childrenRect.width + 4;
        gradient: Gradient {
                  GradientStop { position: 0.0; color: "#FFFFFF" }
                  GradientStop { position: 0.33; color: "#9CAFB8" }
                  GradientStop { position: 0.66; color: "#9CAFB8" }
                  GradientStop { position: 1.0; color: "#FFFFFF" }
              }

        ExclusiveGroup {
            id: articleGroup
        }

        Button {
            text: "Show Result"
            height: 24
            anchors{
                bottom: parent.bottom
            }
            onClicked: {
                manager.showResult();
                showMessage();
            }
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


    Rectangle
    {
        id: wordsFrame
        anchors.top: title_item.bottom
        anchors.bottom: rootItem.bottom
        anchors.left: articleFrame.right
        anchors.right: rootItem.right
        anchors.margins:4
        Words_page {
            id: words_page_item
            anchors.fill: parent
        }
    }


    function addWord(itemText)
    {
        var WordItem = words_page_item.appendWordToFlow(itemText)
        return WordItem;
    }

    function showMessage()
    {
        msg_bar.animate = true
    }

    Message_bar {
        id: msg_bar
        height: parent.height * 0.2
        color:"red"

        anchors.left: parent.left
        anchors.right: parent.right
    }

    DropShadow {
        anchors.fill: msg_bar
        horizontalOffset: 4
        verticalOffset: 8
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: msg_bar
    }
}

