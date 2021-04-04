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

add_executable(testxml main.cpp)
target_link_libraries(testxml libxml2)