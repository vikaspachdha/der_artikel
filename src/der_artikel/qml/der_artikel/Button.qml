import QtQuick 2.1
import QtMultimedia 5.1
Rectangle {
    id:btn_root

    property alias buttonText:label.text
    property alias text_px_size:label.font.pixelSize
    property bool isDown:false
    property alias text_h_alignment: label.horizontalAlignment
    signal activated();


    width: 80
    height: 30
    radius: 4
    gradient: Gradient {
        GradientStop {position: 0  ;color: color_palette.color_btn_02}
        GradientStop {position: 0.2;color: mousearea1.pressed || isDown ? color_palette.color_btn_01:color_palette.color_btn_02}
        GradientStop {position: 1;color: color_palette.color_btn_01}
    }

    border.width: mousearea1.pressed | isDown ? 2:0

    Text {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.baseline: parent.verticalCenter
        anchors.baselineOffset: (font.pixelSize/2) - 2
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
