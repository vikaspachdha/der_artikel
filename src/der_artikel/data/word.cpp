#include "word.h"

Word_C::Word_C():
_text(""),
_artikel(ARTIKEL::INVALID),
_user_artikel(ARTIKEL::INVALID)
{
}

bool Word_C::Read(const QDomElement &element)
{
    return true;
}

bool Word_C::IsCorrect() const
{
    bool correct = false;

    if( (_artikel != ARTIKEL::INVALID)
            && (_user_artikel != ARTIKEL::INVALID)
            && (_artikel == _user_artikel) ) {
        correct = true;
    }

    return correct;
}
