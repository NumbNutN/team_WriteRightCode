cmake_minimum_required(VERSION 3.12)
project(robot)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_COMPILER /usr/bin/gcc)


include_directories(${CMAKE_SOURCE_DIR}/inc)


file(GLOB_RECURSE DIR_SRC "src/*.c")


#设置可执行文件的输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(-g)

#生成可执行文件
add_executable(${PROJECT_NAME} ${DIR_SRC})

target_link_libraries(${PROJECT_NAME} "m")