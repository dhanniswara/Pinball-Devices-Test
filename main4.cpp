#include <Arduino.h>
#include "dynamixel.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_SCL_PIN 22
#define LCD_SDA_PIN 21
#define IR_SENSOR_PIN_1 33
#define IR_SENSOR_PIN_2 18
#define PIEZO_SENSOR_PIN_1 15
#define PIEZO_SENSOR_PIN_2 13
#define ENABLE_TX_PIN 19

void enableTX() {
    digitalWrite(ENABLE_TX_PIN, HIGH); 
}

void disableTX() {
    digitalWrite(ENABLE_TX_PIN, LOW); 
}

void controlServo(int servoID, int position, int duration) {
    enableTX(); 
    playServo(servoID, position, duration); 
    disableTX(); 
}

LiquidCrystal_I2C lcd(0x27, 16, 2);
int ballCount = 3;
int score = 0;

void setup(){
    Serial.begin(115200);
    Wire.begin(LCD_SDA_PIN, LCD_SCL_PIN);  
    lcd.begin(16, 2);
    lcd.print("Aloha");             
    initDynamixel(); 

    pinMode(IR_SENSOR_PIN_1, INPUT);
    pinMode(IR_SENSOR_PIN_2, INPUT);
    pinMode(PIEZO_SENSOR_PIN_1, INPUT);
    // pinMode(PIEZO_SENSOR_PIN_2, INPUT);
    pinMode(ENABLE_TX_PIN, OUTPUT);

    disableTX(); 

    lcd.begin(16, 2);
    lcd.print("Ready to Play!");
    delay(2000);
    lcd.clear();
}

void loop(){
    if (digitalRead(IR_SENSOR_PIN_1) == HIGH) {
        Serial.println("Test1234");
        controlServo(1, 512, 500);  
        delay(1000);                
        controlServo(1, 0, 500);    
        score += 10;
    } else {
        Serial.println("Halo1234");
    }
    
    if (digitalRead(IR_SENSOR_PIN_2) == HIGH) {
        Serial.println("Test4321");
        controlServo(2, 512, 500);  
        delay(1000);                
        controlServo(2, 0, 500);    
        score += 10;
    } else {
        Serial.println("Halo4321");
    }

    if (analogRead(PIEZO_SENSOR_PIN_1) > 50) {
        ballCount -= 1;
        if (ballCount <= 0) {
            lcd.clear();
            lcd.print("Game Over!");
            lcd.setCursor(0, 1);
            lcd.print("Score: ");
            lcd.print(score);
            while (true);  
        }
    }

    lcd.setCursor(0, 0);
    lcd.print("Balls: ");
    lcd.print("   ");  
    lcd.setCursor(7, 0);
    lcd.print(ballCount);

    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print("   ");  
    lcd.setCursor(7, 1);
    lcd.print(score);

    delay(1000);
}
