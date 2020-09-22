cmake_minimum_required (VERSION 2.8.11)
project (sftp)

add_executable (sftp-client test.cpp sftp-client.cpp)
target_link_libraries (sftp-client LINK_PUBLIC ssh)