cmake_minimum_required(VERSION 3.11)

# must define this
#add_definitions(-D_GNU_SOURCE)

add_executable(main main.c)
add_library(hook SHARED hook.c)
add_library(authentic SHARED authentic.c)
add_dependencies(main hook authentic)


set_property(TARGET authentic hook PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(main PRIVATE authentic)



# useless
# have to export LD_PRELOAD=./libhook.so explicitly
#set_property(
#    TARGET helloworld
#    PROPERTY
#        ENVIRONMENT LD_PRELOAD=${PROJECT_BINARY_DIR}/libhook.so)