#ifndef RESULTALGO_I_H
#define RESULTALGO_I_H


class Thema_I;
class Result_C;

/**
 * @brief
 *
 */
class ResultAlgo_I
{
public:
/**
 * @brief
 *
 */
    ResultAlgo_I() {}
    /**
     * @brief
     *
     */
    virtual ~ResultAlgo_I() {}

public:
    /**
     * @brief
     *
     * @param thema
     * @param result
     */
    virtual void Calculate(Thema_I& thema, Result_C& result) = 0;
    /**
     * @brief
     *
     * @param thema
     * @return int
     */
    virtual int playTime(Thema_I& thema) = 0;
};

#endif // RESULTALGO_I_H
