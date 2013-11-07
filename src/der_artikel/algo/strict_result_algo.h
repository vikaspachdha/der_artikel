#ifndef STRICT_RESULT_ALGO_H
#define STRICT_RESULT_ALGO_H

#include "result_algo.h"

class StrictResultAlgo_C : public ResultAlgo_I
{
public:
    StrictResultAlgo_C();

public:
    virtual void Calculate(Thema_I& thema, Result_C& result);
};

#endif // STRICT_RESULT_ALGO_H
