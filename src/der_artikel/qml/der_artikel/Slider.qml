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
    id: sliderRoot
    // User properties
    property bool readOnly:false
    property real value:0
    property alias valueChangeAnimDuration:valueChangeAnim.duration

    // Private properties
    property int bar_height: 12
    property real gripWidth:28
    readonly property real halfGripWidth: gripWidth/2

    signal gripDropped()
    Rectangle {
        id:barRect
        color:color_palette.color_btn_02
        anchors {
            left: parent.left
            leftMargin: halfGripWidth
            right: parent.right
            rightMargin: halfGripWidth
            verticalCenter: parent.verticalCenter
        }
        height: bar_height

        Rectangle {
            id:valueRect
            anchors {
                left: parent.left
                right:grip.right
                rightMargin: halfGripWidth
                top: parent.top
                bottom:parent.bottom
            }
            color: color_palette.color_bg_02
            onWidthChanged: {
                var currentValue = valueRect.width/barRect.width;
                if(mouseArea.pressed && (Math.abs(currentValue - value) > 0.001) ) {
                    value = currentValue;
                }
            }
        }

        Rectangle {
            id: grip
            x:-halfGripWidth
            anchors.verticalCenter: parent.verticalCenter
            width: gripWidth
            height: gripWidth
            radius: halfGripWidth
            color: color_palette.color_btn_01
            Behavior on x {
                NumberAnimation {id:valueChangeAnim; duration: 100 }
            }

            MouseArea {
                id: mouseArea
                enabled: !sliderRoot.readOnly
                anchors.fill:  parent
                drag {
                    target: grip
                    axis: Drag.XAxis
                    minimumX: -halfGripWidth
                    maximumX: barRect.width - halfGripWidth
                }
                onReleased: {
                    sliderRoot.gripDropped()
                }
            }
        }
    }

    function setValue(newValue) {
        grip.x = barRect.width * newValue - halfGripWidth
        var currentValue = valueRect.width/barRect.width;
        if(Math.abs(currentValue - value) > 0.001 ) {
            value = currentValue;
        }
    }

    function getSliderBarX() {
        return barRect.x
    }

    function getSliderBarY() {
        return barRect.y
    }

    function getSliderBarWidth() {
        return barRect.width
    }
}
