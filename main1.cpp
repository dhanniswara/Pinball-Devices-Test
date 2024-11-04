#include <Arduino.h>
#include "dynamixel.h"  // Pastikan ini terhubung ke playServo di task.cpp

#define ENABLE_TX_PIN 19
#define IR_SENSOR_PIN_1 33  // Pin untuk sensor

// Fungsi untuk mengaktifkan dan menonaktifkan TX
void enableTX() {
    digitalWrite(ENABLE_TX_PIN, HIGH);
}

void disableTX() {
    digitalWrite(ENABLE_TX_PIN, LOW);
}

// Fungsi untuk mengontrol servo
void controlServo(int servoID, int position, int duration) {
    enableTX(); 
    playServo(servoID, position, duration); 
    disableTX(); 
}

void setup() {
    Serial.begin(115200);
    initDynamixel(); 
    pinMode(IR_SENSOR_PIN_1, INPUT);
    pinMode(ENABLE_TX_PIN, OUTPUT);
    disableTX();
}

void loop() {
    // Kondisi uji sederhana untuk menggerakkan servo jika sensor mendeteksi sesuatu
    if (digitalRead(IR_SENSOR_PIN_1) == HIGH) {
        controlServo(1, 512, 500);  // Misalnya, menggerakkan servo ID 1 ke posisi 512 dengan durasi 500 ms
        delay(1000);                 // Delay untuk mengamati pergerakan servo
    } else {
        controlServo(1, 0, 500);     // Mengembalikan servo ke posisi awal (opsional)
        delay(1000);
    }
}
