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
    Item {
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        height:incorrect_noun.height
        Noun_Item {
            id:incorrect_noun
            anchors.right: parent.right
            anchors.rightMargin: 4
            anchors.verticalCenter:parent.verticalCenter
            article: Article.INVALID
        }
    }

    Item {
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        height:correct_noun.height
        Noun_Item {
            id:correct_noun
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.verticalCenter:parent.verticalCenter
        }
    }

}
