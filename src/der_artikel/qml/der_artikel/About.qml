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
        id: about_view
        anchors.fill: parent
        anchors.margins: 4
        anchors.rightMargin: 16
        Item {
            id:text_rect
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height:childrenRect.height
            Text {
                id: version_text
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 8
                text:qsTr("Version\n") + manager.version_string + settings.i18n_empty_string

                wrapMode: Text.WordWrap
                font.family: regular_font.name
                color:color_palette.color_font_01
                font.pixelSize: settings.normal_text_size
                font.italic: true
                horizontalAlignment: Text.AlignHCenter
            }

            Text {
                id: content_text
                anchors.top: version_text.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                text:"The SOFTWARE and the data used in the software and any related documentation \
is provided \"as is\" without warranty of any kind, either express or implied, including, without \
limitation, the implied warranties or merchantability or fitness for a particular purpose. The \
entire risk arising out of use or performance of the SOFTWARE remains with you."

                wrapMode: Text.WordWrap
                font.family: regular_font.name
                color:color_palette.color_font_01
                font.pixelSize: settings.normal_text_size
            }

            Text {
                id: developer_text
                anchors.top: content_text.bottom
                anchors.topMargin: 30
                anchors.left: parent.left
                anchors.right: parent.right
                text:"
<u>Developers:</u> \
<p><ul><li>Vikas Pachdha (www.vikaspachdha.com)</li><li>Mohita Gandotra (mohitagandotra@gmail.com)</li></ul></p>

<u>Thema contributors:</u>\
<p><ul><li>Vikas Pachdha</li><li>Mohita Gandotra</li></ul></p>"

                wrapMode: Text.WordWrap
                textFormat: Text.StyledText
                font.family: regular_font.name
                color:color_palette.color_font_01
                font.pixelSize: settings.normal_text_size
            }
        }

        contentHeight: text_rect.childrenRect.height
    }

    Scroll_bar {
        id: scroll_bar
        anchors {
            top:about_view.top
            topMargin: 6
            bottom:about_view.bottom
            bottomMargin: 6
            right: root_item.right
            rightMargin: 4
        }
        orientation: Qt.Vertical
        position: about_view.visibleArea.yPosition
        pageSize: about_view.visibleArea.heightRatio

        opacity: about_view.movingVertically ? 0.7 : 0
    }
}
