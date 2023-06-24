cmake_minimum_required(VERSION 3.16)
project(backToTheFutureLib CXX)

set(SOURCE_FILES
    backToTheFutureLib.hpp
    backToTheFutureLib.cpp
)

add_library(backToTheFutureLib STATIC ${SOURCE_FILES})

install(TARGETS backToTheFutureLib DESTINATION ${LIB_DIR})
install(FILES backToTheFutureLib.hpp DESTINATION ${INCLUDE_DIR})