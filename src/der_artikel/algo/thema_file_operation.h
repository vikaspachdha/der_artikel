#ifndef THEMAFILEOPERATION_I_H
#define THEMAFILEOPERATION_I_H

class ThemaFileOperation_I
{
public:
    ThemaFileOperation_I() {}
    virtual ~ThemaFileOperation_I() {}

public:
    virtual bool execute() = 0;
};



#endif // THEMAFILEOPERATION_I_H
