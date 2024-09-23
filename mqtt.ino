boolean publish_weight(){
    // Create a JSON payload
  StaticJsonDocument<200> outbound_JSON_message;

  outbound_JSON_message["weight"] = weight;

  char JSONmessageBuffer[200];
  serializeJson(outbound_JSON_message, JSONmessageBuffer, sizeof(JSONmessageBuffer));
  
  Serial.print(F("[MQTT] Outbound payload: "));
  serializeJson(outbound_JSON_message, Serial);

  String topic = iot_kernel.mqtt_base_topic + "/measurement";
  return iot_kernel.mqtt.publish(topic.c_str(), JSONmessageBuffer, false);


}
