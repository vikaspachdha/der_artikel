import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id:Manager.RESULT_PAGE
    Label {
        id: result_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: result_lbl.horizontalCenter
        lblText: qsTr("Options") + settings.i18n_empty_string
    }

    Column {
        id: result_level_col
        anchors.top: result_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:replay_btn
            width:parent.width
            // score < 0 means no result is produced so far.
            visible: manager.thema_selected && (currentResult.score > -1)
            text_anchors.horizontalCenter: replay_btn.horizontalCenter
            buttonText: qsTr("Replay") + settings.i18n_empty_string
            onActivated: manager.current_page = Manager.WORDS_PAGE
        }

        Button {
            id:stats_btn
            width:parent.width
            text_anchors.horizontalCenter: stats_btn.horizontalCenter
            buttonText: qsTr("Stats") + settings.i18n_empty_string
            onActivated: manager.current_page = Manager.STATS_PAGE
        }
    }
}
