import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id: Manager.SETTINGS_PAGE

    Label {
        id: options_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: options_lbl.horizontalCenter
        lblText: qsTr("Options") + settings.i18n_empty_string
    }

    Column {
        id: settings_btn_col
        anchors.top: options_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:language_btn
            width:parent.width
            text_anchors.horizontalCenter: language_btn.horizontalCenter
            isDown: settings_page_instance.sub_page_type === SettingsPage.LANGUAGE
            buttonText: qsTr("Language") + settings.i18n_empty_string
            onActivated: settings_page_instance.sub_page_type = SettingsPage.LANGUAGE
        }

        Button {
            id:sound_btn
            visible:false
            width:parent.width
            text_anchors.horizontalCenter: sound_btn.horizontalCenter
            isDown: settings_page_instance.sub_page_type === SettingsPage.SOUND
            buttonText: qsTr("Sound") + settings.i18n_empty_string
            onActivated: showMessage(qsTr("Sorry"), qsTr("This feature is not available"),1200)
        }

        Button {
            id:color_theme_btn
            width:parent.width
            text_anchors.horizontalCenter: color_theme_btn.horizontalCenter
            isDown: settings_page_instance.sub_page_type === SettingsPage.COLOR_THEME
            buttonText: qsTr("Color theme") + settings.i18n_empty_string
            onActivated: settings_page_instance.sub_page_type = SettingsPage.COLOR_THEME
        }

        Button {
            id:game_play_btn
            width:parent.width
            text_anchors.horizontalCenter: game_play_btn.horizontalCenter
            isDown: settings_page_instance.sub_page_type === SettingsPage.GAME_PLAY
            buttonText: qsTr("Game") + settings.i18n_empty_string
            onActivated: settings_page_instance.sub_page_type = SettingsPage.GAME_PLAY
        }
    }
}
