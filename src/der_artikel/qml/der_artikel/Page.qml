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
    id:page
    property int page_id
    x : width +16
    Behavior on x {
        SequentialAnimation {
            PauseAnimation { id: animPause;}
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
            onRunningChanged: {
                if(running===true ) {
                    // Animation starting
                    if(manager.current_page == page_id) {
                        animPause.duration=0
                    } else {
                        animPause.duration=300
                    }
                } else {
                    // Animation stopped
                    if(manager.current_page !== page_id) {
                        page.destroy()
                    }
                }
            }
        }
    }

    Connections {
        target:manager
        onCurrentPageChanged: {
            x = manager.current_page === page_id ? 4 : width +16
        }
    }
    width:parent.width-8
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.topMargin: 6
    anchors.bottomMargin: 6
    clip:true

    Component.onCompleted: {
        manager.setPageItem(page_id,page)
        x = 4
    }
}
