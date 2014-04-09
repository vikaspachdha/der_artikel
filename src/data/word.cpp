//******************************************************************************
/*! \file word.cpp Implementation of \ref Word_C
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
// Declaration
#include "word.h"

//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
Word_C::Word_C(QObject* parent): QObject(parent),
_text(""),
_artikel(Article_C::INVALID),
_user_artikel(Article_C::INVALID)
{
}

//******************************************************************************
/*! \brief Sets user article.
 *
 *  \details Signal \ref Word_C::userArticleChanged "userArticleChanged" is emitted
 *  when user assigned article changes.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] article : New article value to set.
 ******************************************************************************/
void Word_C::setUserArtikel(Article_C::Artikel article)
{
    if(_user_artikel != article) {
        _user_artikel = article;
        emit userArticleChanged();
    }
}

//******************************************************************************
/*! \brief Reads the word data from a file.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] element : Xml node to read from.
 *
 *  \return bool : Returns whether read was a success.
 *  \retval success status.
 *                      <ul>
 *                         <li> False = Failure
 *                         <li> True = Success
 *                      </ul>
 ******************************************************************************/
bool Word_C::read(const QDomElement &element)
{
    bool success = false;
    if(!element.isNull()) {
        _text = element.firstChildElement("WordText").text();
        success = !_text.isEmpty();
        _description = element.firstChildElement("Description").text();

        int article_value = element.firstChildElement("Artikel").text().toInt(&success);
        if(success) {
            switch(article_value) {
            case Article_C::DAS:
            case Article_C::DER:
            case Article_C::DIE:
            case Article_C::NA:
                _artikel = (Article_C::Artikel) article_value;
                break;
            default:
                success = false;
                break;
            }
        }
    }
    return success;
}

//******************************************************************************
/*! \brief Writes the word data to xml node.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] element : Xml node to write data under.
 *
 *  \return bool : Returns whether write was a success.
 *  \retval success status.
 *                      <ul>
 *                         <li> False = Failure
 *                         <li> True = Success
 *                      </ul>
 ******************************************************************************/
bool Word_C::write(QDomElement &element)
{
    bool success = false;

    if( !element.isNull()) {
        QDomDocument domDocument = element.ownerDocument();

        if(!domDocument.isNull() && !_text.isEmpty() && _artikel != Article_C::INVALID) {
            QDomElement dom_word = domDocument.createElement("Word");

            QDomElement dom_text = domDocument.createElement("WordText");
            QDomText text_word = domDocument.createTextNode(_text);
            dom_text.appendChild(text_word);
            dom_word.appendChild(dom_text);

            QDomElement dom_description = domDocument.createElement("Description");
            QDomText text_description = domDocument.createTextNode(_description);
            dom_description.appendChild(text_description);
            dom_word.appendChild(dom_description);

            QDomElement dom_artikel = domDocument.createElement("Artikel");
            QDomText artikel_code = domDocument.createTextNode(QString::number(_artikel));
            dom_artikel.appendChild(artikel_code);
            dom_word.appendChild(dom_artikel);

            element.appendChild(dom_word);
            success = true;
        }
    }

    return success;
}

//******************************************************************************
/*! \brief Checks whether user assigned article is correct or not.
 *
 *  \author Vikas Pachdha
 *
 *  \return bool : Returns whether user assigned article is correct or not.
 *  \retval success status.
 *                      <ul>
 *                         <li> False = Incorrect
 *                         <li> True = Correct
 *                      </ul>
 ******************************************************************************/
bool Word_C::isCorrect() const
{
    bool correct = false;

    if( (_artikel != Article_C::INVALID)
            && (_user_artikel != Article_C::INVALID)
            && (_artikel == _user_artikel) ) {
        correct = true;
    }

    return correct;
}
