import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id:Manager.HELP_PAGE

    Label {
        id: help_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: help_lbl.horizontalCenter
        lblText: qsTr("Topics") + settings.i18n_empty_string
    }

    Column {
        id: help_btn_col
        anchors.top: help_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 4

        Button {
            id:gen_btn
            width:parent.width
            text_anchors.horizontalCenter: gen_btn.horizontalCenter
            buttonText: qsTr("General") + settings.i18n_empty_string
            onActivated: help_page_instance.sub_page_type = HelpPage.GENERAL
        }

        Button {
            id:rules_btn
            width:parent.width
            text_anchors.horizontalCenter: rules_btn.horizontalCenter
            buttonText: qsTr("Rules") + settings.i18n_empty_string
            onActivated: help_page_instance.sub_page_type = HelpPage.RULES
        }

        Button {
            id:score_btn
            width:parent.width
            text_anchors.horizontalCenter: score_btn.horizontalCenter
            buttonText: qsTr("Scoring") + settings.i18n_empty_string
            onActivated: help_page_instance.sub_page_type = HelpPage.SCORING
        }

        Button {
            id:other_btn
            width:parent.width
            text_anchors.horizontalCenter: other_btn.horizontalCenter
            buttonText: qsTr("Contact") + settings.i18n_empty_string
            onActivated: help_page_instance.sub_page_type = HelpPage.OTHERS
        }

    }

}
