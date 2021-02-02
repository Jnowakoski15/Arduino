/*
  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 Library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 Example added 9 Jul 2009
 by Tom Igoe
 Modified 22 Nov 2010
 by Tom Igoe
 Modified 2 Feb 2020
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define LCD_ROW_SIZE 16
static const int DHT_SENSOR_PIN = 13;

DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_ROW_SIZE, 2);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

  float temperature;
  float humidity;
  float dots = 0.0;
  float tmp = 0.0;
  static unsigned long measurement_timestamp = millis();
  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity, &measurement_timestamp ) == true )
 {
  lcd.clear();
  lcd.print(temperature * 1.8 + 32);
  lcd.print("F");
  lcd.print(" H:");
  lcd.print(humidity);
  lcd.print("%");
  dots = 1;
 }

tmp = ((millis() - measurement_timestamp) / 250)+ 1;

if (tmp > dots) {
  lcd.setCursor(0,1);
  lcd.print(".");
  dots = tmp;

 for(int i = 0; i <= dots; i++) {
    lcd.print('.');
  } 
}
 

}

static bool measure_environment( float *temperature, float *humidity, unsigned long *measurement_timestamp )
{
  /* Measure once every four seconds. */
  if( millis( ) - *measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      *measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}
