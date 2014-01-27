#ifndef THEMA_I_H
#define THEMA_I_H

class ResultAlgo_I;
class Word_C;

/**
 * @brief
 *
 */
class Thema_I
{
public:
/**
 * @brief
 *
 */
    Thema_I() {}
    /**
     * @brief
     *
     */
    ~Thema_I() {}

public:
    /**
     * @brief
     *
     * @return unsigned int
     */
    virtual unsigned int GetWordCount() const = 0;
    /**
     * @brief
     *
     * @param index
     * @return const Word_C
     */
    virtual const Word_C* GetWord(int index) const = 0;
    /**
     * @brief
     *
     * @param points
     */
    virtual void AddExperiencePoints(int points) = 0;
    /**
     * @brief
     *
     * @param points
     */
    virtual void DeductExperiencePoints(int points) = 0;
    /**
     * @brief
     *
     */
    virtual void ClearUserInput() = 0;
};

#endif // THEMA_I_H
