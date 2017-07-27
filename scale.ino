#include <ESP8266WiFi.h>
#include <Q2HX711.h>
#include "SSD1306.h"
#include <ESP8266mDNS.h>
#include <WiFiUdp.h> // Required for OTA
#include <ArduinoOTA.h> // OTA updates
#include <ThingSpeak.h>

// Credentials and parameters
#include "credentials.h"
#include "scale_config.h"

#include "font.h"
#include "images.h"

// OTA
#define HOSTNAME "scale"

// Wifi
WiFiClient wifi_client;

// Pin mapping
#define DISPLAY_SDA_PIN D5
#define DISPLAY_SCL_PIN D6
#define HX711_DT_PIN D2
#define HX711_SCL_PIN D1

Q2HX711 hx711(HX711_DT_PIN, HX711_SCL_PIN);
float weight;

long last_sample_time;
#define SAMPLING_PERIOD 100 // [ms]

#define WEIGHT_BUFFER_SIZE 30
float weight_buffer[WEIGHT_BUFFER_SIZE];

#define UPLOAD_MINIMUM_WEIGHT 5 // [kg]
#define UPLOAD_MAXIMUM_WEIGHT_RANGE 0.6 // [kg]

// Display
SSD1306 display(0x3c, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN);
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

// Scale states
boolean wifi_connected = false;
boolean weight_above_threshold = false;
boolean uploading = false;


void setup() {

  // Mandatory initial delay
  delay(10);

  // Serial init
  Serial.begin(115200);
  Serial.println();
  Serial.println(); // Separate serial stream from initial gibberish
  Serial.println(F(__FILE__ " " __DATE__ " " __TIME__));

  display_setup();
  wifi_setup();
  OTA_setup();
  ThingSpeak.begin(wifi_client);

}

void loop() {
  ArduinoOTA.handle();

  

  // Display management
  if(WiFi.status() != WL_CONNECTED){
    // Wifi disconnected

    if(wifi_connected){
      wifi_connected = false;
    }

    display_connecting();

  }
  else {
    // Wifi connected

    if(!wifi_connected){
      wifi_connected = true;
      display_connected();
    }

    // Weight reading loop
    if ( millis() - last_sample_time > SAMPLING_PERIOD) {
      last_sample_time = millis();
      weight = get_weight();
      add_to_buffer(weight);
    

      if (weight > UPLOAD_MINIMUM_WEIGHT) {
        // Wifi connected, weight above threshold
  
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
          //  Wifi connected, weight above threshold and stable
  
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
        // Wifi connected, weight below threshold
  
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
