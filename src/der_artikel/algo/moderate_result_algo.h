#ifndef MODERATE_RESULT_ALGO_H
#define MODERATE_RESULT_ALGO_H

#include "result_algo.h"


/**
 * @brief
 *
 */
class ModerateResultAlgo_C : public ResultAlgo_I
{
public:
/**
 * @brief
 *
 */
    ModerateResultAlgo_C();

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
#endif // MODERATE_RESULT_ALGO_H
