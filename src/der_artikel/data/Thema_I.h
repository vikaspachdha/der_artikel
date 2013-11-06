#ifndef THEMA_I_H
#define THEMA_I_H

class ResultAlgo_I;
class Word_C;

class Thema_I
{
public:
    Thema_I() {}
    ~Thema_I() {}

public:
    virtual unsigned int GetWordCount() const = 0;
    virtual const Word_C* GetWord(unsigned int index) const = 0;
};

#endif // THEMA_I_H
