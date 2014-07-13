import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id:Manager.ABOUT_PAGE

    Label {
        id: option_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Options") + settings.i18n_empty_string
    }

    Column {
        id: about_level_col
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
            buttonText: qsTr("Update") + settings.i18n_empty_string
            onActivated: {
                appUpdater.checkUpdate();
            }
        }

        Button {
            id:update_thema_btn
            width:parent.width
            buttonText:qsTr("Update thema") +settings.i18n_empty_string
            onActivated: {
                themaUpdater.checkUpdate();
            }
        }
    }

    Connections {
        target:appUpdater
        onUpdateResponse: {
            switch(response_code) {
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
        onUpdateResponse: {

            switch(response_code) {

                case ThemaUpdater.UPDATE_STARTED:
                    messageBarInstance.showMsgAsync(qsTr("Updating thema"),"");
                    break;

                case ThemaUpdater.UPDATE_NOT_AVAILABLE:
                case ThemaUpdater.UPDATE_ERROR:
                case ThemaUpdater.UPDATE_ABORTED:
                case ThemaUpdater.UPDATE_FINISHED:
                    messageBarInstance.closeMsg()
                    break;
            }
        }

        onUpdateProgress: {
            msg_bar.message_txt = info;
            msg_bar.setProgress(progress)
        }
    }

}
