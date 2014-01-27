#ifndef EASY_RESULT_ALGO_H
#define EASY_RESULT_ALGO_H

#include "result_algo.h"


/**
 * @brief
 *
 */
class EasyResultAlgo_C : public ResultAlgo_I
{
public:
/**
 * @brief
 *
 */
    EasyResultAlgo_C();

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
#endif // EASY_RESULT_ALGO_H
