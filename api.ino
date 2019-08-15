boolean upload_weight_home(){
  // Create a JSON payload
  StaticJsonDocument<200> outbound_JSON_message;

  outbound_JSON_message["weight"] = (String) weight;

  char JSONmessageBuffer[200];
  serializeJson(outbound_JSON_message, JSONmessageBuffer, sizeof(JSONmessageBuffer));
  
  Serial.print(F("[HTTP] Outbound payload: "));
  serializeJson(outbound_JSON_message, Serial);

  // Sending the payload using HTTP POST request
  HTTPClient http;
  http.begin(API_URL);
  //http.setTimeout(3000); // Probably ms
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(JSONmessageBuffer);
  http.end();

  
  Serial.print(F("[HTTP] Response code:"));
  Serial.println(httpCode);
  
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.print(F("[HTTP] Inbound payload: "));
    Serial.println(payload);
    
    // Parsing payload
    StaticJsonDocument<200> inbound_JSON_message;
    deserializeJson(inbound_JSON_message, payload);
    
    if(httpCode == 200){
      // Success
      return true;
    }
    else {
      // Response code was error
      return false;
    }
  }
  else {
    // response code was negative (unable to connect)
    return false;
  }

  
}
