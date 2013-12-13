import QtQuick 2.0
import QtGraphicalEffects 1.0
import com.vystosi.qmlcomponents 1.0

Item {
    Rectangle {
        id: background_image
        anchors.fill: parent
        radius:6
        color:cp_blue.colorBg01
    }

    DropShadow {
        anchors.fill: background_image
        horizontalOffset: 4
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: background_image
    }

    Command_item
    {
        id: home_cmd
        anchors.centerIn: parent
        visible: manager.current_page !== Manager.HOME_PAGE
        cmd_text: qsTr("Home")
        icon_name: "home"
        onCommandActivated: {
            manager.current_page = Manager.HOME_PAGE
        }
    }

    Command_item
    {
        id: quit_cmd
        anchors.centerIn: parent
        visible: manager.current_page === Manager.HOME_PAGE
        cmd_text: qsTr("Quit")
        icon_name: "quit"
        onCommandActivated: {
            Qt.quit()
        }
    }
}
