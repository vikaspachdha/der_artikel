//******************************************************************************
/*! \file strict_result_algo.h Declaration of \ref StrictResultAlgo_C
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
#ifndef STRICT_RESULT_ALGO_H
#define STRICT_RESULT_ALGO_H

// Project includes
#include "result_algo.h"

//******************************************************************************
/*! \brief Algorithm class for Easy mode.
 *
 *  \details Algorithm decides the scoring and time alocated to complete a thema.
 *
 *  \author Vikas Pachdha
 *
 *  \see \ref ModerateResultAlgo_C , \ref EasyResultAlgo_C
 ******************************************************************************/
class StrictResultAlgo_C : public ResultAlgo_I
{
public:
    StrictResultAlgo_C();

public:
    virtual void Calculate(Thema_I& thema, Result_C& result);
    virtual int playTime(Thema_I& thema);
};

#endif // STRICT_RESULT_ALGO_H
