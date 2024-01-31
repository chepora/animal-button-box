
set(SRC_FILES anibubox.c
            anibubox_sm.c
            ./include/anibubox.h
        )

add_library(anibubox ${SRC_FILES})

target_link_libraries(anibubox pico_stdlib button led pio adc update sleepy_time piezo)
target_include_directories(anibubox PUBLIC ./include/)
