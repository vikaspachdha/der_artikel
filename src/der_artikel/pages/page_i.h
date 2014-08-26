//******************************************************************************
/*! \file page_i.h Declaration of \ref Page_I interface.
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
#ifndef PAGE_I_H
#define PAGE_I_H

// System includes
#include <QList>
#include <QString>

// Project includes
#include "manager.h"



//******************************************************************************
/*! \brief Interface class for a Page entity.
 *
 *  \details \ref Manager_C manages the pages using this interface.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class Page_I
{
public:
    //! Constructor.
    Page_I() {}
    virtual ~Page_I() {}

public:
    //******************************************************************************
    /*! \brief Returns the page id of the page.
     *
     *  \details Detailed description
     *
     *  \author Vikas Pachdha
     *
     *  \return Manager_C::PageId_TP : Page id of the page
     ******************************************************************************/
    virtual Manager_C::PageId_TP pageId() const = 0;

    //******************************************************************************
    /*! \brief \ref Manager_C calls this method to decide whether preconditions are
     *  met to enter this page.
     *
     *  \details Implement this method to define the preconditions for the corresponding page.
     *
     *  \author Vikas Pachdha
     *
     *  \return bool : True if page can be switched. False otherwise
     ******************************************************************************/
    virtual bool canEnter() const = 0;

    //******************************************************************************
    /*! \brief \ref Manager_C calls this method to just before entering the page.
     *
     *  \details Implement this method to write initialization code for the corresponding page.
     *
     *  \author Vikas Pachdha
     ******************************************************************************/
    virtual void enter(Manager_C::PageId_TP prev_page_id) = 0;

    //******************************************************************************
    /*! \brief \ref Manager_C calls this method to decide whether conditions are
     *  met to leave this page.
     *
     *  \details Implement this method to define the conditions for the corresponding page.
     *
     *  \author Vikas Pachdha
     *
     *  \return bool : True if page can be switched off. False otherwise
     ******************************************************************************/
    virtual bool canLeave() const = 0;

    //******************************************************************************
    /*! \brief \ref Manager_C calls this method to just after leaving the page.
     *
     *  \details Implement this method to write clean up code for the corresponding page.
     *
     *  \author Vikas Pachdha
     ******************************************************************************/
    virtual void leave(Manager_C::PageId_TP next_page_id) = 0;
};

#endif // IPAGE_H
