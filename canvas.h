#ifndef CANVAS_H
#define CANVAS_H
#include <Arduino.h>

const int C_SIZE = 16;
uint16_t pixels[C_SIZE][C_SIZE]; //canvas
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
      if (cur_y < C_SIZE - 1) cur_y++;
      break;

    case 'L': //left
      if (cur_x > 0) cur_x--;
      break;

    case 'R': //right
      if (cur_x < C_SIZE - 1) cur_x++;
      break;
  }
}

void paintPixel()
{
  pixels[cur_y][cur_x] = currentColor;
}

void initCanvas() // set the canvas basic color to white
{
   for(int Xpos = 0; Xpos < 16; Xpos++) //x position
  {
    for(int Ypos = 0; Ypos < 16; Ypos++) // y position
    {
      pixels[Ypos][Xpos] = 0xffff;
    }
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

#endif