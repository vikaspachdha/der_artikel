import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0
import com.vystosi.qmlcomponents 1.0
Image {
    id: rootItem;
    width: 400
    height: 400
    clip:true
    source: "qrc:/res/resources/background_texture.png"
    fillMode: Image.Tile
    horizontalAlignment: Image.AlignLeft
    verticalAlignment: Image.AlignTop
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

    Panel_frame {
        id: cmd_panel_frame
        anchors.top: title_item.bottom
        anchors.bottom: parent.bottom
        anchors.left: rootItem.left
        width: 80
    }

//    Rectangle
//    {
//        id: articleFrame
//        anchors.top: title_item.bottom
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        width: childrenRect.width + 4;
//        gradient: Gradient {
//                  GradientStop { position: 0.0; color: "#FFFFFF" }
//                  GradientStop { position: 0.33; color: "#9CAFB8" }
//                  GradientStop { position: 0.66; color: "#9CAFB8" }
//                  GradientStop { position: 1.0; color: "#FFFFFF" }
//              }

//        ExclusiveGroup {
//            id: articleGroup
//        }

//        Button {
//            text: "Home"
//            height: 24
//            anchors{
//                bottom: parent.bottom
//            }
//            onClicked: {
//                manager.showResult();
//                manager.current_page = Manager.HOME_PAGE
//            }
//        }

//        Column {
//            id: articleCol
//            anchors.verticalCenter: parent.verticalCenter
//            spacing: 16
//            RadioButton {
//                id: mannlisch
//                text: "Der"
//                exclusiveGroup: articleGroup
//                checked: true
//                onCheckedChanged: {
//                    if(checked) {
//                        manager.selected_article = 1
//                    }
//                    currentColor = "red"
//                }
//            }
//            RadioButton {
//                text: "Die"
//                exclusiveGroup: articleGroup
//                onCheckedChanged: {
//                    if(checked) {
//                        manager.selected_article = 2
//                    }
//                    currentColor = "pink"
//                }
//            }
//            RadioButton {
//                text: "Das"
//                exclusiveGroup: articleGroup
//                onCheckedChanged: {
//                    if(checked) {
//                        manager.selected_article = 3
//                    }
//                    currentColor = "lightgray"
//                }
//            }
//            RadioButton {
//                text: "None"
//                exclusiveGroup: articleGroup
//                onCheckedChanged: {
//                    if(checked) {
//                        manager.selected_article = 4
//                    }
//                    currentColor = "lightgray"
//                }
//            }

//        }
//    }


    Content_frame
    {
        id: content_frame
        anchors.top: title_item.bottom
        anchors.bottom: rootItem.bottom
        anchors.left: cmd_panel_frame.right
        anchors.right: rootItem.right
    }


    function addWord(itemText)
    {
        var WordItem = content_frame.word_page.appendWordToFlow(itemText)
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

//    DropShadow {
//        anchors.fill: msg_bar
//        horizontalOffset: 4
//        verticalOffset: 8
//        radius: 0
//        spread: 0.3
//        samples: 16
//        color: "#66000000"
//        source: msg_bar
//    }
}

