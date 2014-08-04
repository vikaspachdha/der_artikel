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

Flickable {
    anchors.fill: parent
    anchors.margins: 4

    contentHeight: cp_btn_col.height

    Column {
        id: cp_btn_col
        anchors.top: parent.top
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:cp_blue_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: color_palette === cp_blue
            buttonText: qsTr("Deep blue") + settings.i18n_empty_string
            onActivated: color_palette = cp_blue
        }

        Button {
            id:cp_orange_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: color_palette === cp_orange
            buttonText: qsTr("Tangy Orange") + settings.i18n_empty_string
            onActivated: color_palette = cp_orange
        }

        Button {
            id:cp_night_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: color_palette === cp_night
            buttonText: qsTr("Dark night") + settings.i18n_empty_string
            onActivated: color_palette = cp_night
        }

    }
}
