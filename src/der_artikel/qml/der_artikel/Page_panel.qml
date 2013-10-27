import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    Command_item
    {
        id: home_cmd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        cmd_text: qsTr("Home")
        cmd_icon: "qrc:/res/resources/home.png"
        onCommandActivated: {
            manager.current_page = Manager.HOME_PAGE
        }
    }
}
