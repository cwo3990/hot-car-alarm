/*
 * -------------------
 *  Hot Car Alarm
 * by Connor O'Neill
 * -------------------
 */
#include <LiquidCrystal.h>
#define TEMPERATURE_PIN 0 // ANALOG 0 PIN
#define BUZZER_PIN 6  // DIGITAL 6
#define LED_PIN 4         // DIGITAL 4

int unsafeTemp = 29; // Temperature in Celsius

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  //LCD display

void setup() {
  lcd.begin(16, 2);    // 16 columns and 2 rows
  Serial.begin(9600);  // send temperature to computer
  // setup pins for each component
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int tempReading = analogRead(TEMPERATURE_PIN);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK);  //  Temp Kelvin
  float tempC = tempK - 273.15;                                                 //  Convert Kelvin to Celsius

  // Display Temerature in C
  // lcd.setCursor(0, 0);  // lcd.setCursor(column,row)
  // lcd.print("Temp         C  ");
  
  float tempF = (tempC * 9.0) / 5.0 + 32.0;  // Convert Celcius to Fahrenheit
  lcd.setCursor(0, 0);               // lcd.setCursor(column,row)
  // Display Temperature in F
  lcd.print("Temp         F  ");

  // Display temperature
  lcd.setCursor(6, 0);
  lcd.print(tempF);

  delay(500);

  // beeps and flashes light when temp gets unsafe
  if (tempF >= unsafeTemp) {
    // flash LEDs
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_PIN, HIGH);   // turn one red LED on
    // digitalWrite(ledPin2, HIGH);   // turn the other red LED on
    delay(200);                       // wait
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(LED_PIN, LOW);    // turn one red LED off by making the voltage LOW
    // digitalWrite(ledPin2, LOW);    // turn the other red LED off by making the voltage LOW
    
    unsigned int i;
    
    // Activate buzzer
    // output a frequency
    for (i = 0; i < 80; i++) {
      digitalWrite(BUZZER_PIN, HIGH);  //buzzer on
      delay(1);                    // wait for 1ms
      digitalWrite(BUZZER_PIN, LOW);   //buzzer off
      delay(1);                    // wait for 1ms
    }
    // output another frequency
    for (i = 0; i < 100; i++) {
      digitalWrite(BUZZER_PIN, HIGH);  // buzzer on
      delay(2);                    // wait for 2ms
      digitalWrite(BUZZER_PIN, LOW);   // buzzer off
      delay(2);                    // wait for 2ms
    }
  }
}