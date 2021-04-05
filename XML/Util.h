//
// Created by 罗林one on 2021/4/5.
//

#ifndef TESTXML_UTIL_H
#define TESTXML_UTIL_H

#include <string>

#include "Numeric.h"
#include "XMLTraits.h"

class Util{
public:
    template<class T>
    static typename x_enable_if<Numeric<T>::is_integer, bool>::type atoi(const std::string &s, T& val){
        if (s.empty()) {
            return false;
        }

        T _tmp = 0;
        size_t i = 0;
        if (s[0] == '-') {
            if (s.length() == 1) {
                return false;
            } else if (s.length()>2 && s[1]=='0') {
                return false;
            }

            for (i=1; i<s.length(); ++i) {
                if (s[i]>='0' && s[i]<='9') {
                    T _c = _tmp*10 - (s[i]-'0');
                    if (_c < _tmp) {
                        _tmp = _c;
                    } else if (i > 0) {
                        return false; // overflow
                    }
                } else {
                    return false;
                }
            }
        } else {
            if (s[0] == '+') {
                ++i;
            }
            if (s[i]=='0' && i+1<s.length()) {
                return false;
            }
            for (; i<s.length(); ++i) {
                if (s[i]>='0' && s[i]<='9') {
                    T _c = _tmp*10 + (s[i]-'0');
                    if (_c > _tmp) {
                        _tmp = _c;
                    } else if (i > 0) {
                        return false; // overflow
                    }
                } else {
                    return false;
                }
            }
        }

        val = _tmp;
        return true;
    }
};

#endif //TESTXML_UTIL_H
