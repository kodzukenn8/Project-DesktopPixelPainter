void openStartMenu()
{ 
  tftDisplay.fillScreen(0xFFBD);
  tftDisplay.drawRect(65,35,115,16,0xa691);
  tftDisplay.setCursor(70,40);
  tftDisplay.setTextSize(1);
  tftDisplay.setTextColor(0xa691);
  tftDisplay.print("Select Canvas Size");

  tftDisplay.fillRect(29,99,61,61,0xa691);
  tftDisplay.fillRect(149,99,61,61,0xa691);

  tftDisplay.setCursor(30,122);
  tftDisplay.setTextSize(2);
  tftDisplay.setTextColor(GC9A01A_WHITE);
  tftDisplay.print("16x16");
  tftDisplay.setCursor(150,122);
  tftDisplay.print("32x32");

  tftDisplay.drawLine(32,140,86,140, GC9A01A_WHITE);
}
