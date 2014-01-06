import QtQuick 2.0
import QtGraphicalEffects 1.0
import com.vystosi.qmlcomponents 1.0

Flipable {
    id: flipable
    front: home_cmd
    back: quit_cmd
    property bool flipped: manager.current_page === Manager.HOME_PAGE ? true : false
    property int animation_duration: 500

    transform: Rotation {
        id: rotation
        origin.x: flipable.width/2
        origin.y: flipable.height/2
        axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }
    states: State {
        name: "back"
        PropertyChanges { target: rotation; angle: 180 }
        when: flipped
    }

    transitions: Transition {
        NumberAnimation { target: rotation; property: "angle"; duration: animation_duration }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        radius:6
        color:color_palette.color_bg_01
    }

    DropShadow {
        anchors.fill: background
        horizontalOffset: flipable.flipped ? -4 : 4
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: background

        Behavior on horizontalOffset {
            NumberAnimation { duration: animation_duration }
        }
    }

    Command_item
    {
        id: home_cmd
        anchors.centerIn: parent
        enabled: manager.current_page !== Manager.HOME_PAGE
        cmd_text: qsTr("Home") + settings.i18n_empty_string
        icon_name: "home"
        onCommandActivated: {
            manager.current_page = Manager.HOME_PAGE
        }
    }

    Command_item
    {
        id: quit_cmd
        anchors.centerIn: parent
        enabled: manager.current_page === Manager.HOME_PAGE
        cmd_text: qsTr("Quit") + settings.i18n_empty_string
        icon_name: "quit"
        onCommandActivated: {
            manager.quit()
        }
    }
}
