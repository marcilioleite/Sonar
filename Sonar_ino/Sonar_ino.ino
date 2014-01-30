#include <NewPing.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>

#define TRIGGER_PIN  22
#define ECHO_PIN     23
#define DISTANCE     200
#define CS 53

NewPing             sonar   ( TRIGGER_PIN, ECHO_PIN, DISTANCE );
LiquidCrystal_I2C   lcd     ( 0x27, 16, 2 );
File                file;

void setup () 
{
    pinMode (CS, OUTPUT);
    Serial.begin (9600);
    lcd.init();
    lcd.backlight();
    
    if ( !SD.begin (CS) ) { return; }
}

void loop () 
{
    file = SD.open("log.txt", FILE_WRITE);
    
    unsigned int medicao = ( (sonar.ping() * 10) / US_ROUNDTRIP_CM );
    
    lcd.clear();
    lcd.setCursor(0, 0);    
    lcd.println(String(medicao));    
    file.println(String(medicao));

    file.flush();
    file.close();
    
    delay(1000);
}
