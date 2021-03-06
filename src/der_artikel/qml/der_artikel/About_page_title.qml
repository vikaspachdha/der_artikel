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

Title_bar {
    page_id: Manager.ABOUT_PAGE
    Image {
        id:icon
        source: "qrc:/res/resources/app.png"
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 2
        height:64
        width:height
        fillMode: Image.Stretch
    }

    Text {
        id: name
        text: "Der Artikel"
        anchors.left: icon.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        font.family: title_font.name
        color:color_palette.color_font_01
        font.pixelSize: settings.title_text_size
        horizontalAlignment: Text.AlignHCenter
    }
}
