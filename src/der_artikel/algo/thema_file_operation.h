//******************************************************************************
/*! \file file.h Declaration/Implementation of \ref SomeClass
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
#ifndef THEMAFILEOPERATION_I_H
#define THEMAFILEOPERATION_I_H

//******************************************************************************
/*! \brief Thema file operation interface.
 *
 *  \details Algorithm defines the file operation while updating thema from remote
 *  folders.
 *
 *  \author Vikas Pachdha
 *
 *  \see \ref ThemaAddOperation_C, \ref ThemaDeleteOperation_C, \ref ThemaReplaceOperation_C
 ******************************************************************************/
class ThemaFileOperation_I
{
public:
    ThemaFileOperation_I() {}
    virtual ~ThemaFileOperation_I() {}

public:
    virtual bool execute() = 0;
};



#endif // THEMAFILEOPERATION_I_H
