void resetvariables()
{
  lastmenu = -1; // was previously 0
  gamedata.middlelongpressed = false;
  longpressduration = 0;
  pixels.clear();
  pixels.show();
  display.setTextSize(2);
  gamedata.confirm = false;
  gamedata.togglescreen = 0;
  sendall(); // reset variables on team board
}