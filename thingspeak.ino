boolean upload_weight() {
  Serial.println("Uploading to thingspeak...");
  return (ThingSpeak.writeField(THINGSPEAK_CHANNEL_ID, THINGSPEAK_FIELD, weight, THINGSPEAK_API_KEY) == 200);
}


