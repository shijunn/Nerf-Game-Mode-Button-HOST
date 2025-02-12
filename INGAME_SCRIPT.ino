void checkendgame()
{
  bool over = false;
  while (!over) //&& second team's incomingendgame)
  {
    if (board1_endgame && !board2_endgame && gamedata.modenum == 0)
    {
      mp3.playTrack(3);
      #ifdef devdebug
        Serial.println("board1 won");
      #endif
      oledDisplayCenter("Blue wins!");
      colorWipe(pixels.Color(0,0,255), 5); // sets neopixels on host to blue
      delay(3000);
      over = true;
    }
    else if (!board1_endgame && board2_endgame && gamedata.modenum == 0)
    {
      mp3.playTrack(4);
      #ifdef devdebug
        Serial.println("board2 won");
      #endif
      oledDisplayCenter("Red wins");
      colorWipe(pixels.Color(255,0,0), 5); // sets neopixels on host to red
      delay(3000);
      over = true;
    }
    if (board1_endgame && gamedata.modenum == 2 || board2_endgame && gamedata.modenum == 2)
    {
      if (board1_testtime > board2_testtime)
      {
        mp3.playTrack(3);
        #ifdef devdebug
          Serial.println("board1 won");
        #endif
        oledDisplayCenter("Blue wins!");
        colorWipe(pixels.Color(0,0,255), 5); // sets neopixels on host to blue
        delay(3000);
        over = true;
      }
      else if (board1_testtime < board2_testtime)
      {
        mp3.playTrack(4);
        #ifdef devdebug
          Serial.println("board2 won");
        #endif
        oledDisplayCenter("Red wins");
        colorWipe(pixels.Color(255,0,0), 5); // sets neopixels on host to red
        delay(3000);
        over = true;
      }
    }
  }
  
}

void checkscore() // doesnt reset variables on team boards
{
  bool over = false;
  int previncomingscore = 0;
  while (true)
  {
    oledDisplayScore("B score ", board1_score, "R score ", board2_score);
    if (board1_endgame || board2_endgame)
    {
      #ifdef devdebug
        Serial.println("time ended");
      #endif
      over = true;
    }
    if (board1_endgame && !board2_endgame && over || !board1_endgame && board2_endgame && over)
    { // check who won
      if (gamedata.modenum == 1) // least clicks wins
      {
        if (board1_score < board2_score)
        {
          mp3.playTrack(3);
          #ifdef devdebug
            Serial.println("board1 won");
          #endif
          oledDisplayCenter("Blue wins!");
          colorWipe(pixels.Color(0,0,255), 5); // sets neopixels on host to blue
          gamedata.confirm = false;
          sendall();
          delay(3000);
          break;
        }
        else if (board2_score < board1_score)
        {
          mp3.playTrack(4);
          #ifdef devdebug
            Serial.println("board2 won");
          #endif
          oledDisplayCenter("Red wins");
          colorWipe(pixels.Color(255,0,0), 5); // sets neopixels on host to red
          gamedata.confirm = false;
          sendall();
          delay(3000);
          break;
        }
        else
        {
          #ifdef devdebug
            Serial.println("DRAW");
          #endif
          oledDisplayCenter("Draw");
          colorWipe(pixels.Color(200,200,200), 5); // sets neopixels on host to white
          delay(3000);
          break;
        }
      }
      else if (gamedata.modenum == 3) // most clicks wins
      {
        if (board1_score > board2_score)
        {
          mp3.playTrack(3);
          #ifdef devdebug
            Serial.println("board1 won");
          #endif
          oledDisplayCenter("Blue wins!");
          colorWipe(pixels.Color(0,0,255), 5); // sets neopixels on host to blue
          delay(3000);
          break;
        }
        else if (board2_score > board1_score)
        {
          mp3.playTrack(4);
          #ifdef devdebug
            Serial.println("board2 won");
          #endif
          oledDisplayCenter("Red wins");
          colorWipe(pixels.Color(255,0,0), 5); // sets neopixels on host to red
          delay(3000);
          break;
        }
        else
        {
          #ifdef devdebug
            Serial.println("DRAW");
          #endif
          oledDisplayCenter("Draw");
          colorWipe(pixels.Color(200,200,200), 5); // sets neopixels on host to white
          delay(3000);
          break;
        }
      }
    }
  }
  Serial.println("reached the end, breaking out");
}

void checkprogress()
{
// check endgame and check time
// team board sends live time recorded
// host display updates with new time
bool first = true;
  while (!board1_endgame && !board2_endgame)
  {
    // incomingtesttime stores current recordedtime + prevtime and check if it meets the threshold
    // incomingrecordedtime stores only the current time being recorded
    togglescreenfunction();
    if (gamedata.togglescreen == 0) // toggle screen to switch teams
    {
      if (gamedata.modenum == 2) // king of the hill
      {
        oledDisplayTime(board1_testtime, "B test ", board1_recordedTime, "B rec");
      }
      else if (gamedata.modenum == 4) // chess clock
      {
        oledDisplayTime(board1_checktime, "B checkti ", board1_newTime, "B newTime");
      }
    }

    else if (gamedata.togglescreen == 1)
    {
      if (gamedata.modenum == 2) // king of the hill
      {
        oledDisplayTime(board2_testtime, "R test ", board2_recordedTime, "R rec");
      }
      else if (gamedata.modenum == 4) // chess clock
      {
        oledDisplayTime(board2_checktime, "R checkti ", board2_newTime, "R newTime");
      }
    }

    if (board1_button)
    {
      gamedata.button = true;  // Signal that board1 is active
      sendtoboard2();
    }
    else if (board2_button)
    {
      gamedata.button = true;  // Signal that board2 is active
      sendtoboard1();
    }

    // Stop time deduction when both buttons are released
    if (!board1_button && !board2_button && first)
    {
      gamedata.button = false;
      sendall();
      first = false;
    }
  }
  if (board1_endgame)
  {
    #ifdef devdebug
      Serial.println("board1 won");
    #endif
    oledDisplayCenter("Blue wins!");
    colorWipe(pixels.Color(0,0,255), 5); // sets neopixels on host to blue
    delay(3000);
  }
  else if (board2_endgame)
  {
    #ifdef devdebug
      Serial.println("board2 won");
    #endif
    oledDisplayCenter("Red wins!");
    colorWipe(pixels.Color(255,0,0), 5); // sets neopixels on host to blue
    delay(3000);
  }
}
