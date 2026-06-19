#include "canvas.h"
#include "displayManager.h"
#include "inputRegistry.h"
#include "startMenu.h"

bool cursorVis = false;
unsigned long lastFlash = 0;
const unsigned long CURSOR_FLASH_TIME = 500;

enum Mode
{
  DRAW_MODE,
  COLORPICK_MODE,
  TOOL_MODE,
  START_MENU

};
Mode currentMo = START_MENU;

void setup() 
{
  tftDisplay.begin();
  initCanvas();
  setupInputs();
  openStartMenu();  

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
    case START_MENU:
            SMButPress();
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
    displayPalette(palette, palette_pos, palette_size);
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
  if (inputs[F_IN].isHeld)
    jumpCursor('F');
  if (inputs[B_IN].isHeld)
    jumpCursor('B');
  if (inputs[L_IN].isHeld)
    jumpCursor('L');
  if (inputs[R_IN].isHeld)
    jumpCursor('R');
}

void DMButtonPresses()
{
  if(inputs[M_IN].pressed)
  {
    drawPixel(cur_x,cur_y, currentColor);
    paintPixel();
  }
  if(inputs[MENU_IN].wasPressed)
    DrawToColorMode();

  if(inputs[DEL_IN].wasPressed)
    deleteColor();
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
    DrawToColorMode();
}

void handleCursorFlash()
{
  switch(currentMo)
  {
    case DRAW_MODE:
            if(millis() - lastFlash >= CURSOR_FLASH_TIME)
            {
              lastFlash = millis();
              cursorVis = !cursorVis;

              if(cursorVis)
                flashCursorOn(cur_x, cur_y);
              else
                flashCursorOff(cur_x, cur_y, pixels[cur_y][cur_x]);
            }
            break;
  }
}

void DrawToColorMode() //swap from draw to color pick for now, menu comes later
{
  currentMo = (currentMo == DRAW_MODE) ? COLORPICK_MODE : DRAW_MODE;
}

void startMenutoDraw()
{
  currentMo = (currentMo == START_MENU) ? DRAW_MODE : START_MENU;
}

void SMButPress()
{
  if(inputs[M_IN].wasPressed)
  {
    startMenutoDraw();
    updateCanvasDisp(pixels);
    displayPalette(palette, palette_pos, palette_size);
  }
}
