if(CONFIG_ORESAT_COMMON_LIB)

zephyr_library()

zephyr_include_directories(
  .
)

zephyr_library_sources(
  board_sensors.c
)

endif()
