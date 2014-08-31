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

Title_bar {
    property int play_time: 1
    property alias timer_running:play_timer.running
    property string timer_text_str: ""
    page_id: Manager.WORDS_PAGE
    Timer {
        id: play_timer
        interval: 1000
        repeat: true
        onTriggered: {
            if(play_time<=1) {
                running = false
                manager.current_page = Manager.RESULT_PAGE
            }

            if(play_time <=20) {
                timer_text.color = color_palette.color_info
            }

            if(play_time <=10) {
                timer_text.color = color_palette.color_warn
            }

            timer_text_str = toTime(--play_time)
        }
    }

    Text {
        id: thema_title
        anchors {
            left:parent.left
            leftMargin: 6
            top:parent.top
            topMargin: 6
        }
        text: themaModel.selected_thema ? themaModel.selected_thema.name + "\n" + themaModel.selected_thema.tr_name : ""
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: settings.heading_1_size
    }

    Text {
        id: word_desc
        anchors {
            left:parent.left
            leftMargin: 6
            bottom:parent.bottom
            bottomMargin: 6
            right: timer_text.left
            rightMargin: 6
        }
        text: words_page.word_description
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: settings.heading_1_size
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
    }

    Text {
        id: timer_title
        anchors {
            right: parent.right
            rightMargin: 6
            top:parent.top
            topMargin: 6
        }
        text: qsTr("Remaining time") + settings.i18n_empty_string
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: settings.heading_1_size
    }

    Text {
        id: timer_text
        anchors {
            right: parent.right
            rightMargin: 6
            bottom:parent.bottom
            bottomMargin: 6
        }
        text:manager.game_level === Manager.PRACTICE?"∞":timer_text_str
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: settings.heading_1_size
    }

    onPlay_timeChanged: {
        timer_text.text = toTime(play_time)
    }

    function toTime(secs) {
        var hours = (secs/3600)|0
        secs -= (hours*3600);
        var mins = (secs/60)|0;
        secs -= (mins*60);

        return pad(hours,2)+":"+pad(mins,2)+":"+pad(secs,2)
    }

    function pad (number, max) {
        var str = number.toString()
        return str.length < max ? pad("0" + str, max-1) : str;
    }
}
