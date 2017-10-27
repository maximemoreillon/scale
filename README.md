# scale
Wifi enabled scale that uploads the user's weight to Thingspeak.

**Note to people intending to make their own:** Choose the pins for the display carefully. Some libraries require specific pins to be used.

## Video:
[![Alt text](https://img.youtube.com/vi/msVoXorvrb0/0.jpg)](https://www.youtube.com/watch?v=msVoXorvrb0)


## Parts list
* Wemos D1 Mini
* HX711 load cell amplifier
* SSD1306 OLED display


## Schematic
![alt text](https://moreillon.duckdns.org/projects/iot/images/scale_schematic.png)

## Requirements
* Arduino IDE with [support for ESP8266](https://github.com/esp8266/Arduino)
* [Q2-HX711-Arduino-Library](https://github.com/queuetue/Q2-HX711-Arduino-Library)
* [esp8266-oled-ssd1306](https://github.com/squix78/esp8266-oled-ssd1306)
