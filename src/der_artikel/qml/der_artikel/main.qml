import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0
import com.vystosi.qmlcomponents 1.0

Image {
    id: rootItem;
    width: 400
    height: 400
    property QtObject color_palette : cp_blue

    source: "qrc:/res/resources/background_texture.png"
    fillMode: Image.Tile

    SoundEffect {
        id: click
        source: "qrc:/res/resources/sounds/click.wav"
        volume: settings.sound_level
    }

    Color_palette_blue {
        id:cp_blue
    }

    Color_palette_night {
        id:cp_night
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

    Blanket {
        id:blanket
        anchors.fill: parent
    }

    Message_bar {
        id: msg_bar
        height: 72
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin:8

        onMsgCompleted: {
            rootItem.enabled = true
            blanket.show = false;
        }
    }



    function showMessage(title,msg,duration,msg_type)
    {
        rootItem.enabled = false
        blanket.show = true;
        msg_bar.showMessage(title,msg,duration,msg_type);// = true
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
}

