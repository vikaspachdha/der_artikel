import QtQuick 2.1
import QtMultimedia 5.1
Rectangle {
    id:btn_root

    property alias buttonText:label.text
    property alias textPxSize:label.font.pixelSize
    property bool isDown:false
    property alias text_anchors: label.anchors
    signal activated();


    width: label.width+12
    height: label.height+8
    radius: 4
    gradient: Gradient {
        GradientStop {position: 0  ;color: color_palette.color_btn_02}
        GradientStop {position: 0.2;color: mousearea1.pressed || isDown ? color_palette.color_btn_01:color_palette.color_btn_02}
        GradientStop {position: 1;color: color_palette.color_btn_01}
    }

    border.width: mousearea1.pressed | isDown ? 2:0

    Text {
        id: label
        x:2
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("Button") + settings.i18n_empty_string
        color:color_palette.color_font_02
        font.family: regular_font.name
        font.pixelSize: commandTextSize
    }

    MouseArea {
        id: mousearea1
        anchors.fill: parent
        onClicked: {
            clickSnd.play()
            btn_root.activated()
        }
    }
}
