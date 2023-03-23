cmake_minimum_required(VERSION 3.12)
project(main)

SET(CMAKE_C_STANDARD 99)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET(CMAKE_C_COMPILER D:\\Coding\\mingw64\\bin\\gcc.exe)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(CMAKE_C_COMPILER /usr/bin/gcc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/inc)


file(GLOB_RECURSE DIR_SRC "src/*.c")


#设置可执行文件的输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(-g)

#生成可执行文件
add_executable(${PROJECT_NAME} ${DIR_SRC})

target_link_libraries(${PROJECT_NAME} "m")