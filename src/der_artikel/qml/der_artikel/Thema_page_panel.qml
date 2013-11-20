import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0
Page_panel
{
    Command_item
    {
        id: home_cmd
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
