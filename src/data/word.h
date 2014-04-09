//******************************************************************************
/*! \file word.h Declaration of \ref Word_C
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
#ifndef WORD_H
#define WORD_H
#include "article.h"
#include <QDomElement>
#include <QObject>


//******************************************************************************
/*! \brief Entity class defining a word in thema file.
 *
 *  \details Correct article and descition about the word is stored with the instnace.
 *
 *  \author Vikas Pachdha
 *
 *  \see \ref Thema_C "Thema"
 ******************************************************************************/
class Word_C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString word_text READ wordText CONSTANT)
    Q_PROPERTY(Article_C::Artikel user_article READ userArtikel NOTIFY userArticleChanged)
    Q_PROPERTY(Article_C::Artikel article READ artikel CONSTANT)

public:
    Word_C(QObject* parent=0);

public:
    void setUserArtikel(Article_C::Artikel article);

    //! Returns article set by user.
    Article_C::Artikel userArtikel() const { return _user_artikel; }

    //! Returns the correct article for the noun.
    Article_C::Artikel artikel() const { return _artikel; }

    //! Returns the word text.
    QString wordText() const { return _text; }

    //! Retusn the description text for the word.
    QString description() const  { return _description; }

public:
    bool read(const QDomElement& element);
    bool write(QDomElement& element);
    bool isCorrect() const;

signals:
    //! Emitted when user article is changed.
    void userArticleChanged();

private:
    //! Stores word text.
    QString _text;
    //! Stores word descrition.
    QString _description;
    //! Stores correct article
    Article_C::Artikel _artikel;
    //! Stores user assigned article.
    Article_C::Artikel _user_artikel;

private:
    friend class ThemaBuilder_C;
};
#endif // WORD_H
