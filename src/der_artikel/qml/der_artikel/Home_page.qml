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
    page_id:Manager.HOME_PAGE
    ListModel
    {
        id: page_model
        ListElement { title:QT_TRANSLATE_NOOP("HomePage","Thema"); icon_src:"qrc:/res/resources/thema.png";src_page_id:Manager.THEMA_PAGE}
        ListElement { title:QT_TRANSLATE_NOOP("HomePage","Result"); icon_src:"qrc:/res/resources/result.png";src_page_id:Manager.RESULT_PAGE}
        ListElement { title:QT_TRANSLATE_NOOP("HomePage","Statistics"); icon_src:"qrc:/res/resources/stats.png";src_page_id:Manager.STATS_PAGE}
        ListElement { title:QT_TRANSLATE_NOOP("HomePage","Help"); icon_src:"qrc:/res/resources/help.png";src_page_id:Manager.HELP_PAGE}
        ListElement { title:QT_TRANSLATE_NOOP("HomePage","Settings"); icon_src:"qrc:/res/resources/settings.png";src_page_id:Manager.SETTINGS_PAGE}
        ListElement { title:QT_TRANSLATE_NOOP("HomePage","About"); icon_src:"qrc:/res/resources/about.png";src_page_id:Manager.ABOUT_PAGE}
    }

    GridView {
        id: pageItemGrid
        anchors.fill: parent
        model:page_model
        cellWidth:settings.page_item_width + 12
        cellHeight:settings.page_item_height + 12
        delegate: Page_item {
            width:settings.page_item_width
            height:settings.page_item_height
            label_text:qsTranslate("HomePage",title) + settings.i18n_empty_string
            page_icon: icon_src
        }
    }
}
