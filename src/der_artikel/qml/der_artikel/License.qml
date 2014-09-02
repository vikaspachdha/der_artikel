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
    id:root_item
    anchors.fill: parent

    Flickable {
        id:license_view
        anchors.fill: parent
        anchors.margins: 4
        anchors.rightMargin: 16
        contentHeight: content_text.contentHeight
        Text {
            id: content_text
            anchors.fill: parent
            text:about_page_instance.license_text

            wrapMode: Text.WordWrap
            font.family: regular_font.name
            color:color_palette.color_font_01
            font.pixelSize: settings.normal_text_size
        }
    }

    Scroll_bar {
        id: scroll_bar
        anchors {
            top:license_view.top
            topMargin: 6
            bottom:license_view.bottom
            bottomMargin: 6
            right: root_item.right
            rightMargin: 4
        }
        orientation: Qt.Vertical
        position: license_view.visibleArea.yPosition
        pageSize: license_view.visibleArea.heightRatio

        opacity: license_view.movingVertically ? 0.7 : 0
    }
}
