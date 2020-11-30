cmake_minimum_required(VERSION 3.0.0)

project(GVAR-Decoder)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CPP_SOURCE_FILES src/*.cpp)
add_executable(GVAR-Decoder ${CPP_SOURCE_FILES})

target_include_directories(GVAR-Decoder PUBLIC src)

target_compile_options(GVAR-Decoder PRIVATE -Wall -Wextra -pedantic)

target_link_libraries(GVAR-Decoder PUBLIC m)
if(WIN32 AND NOT MINGW)
    find_package(PNG CONFIG REQUIRED)
else()
    find_package(PNG REQUIRED)
endif()
target_link_libraries(GVAR-Decoder PUBLIC PNG::PNG)
