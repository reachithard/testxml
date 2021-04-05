//
// Created by 罗林one on 2021/4/4.
//

#ifndef TESTXML_XMLTRAITS_H
#define TESTXML_XMLTRAITS_H

template<bool B, class T = void>
struct x_enable_if {};
template <class T>
struct x_enable_if<true, T> { typedef T type; };

#endif //TESTXML_XMLTRAITS_H
