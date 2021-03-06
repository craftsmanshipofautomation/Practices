cmake_minimum_required(VERSION 3.10)
project(practice)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
message(STATUS ${SRC_FILES})
set(exe_list ${exe_list})
foreach(src ${SRC_FILES})
    string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/" "" _src ${src})
    string(REGEX REPLACE ".cpp" "" exe ${_src})
    set(exe_list ${exe} ${exe_list})
    message(STATUS ${exe})
endforeach(src)

set(libs gtest gtest_main gmock gmock_main pthread)
foreach(exe ${exe_list})
    message(STATUS "[exe]: " ${exe})
    add_executable(${exe} ${exe}.cpp)
    TARGET_LINK_LIBRARIES(${exe} ${libs})
endforeach(exe)