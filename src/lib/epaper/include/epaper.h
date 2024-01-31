#ifndef _EPAPER_H_
#define _EPAPER_H_

#include "../DEV_Config.h"
#include "../EPD_1in54_V2.h"
#include "../GUI_Paint.h"
#include "../ImageData.h"
#include "../Debug.h"
#include <stdlib.h> // malloc() free()
#include "spi.h"

#define EP_IMAGE_SIZE 10000

typedef struct {

    uint8_t  image[EP_IMAGE_SIZE];
    uint16_t pic_width;
    uint16_t pic_height;
    uint16_t pic_width_memory;
    uint16_t pic_height_memory;
    uint16_t pic_color;
    uint16_t pic_rotate;
    uint16_t pic_mirror;
    uint16_t pic_width_byte;
    uint16_t pic_height_byte;
    uint16_t pic_scale;
} epaper_picture_t;

typedef struct {

    spi_params_t spi_params;

    uint8_t x_start; //EPD_1IN54_V2_HEIGHT-1,
    uint8_t x_end;
    uint8_t y_start; //EPD_1IN54_V2_WIDTH-1
    uint8_t y_end;

    int16_t imagesize;

    epaper_picture_t epaper_picture;

} epaper_params_t;

int EPD_1IN54_V2_start();
int epaper_paint_example();
void epaper_paint_next();

#endif