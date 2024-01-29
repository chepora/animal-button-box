add_subdirectory(lib)

add_executable(anibubox_poc
                main.c
                board.h)

set(PICO_BOARD "adafruit_feather_rp2040")
target_link_libraries(anibubox_poc pico_stdlib hardware_gpio anibubox)

# disable usb output, enable uart output
pico_enable_stdio_usb(anibubox_poc 0)
pico_enable_stdio_uart(anibubox_poc 1)

pico_add_extra_outputs(anibubox_poc)
