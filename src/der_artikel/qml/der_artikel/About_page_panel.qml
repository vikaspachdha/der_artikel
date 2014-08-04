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
    page_id:Manager.ABOUT_PAGE

    Label {
        id: info_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Info") + settings.i18n_empty_string
    }

    Column {
        id: about_level_col
        anchors.top: info_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:about_btn
            width:parent.width
            buttonText:qsTr("About") +settings.i18n_empty_string
            text_h_alignment: Text.AlignHCenter
            onActivated: {
                about_page_instance.sub_page_type = AboutPage.ABOUT
            }
        }
        Button {
            id:license_btn
            width:parent.width
            buttonText:qsTr("License") +settings.i18n_empty_string
            text_h_alignment: Text.AlignHCenter
            onActivated: {
                about_page_instance.sub_page_type = AboutPage.LICENSE
            }
        }
    }

    Label {
        id: option_lbl
        anchors.top: about_level_col.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Update") + settings.i18n_empty_string
    }

    Column {
        id: update_level_col
        anchors.top: option_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6
        Button {
            id:replay_btn
            width:parent.width
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("App") + settings.i18n_empty_string
            onActivated: {
                appUpdater.checkUpdate();
            }
        }

        Button {
            id:update_thema_btn
            width:parent.width
            buttonText:qsTr("Themas") +settings.i18n_empty_string
            text_h_alignment: Text.AlignHCenter
            onActivated: {
                themaUpdater.checkUpdate();
            }
        }
    }

}
