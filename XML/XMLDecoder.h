//
// Created by 罗林one on 2021/4/4.
//

#ifndef TESTXML_XMLDECODER_H
#define TESTXML_XMLDECODER_H

#include "TXMLDecoder.h"

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>

#include "libxml/parser.h"

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

            //init();
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

private:
    XML_READER_DOCUMENT _doc;
    char *_xml_data;

    typedef std::map<const unsigned char*, size_t, cmp_str> node_index; // index of _childs

    XML_READER_NODE _node;           // current node
    std::vector<XML_READER_NODE> _childs;  // childs
    node_index _childs_index;
    size_t _iter;
};


#endif //TESTXML_XMLDECODER_H
