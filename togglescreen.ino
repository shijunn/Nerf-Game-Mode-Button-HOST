void togglescreenfunction()
{
  // for testing without esp now
  reading = 0;
  avgReading = 0;
  for (int n = 0; n < 10; n++)
  {
    reading = reading + analogRead(joystick);
  }
  avgReading = reading / 10;
  // Serial.println(String("average reading:") + avgReading);
  if (avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && gamedata.togglescreen == 0)
  {
    gamedata.togglescreen = 1;
  }
  else if (avgReading >= MIDDLE_JOYSTICK_THRESHOLD_MIN && avgReading <= MIDDLE_JOYSTICK_THRESHOLD_MAX && gamedata.togglescreen == 1)
  {
    gamedata.togglescreen = 0;
  }
  delay(200);
}