#ifndef STRICT_RESULT_ALGO_H
#define STRICT_RESULT_ALGO_H

#include "result_algo.h"

/**
 * @brief
 *
 */
class StrictResultAlgo_C : public ResultAlgo_I
{
public:
/**
 * @brief
 *
 */
    StrictResultAlgo_C();

public:
    /**
     * @brief
     *
     * @param thema
     * @param result
     */
    virtual void Calculate(Thema_I& thema, Result_C& result);
    /**
     * @brief
     *
     * @param thema
     * @return int
     */
    virtual int playTime(Thema_I& thema);
};

#endif // STRICT_RESULT_ALGO_H
