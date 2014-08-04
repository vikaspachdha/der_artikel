//******************************************************************************
/*! \file 
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
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

        Item{
            id: title_frame
            height: 76
            anchors{
                top: parent.top
                left:parent.left
                leftMargin:8
                right:parent.right
                rightMargin: 8
            }
        }

        Item {
            id: panel_frame
            width:108
            anchors{
                top: title_frame.bottom
                topMargin: 6
                left:parent.left
                bottom:parent.bottom
                bottomMargin: 92
            }
        }

        Item
        {
            id: content_frame
            clip:true
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

    Connections{
        target: manager
        onCurrentPageChanged: {
            switch(manager.current_page) {
            case Manager.HOME_PAGE:
                createDynamicObject("Home_page.qml", content_frame);
                createDynamicObject("Home_page_panel.qml", panel_frame);
                createDynamicObject("Home_page_title.qml", title_frame);
                break;
            case Manager.WORDS_PAGE:
                createDynamicObject("Words_page.qml", content_frame);
                createDynamicObject("Words_page_panel.qml", panel_frame);
                createDynamicObject("Words_page_title.qml", title_frame);
                break;
            case Manager.THEMA_PAGE:
                createDynamicObject("Thema_page.qml", content_frame);
                createDynamicObject("Thema_page_panel.qml", panel_frame);
                createDynamicObject("Thema_page_title.qml", title_frame);
                break;
            case Manager.RESULT_PAGE:
                createDynamicObject("Result_page.qml", content_frame);
                createDynamicObject("Result_page_panel.qml", panel_frame);
                createDynamicObject("Result_page_title.qml", title_frame);
                break;
            case Manager.HELP_PAGE:
                createDynamicObject("Help_page.qml", content_frame);
                createDynamicObject("Help_page_panel.qml", panel_frame);
                createDynamicObject("Help_page_title.qml", title_frame);
                break;
            case Manager.STATS_PAGE:
                createDynamicObject("Stats_page.qml", content_frame);
                createDynamicObject("Stats_page_panel.qml", panel_frame);
                createDynamicObject("Stats_page_title.qml", title_frame);
                break;
            case Manager.SETTINGS_PAGE:
                createDynamicObject("Settings_page.qml", content_frame);
                createDynamicObject("Settings_page_panel.qml", panel_frame);
                createDynamicObject("Settings_page_title.qml", title_frame);
                break;
            case Manager.ABOUT_PAGE:
                createDynamicObject("About_page.qml", content_frame);
                createDynamicObject("About_page_panel.qml", panel_frame);
                createDynamicObject("About_page_title.qml", title_frame);
                break;
            }
        }
    }

    Component.onCompleted: {
        // Destroyed when starup finishes.
        startup_screen = createDynamicObject("Startup_screen.qml",rootItem);
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
        createDynamicObject("Command_frame.qml",rootItem);
        startup_screen.hideStartup();
    }

    function createDynamicObject(qml,parent_object) {
        var new_component = Qt.createComponent(qml,parent_object);
        if (new_component.status === Component.Ready) {
            var new_object = new_component.createObject(parent_object);
            if (new_object == null) {
                console.log("Error creating object from : ", qml);
            }
            return new_object;
        } else if (new_component.status === Component.Error) {
            console.log("Error loading component:", new_component.errorString());
        }
    }
}


