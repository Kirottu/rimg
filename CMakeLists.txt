cmake_minimum_required(VERSION 3.11)
project(rimg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall -Wextra")

set(CUSTOMIZE_BUILD ON)

set(SUPPORT_FILEFORMAT_BMP ON)
set(SUPPORT_FILEFORMAT_TGA ON)
set(SUPPORT_FILEFORMAT_JPG ON)
set(SUPPORT_FILEFORMAT_GIF ON)
set(SUPPORT_FILEFORMAT_PSD ON)
set(SUPPORT_FILEFORMAT_PKM ON)
set(SUPPORT_FILEFORMAT_PVR ON)

set(SUPPORT_TRACELOG OFF)

add_subdirectory("3rdparty/raylib")

file(GLOB MY_SOURCES 
  "src/*.c" 
)

add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE "include/${PROJECT_NAME}"
)

target_link_libraries(${PROJECT_NAME} raylib)
