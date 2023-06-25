add_subdirectory(archiveUtils)

add_executable(BackToTheFuture main.cpp)

target_link_libraries(BackToTheFuture ArchiveUtils pthread)

install(TARGETS BackToTheFuture DESTINATION ${BIN_DIR})
