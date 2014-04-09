//******************************************************************************
/*! \file word_model.cpp Implementation of \ref WordModel_C
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
#include "word_model.h"
#include "data/word.h"
#include "log_defines.h"

/*!
 \brief

 \param parent
*/
WordModel_C::WordModel_C(QObject *parent) :
    QAbstractListModel(parent)
{
}

/*!
 \brief

 \param index
 \param role
 \return QVariant
*/
QVariant WordModel_C::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if(index.isValid()) {
        int row = index.row();
        const Word_C* word = 0;
        if( (row>=0) && row < _words.count() ) {
            word = _words.at(row);
        }

        if(word) {
            switch (role) {
            case WORD_TEXT:
                data = word->wordText();
                break;
            case ARTICLE:
                data = word->artikel();
                break;
            case USER_ARTICLE:
                data = word->userArtikel();
                break;
            default:
                break;
            }
        }
    }
    return data;
}

/*!
 \brief

 \param parent
 \return int
*/
int WordModel_C::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _words.count();
}

/*!
 \brief

 \return QHash<int, QByteArray>
*/
QHash<int, QByteArray> WordModel_C::roleNames() const
{
    QHash<int,QByteArray> roleNames;
    roleNames[WORD_TEXT] = "word_text";
    roleNames[ARTICLE] = "article";
    roleNames[USER_ARTICLE] = "user_article";
    return roleNames;
}

/*!
 \brief

 \param words
*/
void WordModel_C::UpdateWords(QList<const Word_C *> words)
{
    LOG_INFO("Word model :: Updating words.");
    beginResetModel();
    _words.clear();
    _words = words;
    endResetModel();
}
