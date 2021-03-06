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

Page_panel {
    page_id:Manager.WORDS_PAGE
    Label {
        id: level_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Article") + settings.i18n_empty_string
    }

    Column {
        id: article_col
        anchors.top: level_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:der_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: words_page.selected_article === Article.DER
            visible: manager.game_level !== Manager.PRACTICE
            buttonText: qsTr("Der") + settings.i18n_empty_string
            onActivated:  {
                words_page.selected_article = Article.DER
            }
        }

        Button {
            id:die_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: words_page.selected_article === Article.DIE
            visible: manager.game_level !== Manager.PRACTICE
            buttonText: qsTr("Die") + settings.i18n_empty_string
            onActivated:  {
                words_page.selected_article = Article.DIE
            }
        }

        Button {
            id:das_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: words_page.selected_article === Article.DAS
            visible: manager.game_level !== Manager.PRACTICE
            buttonText: qsTr("Das") + settings.i18n_empty_string
            onActivated: {
                words_page.selected_article = Article.DAS
            }
        }

        Button {
            id:info_mode_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            isDown: words_page.info_mode === true
            buttonText: qsTr("Info") + settings.i18n_empty_string
            onActivated: {
                if(manager.game_level === Manager.PRACTICE) {
                    words_page.info_mode = !words_page.info_mode
                } else {
                    words_page.info_mode = true
                }
            }
        }

    }


    Command_item
    {
        id: finish_cmd
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        enabled: visible
        visible: manager.game_level !== Manager.PRACTICE
        cmd_text: qsTr("Finish") + settings.i18n_empty_string
        icon_name: "finish"
        onCommandActivated: {
            manager.current_page = Manager.RESULT_PAGE
        }
    }

}
