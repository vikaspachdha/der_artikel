#ifndef RESULTALGO_I_H
#define RESULTALGO_I_H


class Thema_I;
class Result_C;

class ResultAlgo_I
{
public:
    ResultAlgo_I() {}
    virtual ~ResultAlgo_I() {}

public:
    virtual void Calculate(Thema_I& thema, Result_C& result) = 0;
    virtual int playTime(Thema_I& thema) = 0;
};

#endif // RESULTALGO_I_H
