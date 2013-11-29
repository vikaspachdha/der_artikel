#ifndef MODERATE_RESULT_ALGO_H
#define MODERATE_RESULT_ALGO_H

#include "result_algo.h"


class ModerateResultAlgo_C : public ResultAlgo_I
{
public:
    ModerateResultAlgo_C();

public:
    virtual void Calculate(Thema_I& thema, Result_C& result);
};
#endif // MODERATE_RESULT_ALGO_H
