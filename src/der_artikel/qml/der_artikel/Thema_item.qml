import QtQuick 2.0

Rectangle {
    id: root_rect
    property alias title: thema_title.text
    property alias translation: thema_tr_text.text
    property alias icon_url:thema_icon.source
    property int count:0
    property bool selected: false
    color: selected ? "lightsteelblue" : "lightgray"
    radius:4

    Image {
        id: thema_icon
        width: 64
        height: 64
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        source: "qrc:/qtquickplugin/images/template_image.png"
    }

    Text {
        id: thema_tr_text
        height: 14
        text: qsTr("translation")
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: thema_title.bottom
        anchors.topMargin: 4
        font.pixelSize: 12
    }

    Image {
        id: info_icon
        width: 24
        height: 24
        anchors.bottom: thema_icon.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 4
        source: "qrc:/res/resources/info.png"
    }

    Text {
        id: thema_title
        height: 14
        text: qsTr("Title")
        anchors.top: thema_icon.bottom
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.left: parent.left
        anchors.leftMargin: 4
        font.pixelSize: 14
    }

    Text {
        id: word_count_label
        height: 13
        text: qsTr("Words")
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.left: thema_icon.right
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 8
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    Text {
        id: word_count_text
        height: 14
        text: count
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.left: thema_icon.right
        anchors.leftMargin: 4
        anchors.top: word_count_label.bottom
        anchors.topMargin: 4
        font.pixelSize: 12
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            selected = !selected
        }
    }

}
