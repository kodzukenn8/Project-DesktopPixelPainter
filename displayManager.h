#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>

const int PIXEL_S = 10;
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8
Adafruit_GC9A01A tftDisplay(TFT_CS, TFT_DC, TFT_RST);

void startDisplay()
{
  tftDisplay.begin();
  tftDisplay.fillScreen(0xFFBD);
}

void drawPixel(int c_x, int c_y, uint16_t color)
{
  tftDisplay.fillRect(40 + c_x * PIXEL_S, 40 + c_y * PIXEL_S, PIXEL_S, PIXEL_S, color);
}

void flashCursorOn(int c_x, int c_y) //cursor x and y position
{
  tftDisplay.drawRect(40 + c_x*PIXEL_S, 40 + c_y*PIXEL_S, PIXEL_S, PIXEL_S, GC9A01A_BLACK);
}

void flashCursorOff(int c_x, int c_y, uint16_t color) //cursor x and y position color of the current pixel
{
  drawPixel(c_x, c_y, color);
}

void updateCanvasDisp(const uint16_t pixelArray[C_SIZE][C_SIZE])
{
  for(int Xpos = 0; Xpos < 16; Xpos++) //x position
  {
    for(int Ypos = 0; Ypos < 16; Ypos++) // y position
    {
      tftDisplay.fillRect(40 + Xpos*PIXEL_S, 40 + Ypos*PIXEL_S, PIXEL_S, PIXEL_S, pixelArray[Ypos][Xpos]);
    }
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
    {
      tftDisplay.fillRect(x, y, boxSize, boxSize, pal[palIndex]);
    }
    else
    {
      tftDisplay.fillRect(x, y, boxSize, boxSize, 0xFFBD);
    }
  }
  tftDisplay.drawRect(115, 215, 10, 10, 0x0000);
}
#endif 