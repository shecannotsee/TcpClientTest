cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "tcp_client_test")
###################################################
set(libraries_dir "${CMAKE_SOURCE_DIR}/libraries")
set(sheIni "${libraries_dir}/sheIni")
set(sheThreadPool "${libraries_dir}/sheThreadPool")
###################################################
set(CMAKE_CXX_FLAGS "-g")# 断点无效处理方案
project(${PROJECT_NAME})
# include
include_directories(
        ${sheIni}/src
        ${sheThreadPool}/src
)
# lib
link_directories()
###################################################
file(GLOB_RECURSE SRC "${CMAKE_SOURCE_DIR}/src/*")
file(GLOB_RECURSE sheIni_src_part1 "${sheIni}/src/DataStructure/*")
file(GLOB_RECURSE sheIni_src_part2 "${sheIni}/src/Parse/*")
file(GLOB_RECURSE sheThreadPool_src_part2 "${sheIni}/src/SafeQueue/*")
file(GLOB_RECURSE sheThreadPool_src_part2 "${sheIni}/src/ThreadPool/*")
add_executable(${PROJECT_NAME}
        ${SRC}
        ${sheIni_src_part1}
        ${sheIni_src_part2}
        ${sheThreadPool_src_part1}
        ${sheThreadPool_src_part2}
        )
###################################################
# 链接库
target_link_libraries(${PROJECT_NAME} "-pthread")
