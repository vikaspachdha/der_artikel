import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id: Manager.STATS_PAGE

    Label {
        id: stats_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: stats_lbl.horizontalCenter
        lblText: qsTr("Lets Brag!")
    }

    Column {
        id: help_btn_col
        anchors.top: stats_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 4

        Button {
            id:share_btn
            width:parent.width
            text_anchors.horizontalCenter: share_btn.horizontalCenter
            buttonText: qsTr("Share")
        }
    }
}
