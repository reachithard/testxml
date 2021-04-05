//
// Created by 罗林one on 2021/4/4.
//

#ifndef TESTXML_XMLDECODER_H
#define TESTXML_XMLDECODER_H

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

#include "libxml/parser.h"

#include "Util.h"
#include "TXMLDecoder.h"

using namespace std;

struct cmp_str {
    bool operator()(const unsigned char *a, const unsigned char *b) const {
        return xmlStrcmp(a, b) < 0;
    }
};

class XMLDecoder : public TXMLDecoder<XMLDecoder> {
    typedef xmlDocPtr XML_READER_DOCUMENT;
    typedef xmlNodePtr XML_READER_NODE;
public:
    friend class TXMLDecoder<XMLDecoder>;
    using xdoc_type::decode;

public:
    XMLDecoder(std::string& str, bool isfile = false){
        std::string err;
        _xml_data = NULL;

        do {
            try {
                int leng = 0;
                string strbuffer;
                if (isfile) {
                    std::ifstream fs(str.c_str(), std::ifstream::binary);
                    if (!fs) {
                        err = "Open file["+str+"] fail.";
                        break;
                    }
                    std::string data((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
                    _xml_data = new char[data.length()+1];
                    leng = data.length();
                    memcpy(_xml_data, data.c_str(), data.length());
                    _xml_data[leng] = '\0';
                } else  {
                    _xml_data = new char[str.length()+1];
                    leng = str.length();
                    memcpy(_xml_data, str.c_str(), str.length());
                    _xml_data[leng] = '\0';
                }
                std::cout << _xml_data << std::endl;
                cout << "end" << endl;
                _doc = xmlParseMemory(_xml_data, leng);
                if (_doc == NULL ) {

                    err = "parse string["+str+"] fail.";
                    break;
                }
            }  catch (const std::exception&e) {
                err = std::string("parse xml fail. unknow exception. err=")+e.what();
            }

            if (!err.empty()) {
                break;
            }

            _node = xmlDocGetRootElement(_doc);

            init();
            return;
        } while (false);

        xmlFreeDoc(_doc);
        _doc = NULL;
        if (NULL != _xml_data) {
            delete []_xml_data;
            _xml_data = NULL;
        }
        throw std::runtime_error(err);
    }

    XMLDecoder* Find(const char*key, XMLDecoder *tmp) {
        node_index::iterator iter;
        if (_childs_index.end() != (iter=_childs_index.find((const unsigned char*)key))) {
            tmp->_key = key;
            tmp->_parent = this;
            tmp->_node = _childs[iter->second];
            //tmp->init();
            return tmp;
        } else {
            return NULL;
        }
    }

    template<class T>
    typename x_enable_if<Numeric<T>::is_integer, bool>::type decode(const char *key, T &val){
        bool exists;
        std::string v = get_val(key, exists);
        cout << "getval decode " << v << endl;
        if (!exists) {
//            if (Extend::Mandatory(ext)) {
//                decode_exception("mandatory key not found", key);
//            }
            return false;
        }
        if (Util::atoi(v, val)) {
            return true;
        } else {
            //decode_exception("parse int fail. not integer or overflow", key);
            return false;
        }
    }

private:
    XMLDecoder():xdoc_type(NULL, ""),_doc(NULL),_node(NULL) {
        init();
    }
//    XMLDecoder(const XML_READER_NODE* val, const XMLDecoder *parent, const char*key, size_t iter=0):xdoc_type(parent, key),_doc(NULL),_node(val),_iter(iter) {
//        //init();
//    }
//    XMLDecoder(const XML_READER_NODE* val, const XMLDecoder *parent, size_t index):xdoc_type(parent, index),_doc(NULL),_node(val) {
//        //init();
//    }

    void init() {
        if (NULL != _node) {
            XML_READER_NODE tmp = xmlFirstElementChild(_node);
            for (size_t i=0; tmp; tmp=xmlNextElementSibling(tmp), ++i) {
                std::cout << "map" << tmp->name << std::endl;
                _childs.push_back(tmp);
                _childs_index[tmp->name] = i;
            }
        }
    }

    std::string get_val(const char *key, bool &exists) {
        exists = true;
        if (NULL == key) {
            return (const char*)xmlNodeListGetString(_doc, _node->xmlChildrenNode, 1);
        } else {
            node_index::iterator iter;
            if (_childs_index.end()!=(iter=_childs_index.find((const unsigned char*)key))) {
                return (const char*)xmlNodeListGetString(_doc, _childs[iter->second]->xmlChildrenNode, 1);
            } else {
//                rapidxml::xml_attribute<char> *attr = _node->first_attribute(key);
//                if (NULL != attr) {
//                    return attr->value();
//                }
            }
        }
        exists = false;
        return "";
    }

    XML_READER_DOCUMENT _doc;
    char *_xml_data;

    typedef std::map<const unsigned char*, size_t, cmp_str> node_index; // index of _childs

    XML_READER_NODE _node;           // current node
    std::vector<XML_READER_NODE> _childs;  // childs
    node_index _childs_index;
    size_t _iter;
};


#endif //TESTXML_XMLDECODER_H
