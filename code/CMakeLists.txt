project(code)
add_executable(code src/main.cpp)
target_link_libraries(code ${SDL2_LIBRARY})
install(TARGETS code RUNTIME DESTINATION ${BIN_DIR})
