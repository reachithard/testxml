cmake_minimum_required(VERSION 3.17)
project(testxml)

set(CMAKE_CXX_STANDARD 14)
set(INCLUDEPATH
        ./ThirdParty/libxml2/include
        ./XML)
set(LIBPATH
        ./ThirdParty/libxml2/lib)

include_directories(${INCLUDEPATH})
link_directories(${LIBPATH})

add_executable(testxml main.cpp XML/TXMLDecoder.cpp XML/TXMLDecoder.h XML/XMLDecoder.cpp XML/XMLDecoder.h XML/XML.h XML/XMLTraits.h XML/Serial.h XML/l1l2_expand.h XML/Util.h XML/Numeric.h)
target_link_libraries(testxml libxml2)