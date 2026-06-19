#ifndef CANVAS_H
#define CANVAS_H
#include <Arduino.h>

bool x32 = false; //onyl two options 32x32 or 16x16, false is 16x16
int canvas_size = 16;
uint16_t pixels[32][32]; //canvas
int palette_size = 16;
uint16_t palette[] = {0x0821, 0x2927, 0x39e8, 0x726b, 0x7c0e, 0xa496, 0xce37, 0xef7c, 0xB2C8, 0xCD07, 0xE6AA, 0x4D68, 0x2BAA, 0x3233, 0x443E, 0x85DF}; //color palette, 16 colors for now possibly expand later, palette from lospec: https://lospec.com/palette-list/no-space-16

int cur_x = 0;
int cur_y = 0;

int palette_pos = 5;
uint16_t currentColor = palette[palette_pos];

void moveCursor(char dir)
{
  switch(dir)
  {
    case 'F': //up
      if (cur_y > 0) cur_y--;
      break;

    case 'B':  //down
      if (cur_y < canvas_size - 1) cur_y++;
      break;

    case 'L': //left
      if (cur_x > 0) cur_x--;
      break;

    case 'R': //right
      if (cur_x < canvas_size - 1) cur_x++;
      break;
  }
}
void jumpCursor(char dir)
{
  switch(dir)
  {
    case 'F': //up
      if (cur_y > 5) cur_y -= 5;
      break;

    case 'B':  //down
      if (cur_y < canvas_size - 5) cur_y += 5;
      break;

    case 'L': //left
      if (cur_x > 5) cur_x -= 5;
      break;

    case 'R': //right
      if (cur_x < canvas_size - 5) cur_x += 5;
      break;
  }
}
void paintPixel()
{
  pixels[cur_y][cur_x] = currentColor;
}

void deleteColor()
{
  pixels[cur_y][cur_x] = 0xffff;
}

void initCanvas() // set the canvas basic color to white
{
   for(int Xpos = 0; Xpos < canvas_size; Xpos++) //x position
  {
    for(int Ypos = 0; Ypos < canvas_size; Ypos++) // y position
      pixels[Ypos][Xpos] = 0xffff;
  }
}

void changePalettePos(bool dir) //palette is a 1-d array so L and R are needed, true = left, false = right
{
  if (dir && palette_pos > 0)
    {
      palette_pos--; 
      currentColor = palette[palette_pos];
    }
  else if (dir == false && palette_pos < palette_size-1)
    {
      palette_pos++; 
      currentColor = palette[palette_pos];
    }
}

void setCanvasSize()
{
  if(x32)
    canvas_size = 32;
  else
    canvas_size = 16; 
}

#endif