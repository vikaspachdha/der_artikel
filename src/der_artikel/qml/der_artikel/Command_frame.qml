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

Flipable {
    id: flipable
    property int shadow_offset:4

    front: home_cmd
    back: quit_cmd
    property bool flipped: manager.current_page === Manager.HOME_PAGE ? true : false
    property int animation_duration: 500

    transform: Rotation {
        id: rotation
        origin.x: flipable.width/2
        origin.y: flipable.height/2
        axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }
    states: State {
        name: "back"
        PropertyChanges { target: rotation; angle: 180 }
        when: flipped
    }

    transitions: Transition {
        NumberAnimation { target: rotation; property: "angle"; duration: animation_duration }
    }

    Rectangle {
        id: background_shadow
        x:flipable.flipped ? background.x - shadow_offset : background.x + shadow_offset
        y:background.y + shadow_offset
        width:background.width
        height:background.height
        radius:6
        color:color_palette.shadow_color
        opacity:0.8
        Behavior on x {
            NumberAnimation { duration: animation_duration }
        }
    }

    Rectangle {
        id: background
        anchors.fill: parent
        radius:6
        color:color_palette.color_bg_01
    }

    Command_item
    {
        id: home_cmd
        anchors.centerIn: parent
        enabled: manager.current_page !== Manager.HOME_PAGE
        cmd_text: qsTr("Home") + settings.i18n_empty_string
        icon_name: "home"
        onCommandActivated: {
            manager.current_page = Manager.HOME_PAGE
        }
    }

    Command_item
    {
        id: quit_cmd
        anchors.centerIn: parent
        enabled: manager.current_page === Manager.HOME_PAGE
        cmd_text: qsTr("Quit") + settings.i18n_empty_string
        icon_name: "quit"
        onCommandActivated: {
            manager.quit()
        }
    }
}
