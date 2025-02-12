void drawMenu(int highlightedRow, const char* labels[], const uint8_t* icons[], int totalItems)
{
  display.clearDisplay();
  
  // calculate starting and ending rows for the current view
  int startrow = menuoffset;
  int endrow = min(startrow + visiblerows, totalItems);
  // if startrow + visiblerows more than 7, endrow will become totalItems since it is 7 which is smaller than anything above 7

  for (int i = startrow; i < endrow && i < totalItems; i++)
  {
    int displayrow = i - startrow; // Row position on the display

    if (i == highlightedRow)
    {
      display.fillRect(0, displayrow * 21, SCREEN_WIDTH, 18, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else
    {
      display.setTextColor(SSD1306_WHITE);
    }

    display.drawBitmap(2, displayrow * 21 + 1, icons[i], 16, 16, i == highlightedRow ? SSD1306_BLACK : SSD1306_WHITE);
    display.setCursor(20, displayrow * 21 + 2);
    display.println(labels[i]);
  }

  display.display();
}

void menudisplay()
{
  if (menu != lastmenu || gamedata.goback == true)
  {
    lastmenu = menu;
    gamedata.goback = false; // reset to 
    drawMenu(menu, menuLabels, menuIcons, NUM_MODES);
    gamedata.modenum = menu;
    sendall();
    // team boards should blink white to show that they recieved the update mode number
  }
}




// can probably combine drawMenu and drawMenu2 into one
void drawMenu2(int highlightedRow, const char* labels[], const uint8_t* icons[], int totalItems2)
{
  display.clearDisplay();
  
  // need to create a seperate variable if not it will use and continue from the variables in drawMenu


  // Calculate starting and ending rows for the current view
  int startrow2 = menuoffset2;
  int endrow2 = min(startrow2 + visiblerows2, totalItems2);
  // if startrow + visiblerows more than 7, endrow will become totalItems since it is 7 which is smaller than anything above 7

  for (int i = startrow2; i < endrow2 && i < totalItems2; i++)
  {
    int displayrow = i - startrow2; // Row position on the display

    if (i == highlightedRow)
    {
      display.fillRect(0, displayrow * 21, SCREEN_WIDTH, 18, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }
    else
    {
      display.setTextColor(SSD1306_WHITE);
    }

    display.drawBitmap(2, displayrow * 21 + 1, icons[i], 16, 16, i == highlightedRow ? SSD1306_BLACK : SSD1306_WHITE);
    display.setCursor(20, displayrow * 21 + 2);
    display.println(labels[i]);
  }

  display.display();
}