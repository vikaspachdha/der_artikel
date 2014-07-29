import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id:Manager.ABOUT_PAGE

    Label {
        id: info_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Info") + settings.i18n_empty_string
    }

    Column {
        id: about_level_col
        anchors.top: info_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:about_btn
            width:parent.width
            buttonText:qsTr("About") +settings.i18n_empty_string
            text_h_alignment: Text.AlignHCenter
            onActivated: {
                about_page_instance.sub_page_type = AboutPage.ABOUT
            }
        }
        Button {
            id:license_btn
            width:parent.width
            buttonText:qsTr("License") +settings.i18n_empty_string
            text_h_alignment: Text.AlignHCenter
            onActivated: {
                about_page_instance.sub_page_type = AboutPage.LICENSE
            }
        }
    }

    Label {
        id: option_lbl
        anchors.top: about_level_col.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Update") + settings.i18n_empty_string
    }

    Column {
        id: update_level_col
        anchors.top: option_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6
        Button {
            id:replay_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("App") + settings.i18n_empty_string
            onActivated: {
                appUpdater.checkUpdate();
            }
        }

        Button {
            id:update_thema_btn
            width:parent.width
            buttonText:qsTr("Themas") +settings.i18n_empty_string
            text_h_alignment: Text.AlignHCenter
            onActivated: {
                themaUpdater.checkUpdate();
            }
        }
    }

}
