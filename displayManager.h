#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>

#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8
Adafruit_GC9A01A tftDisplay(TFT_CS, TFT_DC, TFT_RST);

int pixel_size = 160 / canvas_size;

void drawPixel(int c_x, int c_y, uint16_t color)
{
  tftDisplay.fillRect(40 + c_x * pixel_size, 40 + c_y * pixel_size, pixel_size, pixel_size, color);
}

void flashCursorOn(int c_x, int c_y) //cursor x and y position
{
  tftDisplay.drawRect(40 + c_x*pixel_size, 40 + c_y*pixel_size, pixel_size, pixel_size, GC9A01A_BLACK);
}

void flashCursorOff(int c_x, int c_y, uint16_t color) //cursor x and y position color of the current pixel
{
  drawPixel(c_x, c_y, color);
}

void updateCanvasDisp(const uint16_t pixelArray[32][32])
{
  tftDisplay.fillScreen(0xFFBD);
  for(int Xpos = 0; Xpos < canvas_size; Xpos++) //x position
  {
    for(int Ypos = 0; Ypos < canvas_size; Ypos++) // y position
      tftDisplay.fillRect(40 + Xpos*pixel_size, 40 + Ypos*pixel_size, pixel_size, pixel_size, pixelArray[Ypos][Xpos]);
  }
}

void displayPalette(const uint16_t pal[], const int p_pos, const int p_size)
{
  int startX = 95;
  int y = 215;
  int boxSize = 10;

  for(int i = -2; i <= 2; i++)
  {
    int palIndex = p_pos + i;
    int x = startX + ((i + 2) * boxSize);

    if(palIndex >= 0 && palIndex < p_size)
      tftDisplay.fillRect(x, y, boxSize, boxSize, pal[palIndex]);
    else
      tftDisplay.fillRect(x, y, boxSize, boxSize, 0xFFBD);
  }
  tftDisplay.drawRect(115, 215, 10, 10, 0x0000);
}



#endif 