import QtQuick 2.0
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

    ColorPaletteBlue {
        id:cp_blue
    }

    FontLoader {
        id: custom_regular
        source: "qrc:/res/resources/fonts/custom_regular.ttf"
    }

    FontLoader {
        id: custom_command
        source: "qrc:/res/resources/fonts/custom_command.ttf"
    }

    Title_frame{
        id: title_frame
        anchors{
            top: parent.top
            left:parent.left
            leftMargin:8
            right:parent.right
            rightMargin: 8
        }
    }

    Panel_frame {
        id: panel_frame
        anchors{
            top: title_frame.bottom
            topMargin: 6
            left:parent.left
            bottom:command_frame.top
            bottomMargin: 6
        }
    }

    Command_frame {
        id:command_frame
        width:100
        height:80
        anchors{
            left:parent.left
            leftMargin: 8
            bottom:parent.bottom
            bottomMargin: 6
        }
    }

    Content_frame
    {
        id: content_frame
        anchors.top: title_frame.bottom
        anchors.bottom: rootItem.bottom
        anchors.left: parent.left
        anchors.leftMargin: 118
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
        anchors.bottomMargin:8
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
    Component.onCompleted: {
        manager.current_page = Manager.HOME_PAGE
    }

    function articleText(article) {
        var text;
        switch(article) {
        case Article.DER:
            text = "Der"
            break
        case Article.DIE:
            text = "Die"
            break
        case Article.DAS:
            text = "Das"
            break;
        default:
            text = ""
            break;
        }
        return text;
    }
}

