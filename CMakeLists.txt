cmake_minimum_required(VERSION 3.11)
project(rimg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("3rdparty/raylib")


file(GLOB MY_SOURCES 
  "src/*.c" 
)

add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE "include/${PROJECT_NAME}"
)

target_link_libraries(${PROJECT_NAME} raylib)
