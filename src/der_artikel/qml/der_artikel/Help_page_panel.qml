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
        text_h_alignment: Text.AlignHCenter
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
        spacing: 6

        Button {
            id:gen_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("General") + settings.i18n_empty_string
            isDown:help_page_instance.sub_page_type === HelpPage.GENERAL
            onActivated: help_page_instance.sub_page_type = HelpPage.GENERAL
        }

        Button {
            id:rules_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Rules") + settings.i18n_empty_string
            isDown:help_page_instance.sub_page_type === HelpPage.RULES
            onActivated: help_page_instance.sub_page_type = HelpPage.RULES
        }

        Button {
            id:score_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Scoring") + settings.i18n_empty_string
            isDown:help_page_instance.sub_page_type === HelpPage.SCORING
            onActivated: help_page_instance.sub_page_type = HelpPage.SCORING
        }

        Button {
            id:other_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Contact") + settings.i18n_empty_string
            isDown:help_page_instance.sub_page_type === HelpPage.OTHERS
            onActivated: help_page_instance.sub_page_type = HelpPage.OTHERS
        }

    }

}
