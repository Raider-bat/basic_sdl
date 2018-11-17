project(code)
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

add_executable(code src/main.cpp src/AbstractWindow.cpp src/Utils.cpp)

target_link_libraries(code ${SDL2_LIBRARY})
target_link_libraries(code ${GLM_LIBRARY})
target_link_libraries(code ${OPENGL_LIBRARIES})

install(TARGETS code RUNTIME DESTINATION ${BIN_DIR})
