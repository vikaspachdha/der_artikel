import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id:Manager.ABOUT_PAGE
    Column {
        id: about_level_col
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 4

        Button {
            id:replay_btn
            width:parent.width
            text_anchors.horizontalCenter: replay_btn.horizontalCenter
            buttonText: qsTr("Update")
            onActivated: showMessage(qsTr("Latest version"), qsTr("No update is available"),1200)
        }
    }
}
