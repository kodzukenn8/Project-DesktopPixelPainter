#include "canvas.h"
#include "displayManager.h"
#include "inputRegistry.h"


bool cursorVis = false;
unsigned long lastFlash = 0;
const unsigned long CURSOR_FLASH_TIME = 1000;

enum Mode
{
  DRAW_MODE,
  COLORPICK_MODE,
  MENU_MODE
};
Mode currentMo = DRAW_MODE;

void setup() 
{
  startDisplay();
  initCanvas();
  setupInputs();
  updateCanvasDisp(pixels);
  displayPalette(palette, palette_pos, palette_size);
}

void loop() 
{
  updateInputs();

  int old_x = cur_x;
  int old_y = cur_y;
  int old_p = palette_pos;

  switch(currentMo) 
  {
    case DRAW_MODE:
            DMMovementIn();
            DMButtonPresses();
            break;
    case COLORPICK_MODE:
            CPICKMoveIn();
            CPICKButPress(); 
            break;
  }

  if(old_x != cur_x || old_y != cur_y) //if the cursor moves
  {
    flashCursorOff(old_x, old_y, pixels[old_y][old_x]);
    cursorVis = true;
    flashCursorOn(cur_x, cur_y);
  }

  handleCursorFlash();
  if(old_p != palette_pos)
  {
    displayPalette(palette, palette_pos, palette_size);
  }
}

void DMMovementIn() //draw-mode Movement inputs 
{
  if (inputs[F_IN].wasPressed)
    moveCursor('F');
  if (inputs[B_IN].wasPressed)
    moveCursor('B');
  if (inputs[L_IN].wasPressed)
    moveCursor('L');
  if (inputs[R_IN].wasPressed)
    moveCursor('R');
}

void DMButtonPresses()
{
  if(inputs[M_IN].pressed)
  {
    drawPixel(cur_x,cur_y, currentColor);
    paintPixel();
  }
  if(inputs[MENU_IN].wasPressed)
    swapMode();
}


void CPICKMoveIn()
{
  if (inputs[L_IN].wasPressed)
    changePalettePos(true);
  if (inputs[R_IN].wasPressed)
    changePalettePos(false);
}

void CPICKButPress()
{
  if(inputs[MENU_IN].wasPressed)
    swapMode();
}

void handleCursorFlash()
{
  if(millis() - lastFlash >= CURSOR_FLASH_TIME)
  {
    lastFlash = millis();
    cursorVis = !cursorVis;

    if(cursorVis)
      flashCursorOn(cur_x, cur_y);
    else
      flashCursorOff(cur_x, cur_y, pixels[cur_y][cur_x]);
  }
}

void swapMode() //swap from draw to color pick for now, menu comes later
{
  if(currentMo == DRAW_MODE)
    currentMo = COLORPICK_MODE;
  else
    currentMo = DRAW_MODE;
}