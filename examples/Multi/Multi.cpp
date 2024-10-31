#include "Arduino.h"
#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers)
FlowMeter *Meter1;
FlowMeter *Meter2;

// set the measurement update period to 1s (1000 ms)
const unsigned long period = 1000;

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void Meter1ISR() {
    // let our flow meter count the pulses
    Meter1->count();
}

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void Meter2ISR() {
    // let our flow meter count the pulses
    Meter2->count();
}

void setup() {
    // prepare serial communication
    Serial.begin(115200);

    // get a new FlowMeter instance for an uncalibrated flow sensor and let them attach their 'interrupt service handler' (ISR) on every rising edge
    Meter1 = new FlowMeter(2, UncalibratedSensor, Meter1ISR, RISING);
    
    // do this setup step for every  FlowMeter and ISR you have defined, depending on how many you need
    Meter2 = new FlowMeter(3, UncalibratedSensor, Meter2ISR, RISING);
}

void loop() {
    // wait between output updates
    delay(period);

    // update the flow measurement calculations
    Meter1->update(period);
    Meter2->update(period);

    // fetch and output some measurement results
    Serial.println("Meter 1 currently " + String(Meter1->getCurrentFlowrate()) + " l/min, " + String(Meter1->getTotalVolume())+ " l total.");
    Serial.println("Meter 2 currently " + String(Meter2->getCurrentFlowrate()) + " l/min, " + String(Meter2->getTotalVolume())+ " l total.");

    //
    // any other code can go here
    //
}
