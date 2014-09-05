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
    property alias left_text: incorrect_noun.text
    property alias right_text: correct_noun.text
    property alias correct_article:correct_noun.article

    width:parent.width
    height: childrenRect.height

    Noun_Item {
        id:correct_noun
        anchors.top : incorrect_noun.bottom
        anchors.topMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Noun_Item {
        id:incorrect_noun
        anchors.top : parent.top
        anchors.topMargin: 6
        anchors.horizontalCenter: parent.horizontalCenter
        article: Article.INVALID
    }

    Rectangle {
        id: top_line
        width:parent.width/2
        anchors.top: correct_noun.bottom
        anchors.topMargin: 4
        anchors.horizontalCenter: parent.horizontalCenter
        height :1
        color:color_palette.color_btn_01
    }

}
