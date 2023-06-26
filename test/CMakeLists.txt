cmake_minimum_required(VERSION 3.16)
project(BackToTheFutureTests)

add_subdirectory(googleTest)

include_directories(${HEADERS_DIR})
include_directories(googleTest/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/decompressTest.cpp)

add_executable(backToTheFutureTests ${SOURCE_FILES})
target_link_libraries(backToTheFutureTests ArchiveUtils gtest)
install(TARGETS backToTheFutureTests DESTINATION ${BIN_DIR})
