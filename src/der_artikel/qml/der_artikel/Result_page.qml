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
    page_id:Manager.RESULT_PAGE
    id: rectangle1

    Label {
        id: title_label
        text: (list_view.count>0 ? qsTr("Mistakes") : qsTr("No Mistakes")) + settings.i18n_empty_string
        text_color:color_palette.color_font_02
        background_gradient: Gradient {
            GradientStop {position:0.0;color:color_palette.color_btn_02}
            GradientStop {position:0.1;color:color_palette.color_btn_01}
            GradientStop {position:0.9;color:color_palette.color_btn_01}
            GradientStop {position:1.0;color:color_palette.color_btn_02}
        }
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Label {
        id: header_label_incorrect
        text: qsTr("Incorrect   ") + settings.i18n_empty_string
        text_color:color_palette.color_font_02
        visible:list_view.count > 0
        text_h_alignment:Text.AlignRight
        background_gradient: Gradient {
            GradientStop {position:0.0;color:color_palette.color_btn_02}
            GradientStop {position:0.1;color:color_palette.color_btn_01}
            GradientStop {position:0.9;color:color_palette.color_btn_01}
            GradientStop {position:1.0;color:color_palette.color_btn_02}
        }
        anchors {
            top: title_label.bottom
            topMargin: 2
            left: parent.left
            right: parent.horizontalCenter
            rightMargin: 4
        }
    }

    Label {
        id: header_label_correct
        text: qsTr("    Correct") + settings.i18n_empty_string
        text_color:color_palette.color_font_02
        visible:list_view.count > 0
        text_h_alignment:Text.AlignLeft
        background_gradient: Gradient {
            GradientStop {position:0.0;color:color_palette.color_btn_02}
            GradientStop {position:0.1;color:color_palette.color_btn_01}
            GradientStop {position:0.9;color:color_palette.color_btn_01}
            GradientStop {position:1.0;color:color_palette.color_btn_02}
        }
        anchors {
            top: title_label.bottom
            topMargin: 2
            left: parent.horizontalCenter
            leftMargin: 4
            right: parent.right
        }
    }

    ListView {
        id: list_view

        anchors.top: header_label_correct.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        spacing:4
        clip:true
        model: currentResult.incorrectWordsModel
        delegate: Result_item {
            //height: 24
            right_text: articleText(article)+" " + word_text
            left_text: word_text
            correct_article: article
        }
    }

    function onResultUpdated()
    {
        title_label.text = currentResult.grade_string
        score_label.text = currentResult.score_string
        mistakes_label.text = currentResult.mistake_string
        unplayed_label.text = currentResult.unplayed_string
    }
}
