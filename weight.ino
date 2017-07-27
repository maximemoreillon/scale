float get_weight() {
  // Reads HX711 output and convert to kg

  float hx711_raw = hx711.read();
  float weight_hg = map(hx711_raw, MAPPING_RAW_LOW, MAPPING_RAW_HIGH, MAPPING_HG_LOW, MAPPING_HG_HIGH);
  float weight_kg = weight_hg/10.00;

  Serial.print("HX711 raw output: ");
  Serial.print(hx711_raw);
  Serial.print(" ,mapped output: ");
  Serial.print(weight_hg);
  Serial.print(" ,weight kg: ");
  Serial.println(weight_kg);

  return constrain(weight_kg,0.00,200.00);;
}


void add_to_buffer(float in) {
  // Add weight to the buffer

  // Shifting all buffer elements
  for (int i = 1; i < WEIGHT_BUFFER_SIZE; i++) {
    weight_buffer[i - 1] = weight_buffer[i];
  }

  // Adding new element in the buffer
  weight_buffer[WEIGHT_BUFFER_SIZE - 1] = in;
}


float get_range(){
  // Gets difference between min and max of buffer

  float buffer_min = 200.00;
  float buffer_max = 0.00;

  for (int i = 0; i < WEIGHT_BUFFER_SIZE; i++) {
    if(weight_buffer[i] > buffer_max){
      buffer_max = weight_buffer[i];
    }
    if(weight_buffer[i] < buffer_min){
      buffer_min = weight_buffer[i];
    }
  }

  Serial.print("buffer min:");
  Serial.print(buffer_min);
  Serial.print(", max: ");
  Serial.print(buffer_max);
  Serial.print(", range:");
  Serial.println(buffer_max-buffer_min);

  return  buffer_max-buffer_min;
}


String get_weight_string(int weight_int){
  // Convert weight to a String

  int weightWhole = int(weight);
  int weightDecimal = int((weight-weightWhole)*10.00);
  String weight_string = String(weightWhole) + "." + String(weightDecimal);

  return weight_string;
}
