#ifndef EASY_RESULT_ALGO_H
#define EASY_RESULT_ALGO_H

#include "result_algo.h"


class EasyResultAlgo_C : public ResultAlgo_I
{
public:
    EasyResultAlgo_C();

public:
    virtual void Calculate(Thema_I& thema, Result_C& result);
};
#endif // EASY_RESULT_ALGO_H
