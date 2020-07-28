#include <Arduino.h>
#include "analogComp.h"


// Just for debugging
#define WATER_METER_ANALOG  A0
#define WATER_METER_REF     A1

#define ANALOG_CMP_A        AIN0    // D6
#define ANALOG_CMP_B        AIN1    // D7

#define LED             5

#define WATER_DEBOUNCE          75      // milliseconds
unsigned long WATER_DEBOUNCE_TIMER = 0;
volatile uint32_t WATER_COUNTER = 0;


void waterInterrupt(){
    unsigned long now = millis();
    if (now - WATER_DEBOUNCE_TIMER >= WATER_DEBOUNCE) {
        WATER_DEBOUNCE_TIMER = now;
        WATER_COUNTER++;
        digitalWrite(LED, !digitalRead(LED));
    }
}

void setup() {
    Serial.begin(57600);

    // Enable analog input pins to read values for debugging and calibration
    pinMode(WATER_METER_ANALOG, INPUT);
    pinMode(WATER_METER_REF, INPUT);

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    // Setup the Water meter comparitor
    analogComparator.setOn(ANALOG_CMP_A, ANALOG_CMP_B); //we instruct the lib to use voltages on the pins
    analogComparator.enableInterrupt(waterInterrupt, CHANGE); //we set the interrupt and when it has to be raised

    // Init the timers
    unsigned long now = millis();
    WATER_DEBOUNCE_TIMER = now;
    Serial.println("STARTUP Complete");
}



void loop() {
    int total = 0;
    int avg_value = 0;
    int avg_ref = 0;

    // Read the analog value from the hall effect sensor
    total = 0;
    for (int x =0; x< 16; x++) {
        total += analogRead(WATER_METER_ANALOG);
    }
    avg_value = total/16;


    // Read the reference voltage that is being compared against
    total = 0;
    for (int x =0; x< 16; x++) {
        total += analogRead(WATER_METER_REF);
    }
    avg_ref = total/16;
    Serial.print("CALIBRATION: ref: ");
    Serial.print(avg_ref);
    Serial.print(", meas: ");
    Serial.print(avg_value);

    Serial.print(", DIFF: ");
    Serial.print(avg_value - avg_ref);
    Serial.print(", cnt: ");
    Serial.println(WATER_COUNTER);    

    delay(100);
}