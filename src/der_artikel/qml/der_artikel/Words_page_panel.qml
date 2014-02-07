import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page_panel {
    page_id:Manager.WORDS_PAGE
    Label {
        id: level_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: level_lbl.horizontalCenter
        lblText: qsTr("Article")
    }

    Column {
        id: game_level_col
        anchors.top: level_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        enabled: manager.game_level !== Manager.PRACTICE
        spacing: 4

        Button {
            id:der_btn
            width:parent.width
            text_anchors.horizontalCenter: der_btn.horizontalCenter
            isDown: words_page.selected_article === Article.DER
            buttonText: qsTr("Der") + settings.i18n_empty_string
            onActivated:  {
                words_page.info_mode = false
                words_page.selected_article = Article.DER
            }
        }

        Button {
            id:die_btn
            width:parent.width
            text_anchors.horizontalCenter: die_btn.horizontalCenter
            isDown: words_page.selected_article === Article.DIE
            buttonText: qsTr("Die") + settings.i18n_empty_string
            onActivated:  {
                words_page.info_mode = false
                words_page.selected_article = Article.DIE
            }
        }

        Button {
            id:das_btn
            width:parent.width
            text_anchors.horizontalCenter: das_btn.horizontalCenter
            isDown: words_page.selected_article === Article.DAS
            buttonText: qsTr("Das") + settings.i18n_empty_string
            onActivated: {
                words_page.info_mode = false
                words_page.selected_article = Article.DAS
            }
        }

        Button {
            id:na_btn
            width:parent.width
            text_anchors.horizontalCenter: na_btn.horizontalCenter
            isDown: words_page.info_mode === true
            buttonText: qsTr("Info") + settings.i18n_empty_string
            onActivated: {
                words_page.selected_article = Article.NA
                words_page.info_mode = true
            }
        }

    }


    Command_item
    {
        id: finish_cmd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        enabled: manager.game_level !== Manager.PRACTICE
        cmd_text: qsTr("Finish") + settings.i18n_empty_string
        icon_name: "finish"
        onCommandActivated: {
            manager.current_page = Manager.RESULT_PAGE
        }
    }

}
