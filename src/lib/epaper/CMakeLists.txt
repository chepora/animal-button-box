file(GLOB SRC_FILES
        ./include/epaper.h
     "*.h"
     "*.c"
)

add_library(epaper ${SRC_FILES})

target_link_libraries(epaper pico_stdlib hardware_spi spi)
target_include_directories(epaper PUBLIC ./include/)
