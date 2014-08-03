import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0
import QtQuick.Window 2.1
import QtMultimedia 5.1

Window{
    id:main
    width: 640
    height: 480
    minimumHeight:480
    minimumWidth: 640
    visible: true
    title:"Der Artikel - " + Qt.application.version

    property QtObject color_palette : cp_blue

    // Text sizes
    property int heading1Size:16
    property int heading2Size:14
    property int commandTextSize : 14
    property int subCommandTextSize : 11
    property int normalTextSize : 14
    property int nounTextSize: 24
    property var startup_screen


    // Color palettes
    Color_palette_blue {
        id:cp_blue
    }

    Color_palette_night {
        id:cp_night
    }

    Color_palette_orange {
        id:cp_orange
    }

    // Fonts
    FontLoader {
        id: title_font
        source: "qrc:/res/resources/fonts/custom_regular.ttf"
    }

    FontLoader {
        id: regular_font
        source: "qrc:/res/resources/fonts/akshar.ttf"
    }

    // Sounds
    SoundEffect {
        id:coinSnd
        source:"qrc:/res/resources/sounds/coin.wav"
    }

    SoundEffect {
        id:clickSnd
        source:"qrc:/res/resources/sounds/click.wav"
    }

    SoundEffect {
        id:derSnd
        source:"qrc:/res/resources/sounds/der.wav"
    }

    SoundEffect {
        id:dieSnd
        source:"qrc:/res/resources/sounds/die.wav"
    }

    SoundEffect {
        id:dasSnd
        source:"qrc:/res/resources/sounds/das.wav"
    }

    // Children
    Image {
        id: rootItem;
        anchors.fill: parent
        source: color_palette.root_background
        fillMode: Image.Tile

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

    }

    Message_bar {
        id: msg_bar
        anchors.fill: parent
    }

    Connections {
        target:appUpdater
        onUpdateStateChanged: {
            switch(update_state) {
                case AppUpdater.UPDATE_STARTED:
                    messageBarInstance.showMsgAsync(qsTr("App update..."),"");
                    break;

                case AppUpdater.UPDATE_NOT_AVAILABLE:
                    messageBarInstance.closeMsg();
                    messageBarInstance.showMsg(qsTr("No Update Available."),
                                               qsTr("You are running latest version."),
                                               "",
                                               qsTr("Ok"));
                    break;
                case AppUpdater.UPDATE_ERROR:
                case AppUpdater.UPDATE_ABORTED:
                    messageBarInstance.closeMsg();
                    messageBarInstance.showMsg(qsTr("Update Error."),
                                               qsTr("Please try later."),
                                               "",
                                               qsTr("Ok"));
                    break;
                case AppUpdater.UPDATE_AVAILABLE:
                    messageBarInstance.closeMsg()
                    var response = messageBarInstance.showMsg(qsTr("Update available."),
                                               qsTr("Do you want to download the latest version?"),
                                               qsTr("Yes"),
                                               qsTr("No"));
                    if(response === MessageBar.ACCEPTED) {
                        appUpdater.startUpdate();
                    } else {
                        appUpdater.abortUpdate();
                    }

                    break;
            }
        }

        onUpdateProgress: {
            msg_bar.message_txt = info;
            msg_bar.setProgress(progress)
        }
    }

    Connections {
        target:themaUpdater
        onUpdateStateChanged: {
            if(!manager.is_starting_up) {
                switch(update_state) {

                    case ThemaUpdater.UPDATE_STARTED:
                        messageBarInstance.showMsgAsync(qsTr("Updating thema"),"");
                        break;

                    case ThemaUpdater.UPDATE_FINISHED:
                        messageBarInstance.closeMsg()
                        break;
                }
            }
        }

        onUpdateProgress: {
            if(!manager.is_starting_up) {
                msg_bar.message_txt = info;
                msg_bar.setProgress(progress)
            }
        }
    }

    Component.onCompleted: {
        manager.current_page = Manager.HOME_PAGE

        // Destroyed when starup finishes.
        var startup_component = Qt.createComponent("Startup_screen.qml");
        if(startup_component.status === Component.Ready) {
            startup_screen = startup_component.createObject(rootItem);
        }
    }

    function getMessageBar()
    {
        return msg_bar;
    }

    function showMessage(title,msg,duration,msg_type)
    {
        msg_bar.showMessage(title,msg,duration,msg_type);
    }

    function closeMessage()
    {
        msg_bar.closeMessage()
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

    function removeStartupScreen()
    {
        startup_screen.hideStartup();
    }
}


