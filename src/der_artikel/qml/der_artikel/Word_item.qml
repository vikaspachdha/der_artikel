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
    id: root
    // Properties definition
    property alias wordText: noun_item.text
    property string description_text:""
    property bool info_mode: words_page.info_mode
    property QtObject word

    // Signals
    signal wordClicked

    height: childrenRect.height
    width:childrenRect.width

    Noun_Item {
        id:noun_item
        scale: mouse_area.pressed ? .95 :1
        Behavior on scale {
            NumberAnimation { duration: 100}
        }
        article: word == null ? Article.INVALID : word.user_article
    }

    MouseArea {
        id:mouse_area
        anchors.fill: parent
        onClicked: {
            wordClicked()
            switch(word.user_article) {
                case Article.DER:derSnd.play();break;
                case Article.DIE:dieSnd.play();break;
                case Article.DAS:dasSnd.play();break;
            }
        }
    }
}
