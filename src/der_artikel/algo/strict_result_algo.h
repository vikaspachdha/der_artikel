#ifndef STRICT_RESULT_ALGO_H
#define STRICT_RESULT_ALGO_H

#include "result_algo.h"

class StrictResultAlgo_C : public ResultAlgo_I
{
public:
    StrictResultAlgo_C();

public:
    virtual void Calculate(Thema_I& thema, Result_C& result);
    virtual int playTime(Thema_I& thema);
};

#endif // STRICT_RESULT_ALGO_H
