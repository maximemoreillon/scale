boolean upload_weight() {
  // Upload to ThingSpeak
  
  return (ThingSpeak.writeField(THINGSPEAK_CHANNEL_ID, THINGSPEAK_FIELD, weight, THINGSPEAK_API_KEY) == 200);
}


