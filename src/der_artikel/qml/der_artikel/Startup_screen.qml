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

Item {
    id: startup_screen
    anchors.fill: parent
    anchors.margins: 0

    Behavior on anchors.margins {
        NumberAnimation {
            duration:300;
            onRunningChanged: {
                if(!running) {
                    startup_screen.visible = false
                    manager.onStartupCompleted();
                    startup_screen.destroy()
                }
            }
        }
    }

    Behavior on anchors.bottomMargin {
        NumberAnimation {
            duration:300;
        }
    }

    Rectangle {
        id: background_rect
        anchors.fill: parent
        color:color_palette.color_bg_01
    }

    Text {
        id:header_text
        text: "Der Artikel"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: 42
    }

    Text {
        id: loading_text
        text: qsTr("Loading...") + settings.i18n_empty_string
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header_text.bottom
        font.family: regular_font.name
        color:color_palette.color_font_01
        font.pixelSize: normalTextSize

        SequentialAnimation {
            running: true
            loops: Animation.Infinite
            PropertyAnimation { target:loading_text; property: "opacity"; from: 0.4; to: 1.0;duration: 800;}
            PropertyAnimation { target:loading_text; property: "opacity"; from: 1.0; to: 0.4;duration: 800;}
        }
    }

    Component.onCompleted: {
        manager.onStartup();
    }

    function hideStartup() {
        loading_text.visible = false
        background_rect.radius=6
        startup_screen.anchors.bottomMargin = startup_screen.parent.height - 76
        startup_screen.anchors.margins = 4
    }
}
