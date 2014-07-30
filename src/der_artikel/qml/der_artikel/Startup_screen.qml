import QtQuick 2.1
import QtGraphicalEffects 1.0

Item {
    id: startup_screen
    anchors.fill: parent
    anchors.margins: 0
    property int startup_time: 3000

    Behavior on anchors.margins {
        NumberAnimation {
            duration:300;
            onRunningChanged: {
                if(!running) {
                    startup_screen.visible = false
                    manager.onStartupCompleted();
                    //startup_screen.destroy()
                }
            }
        }
    }

    Behavior on anchors.bottomMargin {
        NumberAnimation {
            duration:300;
        }
    }

    Rectangle {
        id: background_rect
        anchors.fill: parent
        color:color_palette.color_bg_01
    }

    DropShadow {
        anchors.fill: background_rect
        visible: settings.enable_effects
        horizontalOffset: 2
        verticalOffset: 4
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: background_rect
    }

    Text {
        id: name
        text: "Der Artikel"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: 42
    }

    Component.onCompleted: {
        console.log("Startup screen created.")
        manager.onStartup();
    }
    Component.onDestruction: {
        console.log("Startup screen destroyed.")
    }

    function hideStartup() {
        background_rect.radius=6
        startup_screen.anchors.bottomMargin = startup_screen.parent.height - 76
        startup_screen.anchors.margins = 4
    }
}
