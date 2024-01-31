#include "epaper.h"

#define EPDEBUG 1

UBYTE *BlackImage;

#define LAST_PICTURE 3

#define PIODEBUG 0

uint8_t current_picture;

int EPD_1IN54_V2_start()
{
  if(EPDEBUG) printf("EPD_1IN54_V2_test Demo\r\n");
  if(DEV_Module_Init()!=0){
    return -1;
  }

  if(EPDEBUG) printf("e-Paper Init and Clear...\r\n");
	EPD_1IN54_V2_Init();
  EPD_1IN54_V2_Clear();

  //Create a new image cache
  // Additional `*2` on the end to account for four-colour images
  UWORD Imagesize = ((EPD_1IN54_V2_WIDTH % 8 == 0)? (EPD_1IN54_V2_WIDTH / 8 ): (EPD_1IN54_V2_WIDTH / 8 + 1)) * EPD_1IN54_V2_HEIGHT * 2;
  if(EPDEBUG) printf("Imagesize was calculated as: %d\r\n", Imagesize);
  if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    if(EPDEBUG) printf("Failed to apply for black memory...\r\n");
    return -1;
  }
  if(EPDEBUG) printf("First loop done...\r\n");

  current_picture = 0;
}

int epaper_paint_example(){

	Paint_NewImage(BlackImage, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
  Paint_SetScale(2); // b&w
  if(EPDEBUG) printf("Drawing\r\n");
  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 2.Drawing on the image
  if(EPDEBUG) printf("Drawing:BlackImage\r\n");

  switch (current_picture)
  {
  case 0:
    Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    break;

  case 1:
    Paint_DrawRectangle(50, 50, 150, 150, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    break;

  case 2:
    Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    break;
  
  default:
    Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    break;
  }
  //Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  //Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  //Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  //Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  //Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  //Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //Paint_DrawString_EN(10, 0, "waveshare", &Font8, BLACK, WHITE);
  //Paint_DrawString_EN(10, 20, "hallo ima", &Font8, WHITE, BLACK);
  //Paint_DrawNum(10, 33, 123456789, &Font8, BLACK, WHITE);
  //Paint_DrawNum(10, 50, 987654321, &Font8, WHITE, BLACK);

  EPD_1IN54_V2_Display(BlackImage);
  DEV_Delay_ms(3000);

  return current_picture;

}


void epaper_paint_next(){

	Paint_NewImage(BlackImage, EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 270, WHITE);
  Paint_SetScale(2); // b&w
  if(EPDEBUG) printf("Drawing\r\n");
  //1.Select Image
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  // 2.Drawing on the image
  if(EPDEBUG) printf("Drawing:BlackImage\r\n");

  switch (current_picture)
  {
  case 0:
    Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    break;

  case 1:
    Paint_DrawRectangle(50, 50, 150, 150, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    break;

  case 2:
    
    Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    break;
  
  default:
    Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    break;
  }
  //Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  //Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  //Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  //Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  //Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  //Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  //Paint_DrawCircle(100, 100, 50, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  //Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //Paint_DrawString_EN(10, 0, "waveshare", &Font8, BLACK, WHITE);
  //Paint_DrawString_EN(10, 20, "hallo ima", &Font8, WHITE, BLACK);
  //Paint_DrawNum(10, 33, 123456789, &Font8, BLACK, WHITE);
  //Paint_DrawNum(10, 50, 987654321, &Font8, WHITE, BLACK);

  EPD_1IN54_V2_Display(BlackImage);

  //return current_picture;
  if(current_picture == LAST_PICTURE){
        current_picture = 0;
    }else current_picture++;

}

//	if(EPDEBUG) printf("Clear...\r\n");
//	//EPD_1IN54_V2_Init();
//  //EPD_1IN54_V2_Clear();
//	
//  if(EPDEBUG) printf("Goto Sleep...\r\n");
//  EPD_1IN54_V2_Sleep();
//  free(BlackImage);
//  BlackImage = NULL;
//  DEV_Delay_ms(2000);//important, at least 2s
//  // close 5V
//  if(EPDEBUG) printf("close 5V, Module enters 0 power consumption ...\r\n");
//  DEV_Module_Exit();
//
//
//  return 0;
//}
