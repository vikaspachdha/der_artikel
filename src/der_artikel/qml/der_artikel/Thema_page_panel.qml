import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
Page_panel
{
    page_id: Manager.THEMA_PAGE
    Label {
        id: level_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: level_lbl.horizontalCenter
        lblText: qsTr("Game Level") + settings.i18n_empty_string
    }
    Column {
        id: game_level_col
        anchors.top: level_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 4


        Button {
            id:easy_btn
            width:parent.width
            text_anchors.horizontalCenter: easy_btn.horizontalCenter
            isDown: manager.game_level === Manager.EASY
            buttonText: qsTr("Easy") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.EASY
        }

        Button {
            id:moderate_btn
            width:parent.width
            text_anchors.horizontalCenter: moderate_btn.horizontalCenter
            isDown: manager.game_level === Manager.MODERATE
            buttonText: qsTr("Moderate") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.MODERATE
        }

        Button {
            id:expert_btn
            width:parent.width
            text_anchors.horizontalCenter: expert_btn.horizontalCenter
            isDown: manager.game_level === Manager.EXPERT
            buttonText: qsTr("Expert") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.EXPERT
        }

    }

    Command_item
    {
        id: start_cmd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        enabled: themaModel.selection_state===ThemaModel.SINGLE_SELECTION
        cmd_text: qsTr("Start") + settings.i18n_empty_string
        icon_name: "start"
        onCommandActivated: {
            manager.current_page = Manager.WORDS_PAGE
        }
    }
}
