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
    id: item_root
    property int article: Article.INVALID
    property alias text: label.text
    height: childrenRect.height
    width:childrenRect.width
    Image {
        id: left_image
        height: text_area.height
        width:sourceSize.width
        source: {
            switch(item_root.article) {
            case Article.DER:return "qrc:/res/resources/paper_texture_left_der.png";
            case Article.DIE:return "qrc:/res/resources/paper_texture_left_die.png";
            case Article.DAS:return "qrc:/res/resources/paper_texture_left_das.png";
            default:return "qrc:/res/resources/paper_texture_left.png";
            }
        }
    }

    Image {
        id:text_area
        width:label.width
        height:label.height
        anchors.left: left_image.right
        source: {
            switch(item_root.article) {
            case Article.DER:return "qrc:/res/resources/paper_texture_middle_der.png";
            case Article.DIE:return "qrc:/res/resources/paper_texture_middle_die.png";
            case Article.DAS:return "qrc:/res/resources/paper_texture_middle_das.png";
            default:return "qrc:/res/resources/paper_texture_middle.png";
            }
        }
    }

    Image {
        id: right_image
        height: text_area.height
        width:sourceSize.width
        anchors.left: text_area.right
        source: {
            switch(item_root.article) {
            case Article.DER:return "qrc:/res/resources/paper_texture_right_der.png";
            case Article.DIE:return "qrc:/res/resources/paper_texture_right_die.png";
            case Article.DAS:return "qrc:/res/resources/paper_texture_right_das.png";
            default:return "qrc:/res/resources/paper_texture_right.png";
            }
        }
    }

    Text {
        id: label
        anchors.left: text_area.left
        anchors.verticalCenter: text_area.verticalCenter
        font.family: "Georgia"
        font.pixelSize: settings.noun_text_size
    }
}
