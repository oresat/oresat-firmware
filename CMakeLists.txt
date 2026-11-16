cmake_minimum_required(VERSION 3.28.0)

zephyr_include_directories(.)
zephyr_include_directories(lib)

add_subdirectory(lib)
#add_subdirectory(boards)
#add_subdirectory(drivers)

