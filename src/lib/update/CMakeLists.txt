
set(SRC_FILES update.c
              ./include/update.h
        )

add_library(update ${SRC_FILES})

target_link_libraries(update pico_stdlib hardware_gpio)
target_include_directories(update PUBLIC ./include/)
