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

Item {
    anchors.fill: parent
    Label {
        id:msg_time_lbl
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top:parent.top
        anchors.topMargin: 8
        text_h_alignment: Text.AlignLeft
        text:qsTr("Word info Time (in msecs)") + settings.i18n_empty_string
    }
    Rectangle {
        id:msg_time_input_rect
        anchors{top:msg_time_lbl.bottom;left:parent.left;leftMargin: 8}
        width:40
        height:msg_time_input.contentHeight + 4
        radius: 4
        color:color_palette.color_btn_01
        TextInput {
            id:msg_time_input
            width:parent.width - 4
            anchors{centerIn: parent}
            text:settings.word_msg_time_str
            validator: IntValidator{bottom:settings.min_word_msg_time;top:settings.max_word_msg_time}
            onTextChanged: {
                settings.word_msg_time_str = text;
            }
        }
    }

    Slider {
        id:msgTimeSlider
        property bool update_value: true
        property int  msec_range: settings.max_word_msg_time - settings.min_word_msg_time
        anchors.verticalCenter: msg_time_input_rect.verticalCenter
        anchors.left: msg_time_input_rect.right
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 8
        onValueChanged: {
            update_value = false
            settings.word_msg_time = (value * msec_range) + settings.min_word_msg_time
            update_value = true;
        }

        Connections {
            target:settings
            onWordMsgTimeChanged : {
                if(msgTimeSlider.update_value) {
                    msgTimeSlider.setValue((settings.word_msg_time - settings.min_word_msg_time)/msgTimeSlider.msec_range)
                }
            }
        }
        Component.onCompleted: {
            msgTimeSlider.setValue((settings.word_msg_time - settings.min_word_msg_time)/msec_range)
        }
    }

    Label {
        id:url_lbl
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top:msgTimeSlider.bottom
        anchors.topMargin: 20
        text_h_alignment: Text.AlignLeft
        text:qsTr("Thema update url") + settings.i18n_empty_string
    }

    Rectangle {
        id:url_input_rect
        anchors{top:url_lbl.bottom;left:parent.left;leftMargin: 8;right: parent.right;rightMargin: 8}
        height:url_input.contentHeight + 4
        radius: 4
        color:color_palette.color_btn_01
        clip:true
        TextInput {
            id:url_input
            width:parent.width-4
            anchors{centerIn: parent}
            selectByMouse: true
            onTextChanged: {
                settings.thema_remote_path = text;
            }
            Component.onCompleted: {
                url_input.text = settings.thema_remote_path
            }
        }
    }

    Label {
        id:auto_update_lbl
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top:url_input_rect.bottom
        anchors.topMargin: 20
        text_h_alignment: Text.AlignLeft
        text:qsTr("Update thema files automatically every fortnight.") + settings.i18n_empty_string
    }

    Button {
        id:auto_update_btn
        anchors{top:auto_update_lbl.bottom;left:parent.left;leftMargin: 8}
        text_h_alignment: Text.AlignHCenter
        isDown: settings.thema_auto_update === true
        buttonText: qsTr("Auto update") + settings.i18n_empty_string
        onActivated: {
            settings.thema_auto_update = !settings.thema_auto_update
        }

    }

}
