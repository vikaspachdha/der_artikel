import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0


Flipable {
    id: thema_item_root
    property alias title: thema_title.text
    property alias translation: thema_tr_text.text
    property alias author_name: author.text
    property alias last_played_text: date.text
    property alias icon_url:thema_icon.source
    property int count:0
    property bool thema_selected: false
    property int flip_timeout:5000
    property bool flipped: false

    front: thema_rect
    back:info_rect

    signal themaClicked()
    signal themaLongClicked()

    Rectangle {
        id: info_rect
        color:color_palette.color_btn_01
        radius:4
        anchors.fill: parent
        Text {
            id:author_label
            anchors.top:parent.top
            anchors.topMargin: 2
            anchors.left:parent.left
            anchors.leftMargin: 2
            anchors.right: parent.right
            text:qsTr("Author :") + settings.i18n_empty_string
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 14
        }
        Text {
            id:author
            anchors.top: author_label.bottom
            anchors.left:parent.left
            anchors.leftMargin: 2
            anchors.right: parent.right
            text:"-"
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 12
        }
        Text {
            id:last_played_date_label
            anchors.top:author.bottom
            anchors.topMargin: 8
            anchors.left:parent.left
            anchors.leftMargin: 2
            anchors.right: parent.right
            text:qsTr("Last Played :") + settings.i18n_empty_string
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 14
        }
        Text {
            id:date
            anchors.top: last_played_date_label.bottom
            anchors.left:parent.left
            anchors.leftMargin: 2
            anchors.right: parent.right
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 12
        }
    }


    Rectangle {
        id: thema_rect
        color:color_palette.color_btn_01
        radius:4
        anchors.fill: parent
        Image {
            id: thema_icon
            width: 64
            height: 64
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
        }

        Text {
            id: thema_title
            height: 14
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: thema_icon.bottom
            anchors.topMargin: 2
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 12
        }

        Text {
            id: thema_tr_text
            height: 14
            anchors.top: thema_title.bottom
            anchors.topMargin: 2
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: parent.left
            anchors.leftMargin: 4
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 12
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
            anchors.topMargin: 4
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 12
        }

        Text {
            id: word_count_text
            height: 14
            text: thema_item_root.count
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: thema_icon.right
            anchors.leftMargin: 4
            anchors.top: word_count_label.bottom
            anchors.topMargin: 0
            color:color_palette.color_font_02
            font.family:custom_regular.name
            font.pixelSize: 12
        }

        MouseArea {
            anchors.fill: thema_rect
            onClicked: {
                thema_item_root.themaClicked()
            }
            onPressAndHold: {
                thema_item_root.themaLongClicked()
            }
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
            MouseArea {
                anchors.fill: info_icon
                onClicked: thema_item_root.flipped = !thema_item_root.flipped
            }
        }

    }


    transform: Rotation {
        id: rotation
        origin.x: thema_item_root.width/2
        origin.y: thema_item_root.height/2
        axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }

    Rectangle {
        height: 6
        width: height
        radius: 3
        anchors{left:parent.left;top:parent.top;margins: 4}
        visible: thema_item_root.thema_selected
        color:color_palette.color_font_02
    }

    states: State {
        name: "back"
        PropertyChanges { target: rotation; angle: 180 }
        when: thema_item_root.flipped
    }

    transitions: Transition {
        NumberAnimation { target: rotation; property: "angle"; duration: 200 }
    }



    Timer {
        id:flip_timer
        interval: flip_timeout
        onTriggered: {
            thema_item_root.flipped = false
        }
    }

    onFlippedChanged: {
        if(flipped) {
            flip_timer.restart()
        } else {
            flip_timer.stop()
        }
    }

}





