import QtQuick 2.0

Rectangle {
    id: rectangle1

    property alias item_title: text1.text
    property alias item_result: text2.text
    width:parent.width
    radius:4
    gradient: Gradient {
        GradientStop {position:0.0;color:cp_blue.colorBg02}
        GradientStop {position:0.1;color:cp_blue.colorBg01}
        GradientStop {position:0.9;color:cp_blue.colorBg01}
        GradientStop {position:1.0;color:cp_blue.colorBg02}
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
        color:cp_blue.colorf01
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
    }

}
