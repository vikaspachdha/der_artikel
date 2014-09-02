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
    id: word_page_root
    page_id:Manager.WORDS_PAGE

    Flickable
    {
        id: wordsFrame
        anchors.fill: word_page_root
        anchors.rightMargin: 16
        clip: true
        contentHeight: wordFlow.childrenRect.height
        Flow
        {
            id: wordFlow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: 6
        }
    }

    Scroll_bar {
        id: scroll_bar
        anchors {
            top:wordsFrame.top
            topMargin: 6
            bottom:wordsFrame.bottom
            bottomMargin: 6
            right: word_page_root.right
            rightMargin: 4
        }
        orientation: Qt.Vertical
        position: wordsFrame.visibleArea.yPosition
        pageSize: wordsFrame.visibleArea.heightRatio

        opacity: wordsFrame.movingVertically ? 0.7 : 0
    }


    function addWord(word_object,itemText,desc)
    {
        var wordComponent = Qt.createComponent("Word_item.qml");
        if(wordComponent.status == Component.Ready) {
            var wordItem = wordComponent.createObject(wordFlow);
            wordItem.word = word_object;
            wordItem.wordText = itemText;
            wordItem.description_text = desc;
        }

        return wordItem;
    }
}
