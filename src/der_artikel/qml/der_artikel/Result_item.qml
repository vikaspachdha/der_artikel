import QtQuick 2.0

Rectangle {
    id: rectangle1

    property alias item_title: text1.text
    property alias item_result: text2.text

    color: "#C7CDE6"
    width:parent.width

    Image {
        id: image1
        width: height
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        source: "qrc:/res/resources/thumbs_down_32.png"
    }

    Text {
        id: text1
        height: parent.height*0.5
        font.pixelSize: height* 0.9
        smooth: true
        anchors.rightMargin: 0
        verticalAlignment: Text.AlignVCenter
        anchors.left: image1.right
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Text {
        id: text2
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 4
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom
        anchors.left: image1.right
        anchors.topMargin: 0
        font.pixelSize: height*0.9
        color:"green"
    }

}
