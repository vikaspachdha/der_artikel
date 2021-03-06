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
    id: title
    property int page_id
    property int shadow_offset:4
    y:-height-4
    height:settings.title_frame_height - 6
    anchors{left:parent.left;right:parent.right}
    Behavior on y {
        SequentialAnimation {
            PauseAnimation { id:animPause }
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
            onRunningChanged: {
                if(running===true ) {
                    // Animation starting
                    if(manager.current_page === page_id) {
                        animPause.duration=0
                    } else {
                        animPause.duration=300
                    }
                } else {
                    // Animation stopped
                    if(manager.current_page !== page_id) {
                        title.destroy()
                    }
                }
            }
        }
    }

    Connections {
        target:manager
        onCurrentPageChanged: {
            y = manager.current_page === page_id ? 4 : -height-4
        }
    }

    Rectangle {
        id: background_shadow
        x:background_image.x + shadow_offset
        y:background_image.y + shadow_offset
        width:background_image.width
        height:background_image.height
        radius:6
        color:color_palette.shadow_color
        opacity:0.8
    }

    Rectangle {
        id: background_image
        anchors.fill: parent
        radius:6
        color:color_palette.color_bg_01
    }

    Component.onCompleted: {
        manager.setTitleItem(page_id,title)
        y = 4
    }
}
