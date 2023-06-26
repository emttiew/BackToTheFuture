cmake_minimum_required(VERSION 3.16)
project(ArchiveUtils CXX)

set(SOURCE_FILES
    Compress.cpp
    Decompress.cpp
)

add_library(ArchiveUtils STATIC ${SOURCE_FILES})

add_custom_target(BuildZipLib ALL 
                   COMMAND ${CMAKE_MAKE_PROGRAM}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zipLib
                   COMMENT "Original ZipLib makefile target")

add_library(ZipLib SHARED IMPORTED)

set(ZIPLIB_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/zipLib/Bin/libzip.so)

set_target_properties(ZipLib PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${ZIPLIB_LIBRARY}")

add_dependencies(ZipLib BuildZipLib) # So that anyone linking against TheLib causes BuildTheLib to build first

target_link_libraries(ArchiveUtils PRIVATE ZipLib)

#file(COPY ${ZIPLIB_LIBRARY} DESTINATION ${LIB_DIR})

install(TARGETS ArchiveUtils DESTINATION ${LIB_DIR})
install(FILES Decompress.hpp Compress.hpp DESTINATION ${INCLUDE_DIR})

SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_DIR}")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_DIR}")