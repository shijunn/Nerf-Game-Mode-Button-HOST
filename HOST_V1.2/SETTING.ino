void setting()
{
  gamedata.middlelongpressed = false;
  gamedata.togglescreen = 0; //set default screen in settings to game time
  bool savesettings = false;
  int prevtogglescreen = 0;
  
  while (!gamedata.middlelongpressed && !gamedata.goback) // goes out of while loop and back to main menu
  {
    reading = 0;
    avgReading = 0;
    for (int n = 0; n < 10; n++)
    {
      reading = reading + analogRead(joystick);
    }
    avgReading = reading / 10;
    if (avgReading >= UP_JOYSTICK_THRESHOLD_MIN && avgReading <= UP_JOYSTICK_THRESHOLD_MAX)
    {
      if (gamedata.togglescreen == 0)
      {
        gamedata.togglescreen = 1;
      }
      else if (gamedata.togglescreen == 1)
      {
        gamedata.togglescreen = 0;
      }
    }
    else if (avgReading >= DOWN_JOYSTICK_THRESHOLD_MIN && avgReading <= DOWN_JOYSTICK_THRESHOLD_MAX)
    {
      if (gamedata.togglescreen == 0)
      {
        gamedata.togglescreen = 1;
      }
      else if (gamedata.togglescreen == 1)
      {
        gamedata.togglescreen = 0;
      }
    }
    else if (avgReading >= LEFT_JOYSTICK_THRESHOLD_MIN && avgReading <= LEFT_JOYSTICK_THRESHOLD_MAX)
    {
      gamedata.goback = true;
    }
    else if (avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && laststate == HIGH)
    {
      pressedTime = millis();
      laststate = LOW;
    }
    else if(avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && laststate == LOW)
    {
      longpress = millis() - pressedTime;
      if (longpress > 2000)
      {
        gamedata.middlelongpressed = true;
        laststate = HIGH;
      }
    }
    else
    {
      laststate = HIGH; // when middle isnt pressed, time will restart to prevent accidental press
    }
      drawMenu2(gamedata.togglescreen, menuLabels2, menuIcons2, 2);
      if (gamedata.togglescreen != prevtogglescreen)
      {
        prevtogglescreen = gamedata.togglescreen;
        sendall();
      }
    delay(200);
  }

  while (!savesettings && !gamedata.goback)
  {
    if (gamedata.togglescreen == 0)
    {
      reading = 0;
      avgReading = 0;
      for (int n = 0; n < 10; n++)
      {
        reading = reading + analogRead(joystick);
      }
      avgReading = reading / 10;
      if (avgReading >= UP_JOYSTICK_THRESHOLD_MIN && avgReading <= UP_JOYSTICK_THRESHOLD_MAX) //&& timesetting > 0) // more than 0 to prevent negative number, not needed though since timesetting is unsigned
      {
        timesetting--;
        gamedata.gamemodetime = timesetting * 60000; // convert to milliseconds
        sendall();
      }
      else if (avgReading >= DOWN_JOYSTICK_THRESHOLD_MIN && avgReading <= DOWN_JOYSTICK_THRESHOLD_MAX)
      {
        timesetting++;
        gamedata.gamemodetime = timesetting * 60000; // convert to milliseconds
        sendall();
      }
      else if (avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && laststate == HIGH)
      {
        pressedTime = millis();
        laststate = LOW;
      }
      else if(avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && laststate == LOW)
      {
        longpress = millis() - pressedTime;
        if (longpress > 2000)
        {
          
          laststate = HIGH;
          gamedata.gamemodetime = timesetting * 60000; // convert to milliseconds
          preferences.putULong("game_duration", gamedata.gamemodetime);
          #ifdef devdebug
            Serial.println("game duration preferences saved");
            Serial.println(String("Game time set to: ") + timesetting + String(" mins"));
            Serial.println(gamedata.gamemodetime + String("ms"));
          #endif
          sendall();
          savesettings = true; // savesettings and exit
        }
      }
      else
      {
        laststate = HIGH; // when middle isnt pressed, time will restart to prevent accidental press
      }
      oledDisplayStrInt(gamedata.gamemodetime/60000, " mins"); // live display update
      delay(100);
      
    }
    else
    {
      //readstickinsettings(gamedata.countdowntime, countdownsetting, 1000);
      reading = 0;
      avgReading = 0;
      for (int n = 0; n < 10; n++)
      {
        reading = reading + analogRead(joystick);
      }
      avgReading = reading / 10;
      if (avgReading >= UP_JOYSTICK_THRESHOLD_MIN && avgReading <= UP_JOYSTICK_THRESHOLD_MAX) //&& timesetting > 0) // more than 0 to prevent negative number, not needed though since timesetting is unsigned
      {
        countdownsetting--;
        gamedata.countdowntime = countdownsetting * 1000; // convert to seconds
        sendall();
      }
      else if (avgReading >= DOWN_JOYSTICK_THRESHOLD_MIN && avgReading <= DOWN_JOYSTICK_THRESHOLD_MAX)
      {
        countdownsetting++;
        gamedata.countdowntime = countdownsetting * 1000; // convert to seconds
        sendall();
      }
      else if (avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && laststate == HIGH)
      {
        pressedTime = millis();
        laststate = LOW;
      }
      else if(avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && laststate == LOW)
      {
        longpress = millis() - pressedTime;
        if (longpress > 2000)
        {
          savesettings = true; // savesettings and exit
          laststate = HIGH;
          gamedata.countdowntime = countdownsetting * 1000; // convert to milliseconds
          preferences.putULong("game_countdown", gamedata.countdowntime);
          #ifdef devdebug
            Serial.println("countdown preferences saved");
            Serial.println(String("Countdown time set to: ") + countdownsetting + String(" seconds"));
            Serial.println(gamedata.countdowntime + String("ms"));
          #endif
          sendall();
        }
      }
      else
      {
        laststate = HIGH; // when middle isnt pressed, time will restart to prevent accidental press
      }
      oledDisplayStrInt(gamedata.countdowntime/1000, " sec"); // live display update
      delay(100);
    }
  }
}


