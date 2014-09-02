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
        Text {
            id: content_text
            anchors.fill: parent
            anchors.rightMargin: 16
            text:qsTr("To play the game select a thema from thema page and click start. \
\nwords page shall open with the words displayed on right side and \
articles on left side.\n\nTo gain points, user must assign correct articles to the nouns. \
Clicking on article button makes the corresponding article as active article and clicking \
on words afterwards assigns the selected article to the clicked word.\n\nChange in \
background color of word confirms article assignment. The user must assign articles \
to all the words. Incorrect articles and unplayed words may result into points deduction \
depending on the game level selected.")  + settings.i18n_empty_string

            wrapMode: Text.WordWrap
            font.family: regular_font.name
            color:color_palette.color_font_01
            font.pixelSize: settings.normal_text_size
        }
        contentHeight: content_text.contentHeight
    }

    Scroll_bar {
        id: scroll_bar
        anchors {
            top:help_view.top
            topMargin: 6
            bottom:help_view.bottom
            bottomMargin: 6
            right: root_item.right
            rightMargin: 4
        }
        orientation: Qt.Vertical
        position: help_view.visibleArea.yPosition
        pageSize: help_view.visibleArea.heightRatio
        opacity: help_view.movingVertically ? 0.7 : 0
    }
}
