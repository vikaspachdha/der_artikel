//******************************************************************************
/*! \file word_model.h Declaration of \ref WordModel_C
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
#ifndef WORD_MODEL_H
#define WORD_MODEL_H

// System includes
#include <QAbstractListModel>

// Forward declaration
class Word_C;


//******************************************************************************
/*! \brief Data model of words. \ref Word_C "words" are updated using
 *  WordModel_C::updateWords "updateWords".
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class WordModel_C : public QAbstractListModel
{
    Q_OBJECT

public:

    //******************************************************************************
    /*! \brief Data roles to access \ref Word_C "word" data.
     *
     *  \author Vikas Pachdha
     ******************************************************************************/
    enum ROLES_TP {
        WORD_TEXT = Qt::UserRole,
        ARTICLE,
        USER_ARTICLE
    };

public:
    explicit WordModel_C(QObject *parent = 0);
    ~WordModel_C();

public:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int,QByteArray> roleNames() const;

public:
    void updateWords(QList<const Word_C *> words);
private:
    void clearWords();
private:
    QList<const Word_C*> _words;
};

#endif // WORD_MODEL_H
