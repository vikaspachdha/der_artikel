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

Page_panel
{
    page_id:Manager.RESULT_PAGE

    Label {
        id: result_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Options") + settings.i18n_empty_string
    }

    Column {
        id: view_type_col
        anchors.top: result_lbl.bottom
        anchors.topMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:replay_btn
            width:parent.width
            // score < 0 means no result is produced so far.
            visible: manager.thema_selected && (currentResult.score > -1)
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Replay") + settings.i18n_empty_string
            onActivated: manager.current_page = Manager.WORDS_PAGE
        }

        Item {
            id:spacer
            width:parent.width
            height: 20
            visible:replay_btn.visible
        }

        Button {
            id:correction_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Corrections") + settings.i18n_empty_string
            isDown: result_page_instance.view_type === ResultPage.VIEW_CORRECTION
            onActivated: result_page_instance.view_type = ResultPage.VIEW_CORRECTION
        }

        Button {
            id:mistakes_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Mistakes") + settings.i18n_empty_string
            isDown: result_page_instance.view_type === ResultPage.VIEW_MISTAKES
            onActivated: result_page_instance.view_type = ResultPage.VIEW_MISTAKES
        }
    }
}
