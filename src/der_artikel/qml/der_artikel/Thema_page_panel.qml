import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
Page_panel
{
    Button {
        id:easy_btn
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.bottom: moderate_btn.top
        anchors.bottomMargin: 4
        buttonText: qsTr("Easy")
    }

    Button {
        id:moderate_btn
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.bottom: expert_btn.top
        anchors.bottomMargin: 4
        buttonText: qsTr("Moderate")
    }

    Button {
        id:expert_btn
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.bottom: start_cmd.top
        anchors.bottomMargin: 8
        buttonText: qsTr("Expert")
    }

    Command_item
    {
        id: start_cmd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        cmd_text: qsTr("Start")
        cmd_icon: "qrc:/res/resources/start.png"
        onCommandActivated: {
            manager.current_page = Manager.WORDS_PAGE
        }
    }
}
