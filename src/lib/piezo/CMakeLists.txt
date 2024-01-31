set(SRC_FILES piezo.c
              ./include/piezo.h
        )

add_library(piezo ${SRC_FILES})

target_link_libraries(piezo pico_stdlib hardware_gpio hardware_pwm hardware_clocks)
target_include_directories(piezo PUBLIC ./include/)
