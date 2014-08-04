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

Page {
    id:root
    page_id:Manager.STATS_PAGE

    property int thema_count:0
    property int inert_thema_count:0
    property int golden_thema_count:0
    property int silver_thema_count:0
    property int rusty_thema_count:0
    property string best_thema_name:""

    Flickable {
        anchors.fill: parent
        contentHeight: 6 * 32 + 12
        Repeater {
            model:7
            delegate: Noun_Item {
                x:6
                y: index*(height + 6)
                text: {
                    switch(index) {
                    case 0:return qsTr("Thema count : ") + thema_count + settings.i18n_empty_string
                    case 1:return qsTr("Total word count : ") + themaModel.total_word_count + settings.i18n_empty_string
                    case 2:return qsTr("Best Thema : ")  + best_thema_name + settings.i18n_empty_string
                    case 3:return qsTr("Inert themas : ")  + inert_thema_count + settings.i18n_empty_string
                    case 4:return qsTr("Golden themas : ")  + golden_thema_count + settings.i18n_empty_string
                    case 5:return qsTr("Silver themas : ")  + silver_thema_count + settings.i18n_empty_string
                    case 6:return qsTr("Rusty themas : ")  + rusty_thema_count + settings.i18n_empty_string
                    }
                }
            }
        }
    }
}
