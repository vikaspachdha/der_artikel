import QtQuick 2.0

Rectangle {
    id: rectangle1

    property alias left_text: text1.text
    property alias left_text_color: text1.color
    property alias right_text: text2.text
    property alias right_text_color: text2.color
    property alias center_text: centerText.text
    width:parent.width
    radius:4
    gradient: Gradient {
        GradientStop {position:0.0;color:color_palette.color_btn_02}
        GradientStop {position:0.1;color:color_palette.color_btn_01}
        GradientStop {position:0.9;color:color_palette.color_btn_01}
        GradientStop {position:1.0;color:color_palette.color_btn_02}
    }

    Text {
        id: text1
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: centerText.left
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        font.family:command_font.name
        font.pixelSize: 18
        color:"#75110C"
        elide: Text.ElideRight
    }

    Text {
        id: centerText
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        text:" -> "
        font.family:command_font.name
        font.pixelSize: 18
        color:color_palette.color_font_01
    }

    Text {
        id: text2
        anchors.top:parent.top
        anchors.bottom: parent.bottom
        anchors.left: centerText.right
        anchors.right: parent.right
        font.family:command_font.name
        font.pixelSize: 18
        verticalAlignment: Text.AlignVCenter
        color:"#17CC00"
        elide: Text.ElideRight
    }

}
