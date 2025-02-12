void sendall()
{
  esp_err_t result = esp_now_send(0, (uint8_t *) &gamedata, sizeof(game_struct));
        
  if (result == ESP_OK)
  {
    Serial.println("Sent game mode successfully");
  }
  else
  {
  Serial.println("Error sending game mode");
  }
}

void sendtoboard1()
{
  esp_err_t result = esp_now_send(broadcastAddressBlue, (uint8_t *) &gamedata, sizeof(game_struct));
        
  if (result == ESP_OK)
  {
    Serial.println("Sent data to board 1");
  }
  else
  {
  Serial.println("Error sending data to board 1");
  }
}

void sendtoboard2()
{
  esp_err_t result = esp_now_send(broadcastAddressRed, (uint8_t *) &gamedata, sizeof(game_struct));
        
  if (result == ESP_OK)
  {
    Serial.println("Sent data to board 2");
  }
  else
  {
  Serial.println("Error sending data to board 2");
  }
}