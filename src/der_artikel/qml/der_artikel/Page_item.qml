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
    id: root_item
    property alias label_text:item_label.text
    property alias page_icon:icon.source
    Rectangle {
        anchors.fill:icon
        color:color_palette.color_btn_01
        radius:8
    }

    Image {
        id: icon
        width:parent.width
        height: width
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: "qrc:/res/resources/default_thema.png"
    }

    Text {
        id: item_label
        anchors.top: icon.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 0
        horizontalAlignment: Text.AlignHCenter
        smooth:true
        color:color_palette.color_font_01
        font.family: regular_font.name
        font.pixelSize: settings.cmd_text_size
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: {
            manager.current_page=model.src_page_id
        }
    }
}
