import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Image {
    id: rootItem;
    width: 480
    height: 400
    property QtObject color_palette : cp_night

    source: color_palette.root_background
    fillMode: Image.Tile

    Color_palette_blue {
        id:cp_blue
    }

    Color_palette_night {
        id:cp_night
    }

    Color_palette_orange {
        id:cp_orange
    }

    FontLoader {
        id: custom_regular
        source: "qrc:/res/resources/fonts/custom_regular.ttf"
    }

    FontLoader {
        id: command_font
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
        anchors.leftMargin: 112
        anchors.right: rootItem.right
        anchors.rightMargin: 4
    }


    function addWord(itemText, desc)
    {
        var WordItem = content_frame.word_page.addWord(itemText, desc)
        return WordItem;
    }

    Message_bar {
        id: msg_bar
        anchors.fill: parent
        onMsgCompleted: {
            rootItem.enabled = true
        }
    }

    function showMessage(title,msg,duration,msg_type)
    {
        rootItem.enabled = false
        msg_bar.showMessage(title,msg,duration,msg_type);
    }

    function closeMessage()
    {
        msg_bar.closeMessage()
    }

    Component.onCompleted: {
        manager.current_page = Manager.HOME_PAGE

        // self destroying statrtup screen
        var startup_component = Qt.createComponent("Startup_screen.qml");
        if(startup_component.status === Component.Ready) {
            startup_component.createObject(rootItem);
        }
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

    function colorOpacity(color, opacity) {
        var hex_opacity = parseInt((opacity * 255),10).toString(16)
        var new_color = color
        if(color.length > 7) {
            new_color = "#" + hex_opacity + color.substring(3)
        } else {
            new_color = "#" + hex_opacity + color.substring(1)
        }
        return new_color
    }
}

