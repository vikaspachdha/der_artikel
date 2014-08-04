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
    page_id: Manager.THEMA_PAGE
    Label {
        id: level_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Game Level") + settings.i18n_empty_string
    }

    Column {
        id: game_level_col
        anchors.top: level_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6


        Button {
            id:easy_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: manager.game_level === Manager.EASY
            buttonText: qsTr("Easy") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.EASY
        }

        Button {
            id:moderate_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: manager.game_level === Manager.MODERATE
            buttonText: qsTr("Moderate") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.MODERATE
        }

        Button {
            id:expert_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: manager.game_level === Manager.EXPERT
            buttonText: qsTr("Expert") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.EXPERT
        }

        Button {
            id:practice_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: manager.game_level === Manager.PRACTICE
            buttonText: qsTr("Practice") + settings.i18n_empty_string
            onActivated: manager.game_level = Manager.PRACTICE
        }

    }

    Command_item
    {
        id: start_cmd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        enabled: themaModel.selection_state===ThemaModel.SINGLE_SELECTION
        cmd_text: qsTr("Play") + settings.i18n_empty_string
        icon_name: "start"
        onCommandActivated: {
            manager.current_page = Manager.WORDS_PAGE
        }
    }
}
