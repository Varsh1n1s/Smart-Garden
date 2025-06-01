//libraries used for the sensors
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#include<DHT.h>
#include<Arduino.h>

#define DHTTYPE DHT11

//Defining the OLED screen size
#define screen_width 128
#define screen_height 64

//Declare the SSD1306 display object to I2C
Adafruit_SSD1306 oled(screen_width, screen_height, &Wire, -1);

//Initializing the pins
#define moistureSensor A0
#define rainSensor 5
#define touchSensor 2
#define htSensor 3

DHT dht(htSensor, DHTTYPE);


void setup(){
  pinMode(touchSensor,INPUT);
  pinMode(htSensor,INPUT);
  pinMode(moistureSensor,INPUT);
  pinMode(rainSensor,INPUT);
  Serial.begin(9600);
  

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  oled.clearDisplay(); // clear display
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Device is ON"); // text to display
  delay(1000);
  oled.display();
}

void loop(){
  float humi  = dht.readHumidity();    // read humidity
  humi = humi/2;
  float tempC = dht.readTemperature(); // read temperature
  float temp = tempC + 12.0000;
  int moistureValue = readSensorMoisture();
  bool rain = digitalRead(rainSensor);
  delay(500);
  
  oled_display(moistureValue,humi,temp,rain);
}

void oled_display(int moistureValue, float humi,float temp, bool rain){
  oled.clearDisplay(); // clear display
  delay(500);
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.print("Moisture: ");
  oled.println(moistureValue); // Display moisture
  oled.print("Humidity: ");
  oled.println(humi); // Display humidity
  oled.print("Temperature: ");
  oled.println(temp); // Display temperature
  oled.print("Rain(1 - No rain, 0 - Raining): ");
  oled.println(rain); // Display Rain - YES/NO
  oled.display();
}

int readSensorMoisture() {
  int sensorValue = analogRead(moistureSensor);  // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog rain value
}