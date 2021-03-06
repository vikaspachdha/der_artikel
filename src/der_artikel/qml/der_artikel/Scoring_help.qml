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
        id:help_view
        anchors.fill: parent
        anchors.margins: 4
        anchors.rightMargin: 16
        contentHeight: content_text.contentHeight
        Text {
            id: content_text
            anchors.fill: parent
            text:qsTr("<p>Scoring:<table border=\"1\"> \
<tr> \
<td><b>Game level</b></td> \
<td>Correct article</td> \
<td>Incorrect article</td> \
<td>Unplayed word</td> \
</tr> \
<tr> \
<td>EASY</td> \
<td>1</td> \
<td>-0.5</td> \
<td>-0.25</td> \
</tr> \
<tr> \
<td>Moderate</td> \
<td>1</td> \
<td>-0.5</td> \
<td>0</td> \
</tr> \
<tr> \
<td>Expert</td> \
<td>1</td> \
<td>0</td> \
<td>0</td> \
</tr> \
</table> \
</p><p>Grading:<table border=\"1\"> \
<tr> \
<td><b>SCORE</b></td> \
<td>Grade</td> \
</tr> \
<tr> \
<td>&gt;94.99</td> \
<td>A+</td> \
</tr> \
<tr> \
<td>&gt;89.99</td> \
<td>A</td> \
</tr> \
<tr> \
<td>&gt;79.99</td> \
<td>B+</td> \
</tr> \
<tr> \
<td>&gt;69.99</td> \
<td>B</td> \
</tr> \
<tr> \
<td>&gt;59.99</td> \
<td>C</td> \
</tr> \
<tr> \
<td>&gt;49.99</td> \
<td>D</td> \
</tr> \
<tr> \
<td>&lt;49.99</td> \
<td>E</td> \
</tr> \
</table> \
</p><p>Experience:<table border=\"1\"> \
<tr> \
<td><b>Grade</b></td> \
<td>Easy</td> \
<td>Moderate</td> \
<td>Expert</td> \
</tr> \
<tr> \
<td>A+</td> \
<td>50</td> \
<td>80</td> \
<td>100</td> \
</tr> \
<tr> \
<td>A</td> \
<td>40</td> \
<td>60</td> \
<td>80</td> \
</tr> \
<tr> \
<td>B+</td> \
<td>30</td> \
<td>50</td> \
<td>70</td> \
</tr> \
<tr> \
<td>B</td> \
<td>20</td> \
<td>40</td> \
<td>60</td> \
</tr> \
<tr> \
<td>C</td> \
<td>10</td> \
<td>30</td> \
<td>50</td> \
</tr> \
<tr> \
<td>D</td> \
<td>5</td> \
<td>20</td> \
<td>40</td> \
</tr> \
<tr> \
<td>E</td> \
<td>0</td> \
<td>-10</td> \
<td>-20</td> \
</tr> \
</table></p>") + settings.i18n_empty_string

            textFormat: Text.RichText
            wrapMode: Text.WordWrap
            font.family: regular_font.name
            color:color_palette.color_font_01
            font.pixelSize: settings.normal_text_size
        }
    }


    Scroll_bar {
        id: scroll_bar
        anchors {
            top:root_item.top
            topMargin: 6
            bottom:root_item.bottom
            bottomMargin: 6
            right: root_item.right
            rightMargin: 4
        }
        orientation: Qt.Vertical
        position: help_view.visibleArea.yPosition
        pageSize: help_view.visibleArea.heightRatio

        opacity: help_view.movingVertically ? 0.7 : 0
        Behavior on opacity {
            NumberAnimation { properties: "opacity"; duration: 250 }
        }
    }
}
