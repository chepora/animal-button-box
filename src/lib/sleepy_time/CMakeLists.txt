
set(SRC_FILES sleepy_time.c
              ./include/sleepy_time.h
        )

add_library(sleepy_time ${SRC_FILES})

target_link_libraries(sleepy_time pico_stdlib hardware_timer)
target_include_directories(sleepy_time PUBLIC ./include/)
