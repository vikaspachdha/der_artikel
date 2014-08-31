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
import QtMultimedia 5.1
Rectangle {
    id:btn_root

    property alias buttonText:label.text
    property alias text_px_size:label.font.pixelSize
    property bool isDown:false
    property alias text_h_alignment: label.horizontalAlignment
    signal activated();

    scale: mouse_area.pressed ? .95 :1
    Behavior on scale {
        NumberAnimation { duration: 100}
    }

    width: Math.max(80, label.contentWidth + 6)
    height: Math.max(30,label.contentHeight + 6)
    radius: 4
    gradient: Gradient {
        GradientStop {position: 0  ;color: color_palette.color_btn_02}
        GradientStop {position: 0.2;color: mouse_area.pressed || isDown ? color_palette.color_btn_01:color_palette.color_btn_02}
        GradientStop {position: 1;color: color_palette.color_btn_01}
    }

    border.width: isDown ? 2:0

    Text {
        id: label
        anchors.left: parent.left
        anchors.leftMargin: 3
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.baseline: parent.verticalCenter
        anchors.baselineOffset: (font.pixelSize/2) - 2
        text: qsTr("Button") + settings.i18n_empty_string
        color:color_palette.color_font_02
        font.family: regular_font.name
        font.pixelSize: settings.cmd_text_size
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: {
            clickSnd.play()
            btn_root.activated()
        }
    }
}
