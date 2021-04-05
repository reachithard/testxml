//
// Created by 罗林one on 2021/4/4.
//

#ifndef TESTXML_XML_H
#define TESTXML_XML_H

#include <string>

#include "XMLDecoder.h"

class XML{
public:
    template<class T>
    static void Decode(std::string& str, T& val){
        XMLDecoder decoder(str);
    }

    template<class T>
    static void DecodeFile(std::string& str, T& val){
        XMLDecoder decoder(str, true);
        decoder.decode(nullptr, val);
    }
};
#endif //TESTXML_XML_H
