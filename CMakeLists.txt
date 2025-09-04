if(CONFIG_CANOPENNODE_V4)

zephyr_syscall_include_directories(lib)   

endif()

zephyr_include_directories(.)
zephyr_include_directories(lib)

add_subdirectory(lib)
#add_subdirectory(boards)
#add_subdirectory(drivers)

