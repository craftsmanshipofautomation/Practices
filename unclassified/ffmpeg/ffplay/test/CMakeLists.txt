project(test)
include_directories(${ROOT_SOURCE_DIR})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
message(STATUS ${SRC_FILES})
set(exe_list ${exe_list})
foreach(src ${SRC_FILES})
    string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/" "" _src ${src})
    string(REGEX REPLACE ".cpp" "" exe ${_src})
    set(exe_list ${exe} ${exe_list})
    message(STATUS ${exe})
endforeach(src)

find_package(GTest REQUIRED)

set(libs ff ${GTEST_LIBRARIES})
foreach(exe ${exe_list})
    message(STATUS "[exe]: " ${exe})
    add_executable(${exe} ${exe}.cpp)
    TARGET_LINK_LIBRARIES(${exe} ${libs})
endforeach(exe)

add_subdirectory(c)

configure_file(testmp3_2.mp3 testmp3_2.mp3 copy COPYONLY)
configure_file(testmp3_2.mp3 c/testmp3_2.mp3 copy COPYONLY)