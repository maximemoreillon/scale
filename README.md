# scale
Wifi enabled scale that uploads the user's weight to the cloud.

**Note to people intending to make their own:** Choose the pins for the display carefully. Some libraries require specific pins to be used.

## Video:
[![Alt text](https://img.youtube.com/vi/msVoXorvrb0/0.jpg)](https://www.youtube.com/watch?v=msVoXorvrb0)

## Requirements
* Arduino IDE with [support for ESP8266](https://github.com/esp8266/Arduino)
* [Q2-HX711-Arduino-Library](https://github.com/queuetue/Q2-HX711-Arduino-Library)
* [esp8266-oled-ssd1306](https://github.com/squix78/esp8266-oled-ssd1306)

## Calibration
Calibration is done using the MAPPING_RAW_LOW, MAPPING_RAW_HIGH, MAPPING_HG_LOW and MAPPING_HG_HIGH defines in scale_config.h such that:
* MAPPING_RAW_LOW is the raw reading of the HX711 when MAPPING_HG_LOW hectograms are on the scale.
* MAPPING_RAW_HIGH is the raw reading of the HX711 when MAPPING_HG_HIGH hectograms are on the scale.

## Hardware

### Parts list
* Wemos D1 Mini
* HX711 load cell amplifier
* SSD1306 OLED display

### Schematic
![alt text](http://maximemoreillon.com/images/projects/iot/scale/scale_schematic.png)


