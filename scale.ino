/*
 * WIFI SCALE
 * Maxime MOREILLON
 * 
 * Board type: Wemos D1 mini
 */

#include "IotKernel.h"

#include <Q2HX711.h>
#include "SSD1306.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>

// Credentials and parameters
#include "credentials.h"
#include "scale_config.h"

#include "font.h"
#include "images.h"


// Pin mapping
#define DISPLAY_SDA_PIN D5
#define DISPLAY_SCL_PIN D6
#define HX711_DT_PIN D2
#define HX711_SCL_PIN D1

// Weight
#define SAMPLING_PERIOD 100 // [ms]
#define WEIGHT_BUFFER_SIZE 30
#define UPLOAD_MINIMUM_WEIGHT 5 // [kg]
#define UPLOAD_MAXIMUM_WEIGHT_RANGE 0.6 // [kg]

// Display
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

IotKernel iot_kernel("scale","0.0.3"); 

Q2HX711 hx711(HX711_DT_PIN, HX711_SCL_PIN);

float weight; // [kg]

long last_sample_time;

float weight_buffer[WEIGHT_BUFFER_SIZE];



// Display
SSD1306 display(0x3c, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);


// States
boolean wifi_connected = false;
boolean weight_above_threshold = false;
boolean uploading = false;


void setup() {

  iot_kernel.init();

  display_setup();
  delay(10);
  display_nothing();
}

void loop() {

   iot_kernel.loop();

  if(WiFi.status() != WL_CONNECTED){
    // Wifi disconnected: display connecting

    if(wifi_connected){
      Serial.println("[Wifi] Disconnected");
      wifi_connected = false;
    }

    display_connecting();

  }
  else {
    // Wifi connected

    if(!wifi_connected){
      wifi_connected = true;
      Serial.println("[Wifi] Connected");
      display_connected();
    }

    // Weight reading loop
    if ( millis() - last_sample_time > SAMPLING_PERIOD) {
      last_sample_time = millis();
      weight = get_weight();
      add_to_buffer(weight);
    

      if (weight > UPLOAD_MINIMUM_WEIGHT) {
        // Wifi connected, weight above threshold: display weight
  
        if(!weight_above_threshold){
          weight_above_threshold = true;
        }
  
        if( get_range() > UPLOAD_MAXIMUM_WEIGHT_RANGE) {
          //  Wifi connected, weight above threshold and unstable
  
          if(!uploading){
            display_weight();
          }
        }
        else {
          //  Wifi connected, weight above threshold and stable: upload to thingspeak
  
          if(!uploading){
            uploading = true;
            display_uploading();
            
            if(upload_weight()){
              display_upload_success();
            }
            else{
              display_upload_fail();
            }
          }
        }
      }
      else {
        // Wifi connected, weight below threshold: display nothing to prevent display burn in
  
        if(weight_above_threshold){
          weight_above_threshold = false;
          display_nothing();
        }
  
        if(uploading){
          uploading = false;
        }
      }
    }
  }
}
