//
// Created by 罗林one on 2021/4/5.
//

#ifndef TESTXML_NUMERIC_H
#define TESTXML_NUMERIC_H

template <typename T>
struct Numeric{
    static const bool value = false;
    static const bool is_integer = false;
    static const bool is_float = false;
};

template<>
struct Numeric<int>{
    static const bool value = false;
    static const bool is_integer = true;
    static const bool is_float = false;
};

#endif //TESTXML_NUMERIC_H
