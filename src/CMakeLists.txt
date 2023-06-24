add_subdirectory(backToTheFutureLib)

add_executable(BackToTheFuture main.cpp)

target_link_libraries(BackToTheFuture backToTheFutureLib)
install(TARGETS BackToTheFuture DESTINATION ${BIN_DIR})