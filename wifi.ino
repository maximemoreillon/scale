void wifi_setup()
{
  Serial.print("Wifi connecting to: ");
  Serial.print(WIFI_SSID);
  WiFi.hostname(HOSTNAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}
