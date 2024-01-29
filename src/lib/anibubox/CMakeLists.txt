
set(SRC_FILES anibubox.c
            anibubox_sm.c
            ./include/anibubox.h
            ./include/anibubox_sm.h
        )

add_library(anibubox ${SRC_FILES})

target_link_libraries(anibubox pico_stdlib button led pio)
target_include_directories(anibubox PUBLIC ./include/)
