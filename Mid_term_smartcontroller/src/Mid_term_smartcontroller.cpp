/* 
 * Project Mid_Term_smartcontroller
 * Author: Andres Sebastian Cordova
 * Date: 4-MARCH-2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTClassroom_CNM.h"
#include "Colors.h"
#include "button.h"
#include "neopixel.h"
#include "encoder.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_BME280.h"


const int MYWEMO=0;                     //Wemo and Button
const int BUTTONPIN = D14; 


bool buttonState;
bool buttonOnOff;

int position;                           
int lastPosition;
int newPosition;


bool status;                            //for OLED & BME 
const int OLED_RESET = -1;
float tempF;
float tempC;

const int PIXELCOUNT = 12;              //for LED Pixels
int neopixel_1;
const int DELAYLIGHT = 500;



// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

Button button(BUTTONPIN);
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_BME280 bme;
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1, WS2812B);

void pixelFill (int start, int end, int hexcolor, int pixelBrightness);
int segment;

// setup() runs once, when the device is first turned on
void setup() {
 Serial.begin(9600);
  waitFor(Serial.isConnected,10000);

  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.display();

  status = bme.begin(0x76);
  if (status == false){
  Serial.printf ("BME280 at address 0x%02xfailed to start", 0x76);
  display.printf ("BME280 at address 0x%02xfailed to start", 0x76);
  display.display();
  }
  

  pixel.begin();
  pixel.setBrightness(255);
  pixel.show(); 





}

// loop() runs over and over again, as quickly as it can execute.
void loop() {


   if (button.isClicked()){
      buttonOnOff =! buttonOnOff;
      Serial.printf("Click\n");
    }

    if (buttonOnOff){
      wemoWrite(0,HIGH);

    }

    else {
      wemoWrite(0,LOW);

    }

    display.setCursor(0,0);
  tempF = (bme.readTemperature()*(9.0/5.0)+32);   //deg C 


  display.printf("%0.1f\n",tempF);
  display.display();
  display.clearDisplay();
  

    pixel.show();
    pixel.clear();
    


  

for (neopixel_1=0; neopixel_1<=12; neopixel_1++){
  
  pixel.setPixelColor(neopixel_1,144,66,0);
  pixel.show ();
  delay (DELAYLIGHT);
  pixel.clear();
  pixel.show();

}


}







 

 
