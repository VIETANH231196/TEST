
#include "thermistor.h"
#include "HardwareSerial.h"
#include "U8glib.h"
U8GLIB_ST7920_128X64_4X u8g(58, 56, 57);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

// Analog pin used to read the NTC
#define NTC_PIN               A1

// Thermistor object
THERMISTOR thermistor(NTC_PIN,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

// Global temperature reading
uint16_t temp;
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0, 20); 
  //u8g.setFont(u8g_font_osb21);
  u8g.print(temp);
}

void setup()
{
    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  temp = thermistor.read();   // Read temperature
  Serial.print("Temp in 1/10 ºC : ");
  Serial.println(temp);
   u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  delay(5000);
}

