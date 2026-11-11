#ifndef _TRIBOOL_H_
#define _TRIBOOL_H_

enum class Tribool
{
    Unknown,
    False,
    True
};

inline
bool MakeBool(const Tribool& i_value)
{
    DBG_ASSERT_MSG(i_value != Tribool::Unknown, "Casting Tribool that is unknown to bool. This is not well defined.");
    return i_value == Tribool::True;
}

inline
Tribool MakeTribool(const bool i_value)
{
    return i_value? Tribool::True : Tribool::False;
}

#endif
