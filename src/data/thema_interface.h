//******************************************************************************
/*! \file thema_interface.h Declaration of \ref Thema_I
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
#ifndef THEMA_I_H
#define THEMA_I_H

class ResultAlgo_I;
class Word_C;


//******************************************************************************
/*! \brief Interface class to create thema implementation.
 *
 *  \author Vikas Pachdha
 *
 *  \see \ref Thema_C
 ******************************************************************************/
class Thema_I
{
public:
    Thema_I() {}
    ~Thema_I() {}

public:
    virtual unsigned int wordCount() const = 0;
    virtual const Word_C* word(int index) const = 0;
    virtual void addExperiencePoints(int points) = 0;
    virtual void deductExperiencePoints(int points) = 0;
    virtual void clearUserInput() = 0;
};

#endif // THEMA_I_H
