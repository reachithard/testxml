//
// Created by 罗林one on 2021/4/4.
//

#ifndef TESTXML_TXMLDECODER_H
#define TESTXML_TXMLDECODER_H

#include "XMLTraits.h"

template<typename DOC>
class TXMLDecoder {
protected:
    typedef DOC doc_type;
    typedef TXMLDecoder<DOC> xdoc_type;
public:
    TXMLDecoder(const doc_type *parent, const char* key){

    }

    TXMLDecoder() {}

    virtual ~TXMLDecoder(){

    }

    doc_type* find(const char* key, doc_type* tmp){
        doc_type *obj = static_cast<doc_type*>(this);
        if (nullptr != key) {
            obj = obj->Find(key, tmp);
//            if (NULL == obj && Extend::Mandatory(ext)) {
//                decode_exception("mandatory key not found", key);
//            }
        }
        return obj;
    }

    template<class T>
    typename x_enable_if<T::__Serial_Value, bool>::type decode(const char* key, T& val){
        doc_type tmp;
        doc_type *obj = find(key, &tmp);
        if (nullptr == obj) {
            return false;
        }

        val.SerialDecode(*obj, val);
        return true;
    }
protected:
    const doc_type* _parent;
    const char* _key;
    int _index;
};


#endif //TESTXML_TXMLDECODER_H
