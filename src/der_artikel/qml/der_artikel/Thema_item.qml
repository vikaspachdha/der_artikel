//******************************************************************************
/*! \file 
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0
import QtMultimedia 5.1
import QtGraphicalEffects 1.0

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

    RectangularGlow {
        anchors.fill: info_rect
        glowRadius: 8
        spread: 0.2
        color: color_palette.selection_shadow
        cornerRadius: info_rect.radius + glowRadius
        visible: thema_item_root.thema_selected
    }

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
            font.family:regular_font.name
            font.pixelSize: settings.cmd_text_size
        }
        Text {
            id:author
            anchors.top: author_label.bottom
            anchors.left:parent.left
            anchors.leftMargin: 2
            anchors.right: parent.right
            text:"-"
            color:color_palette.color_font_02
            font.family:regular_font.name
            font.pixelSize: settings.sub_cmd_text_size
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
            font.family:regular_font.name
            font.pixelSize: settings.cmd_text_size
        }
        Text {
            id:date
            anchors.top: last_played_date_label.bottom
            anchors.left:parent.left
            anchors.leftMargin: 2
            anchors.right: parent.right
            color:color_palette.color_font_02
            font.family:regular_font.name
            font.pixelSize: settings.sub_cmd_text_size
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
            font.family:regular_font.name
            font.pixelSize: settings.sub_cmd_text_size
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
            font.family:regular_font.name
            font.pixelSize: settings.sub_cmd_text_size
        }

        Text {
            id: word_count_label
            height: 13
            text: qsTr("Words") +settings.i18n_empty_string
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.left: thema_icon.right
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 4
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color:color_palette.color_font_02
            font.family:regular_font.name
            font.pixelSize: settings.sub_cmd_text_size
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
            font.family:regular_font.name
            font.pixelSize: settings.sub_cmd_text_size
        }

        MouseArea {
            anchors.fill: thema_rect
            onClicked: {
                thema_item_root.themaClicked()
                coinSnd.play()
            }
            onPressAndHold: {
                thema_item_root.themaLongClicked()
                coinSnd.play()
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





