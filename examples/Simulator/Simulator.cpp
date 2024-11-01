#include "Arduino.h"
#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// let's provide our own sensor properties, including calibration points for error correction
FlowSensorProperties MySensor = {60.0f, 4.5f, {1.2, 1.1, 1.05, 1, 1, 1, 1, 0.95, 0.9, 0.8}};
FlowMeter *Meter;

void setup() {
    // prepare serial communication
    Serial.begin(115200);

    // let's pretend there's a calibrated flow sensor connected to pin 3
    Meter = new FlowMeter(3, MySensor);
}

void loop() {
    // randomly change simulation period and pulse rate
    long frequency = random(MySensor.capacity * MySensor.kFactor);  // Hz
    long period = random(3 * frequency, 5000);                      // ms

    // simulate random flow meter pulses within a random period
    for (long i = 0; i < (long) ((float) period * (float) frequency / 1000.0f); i++) {
        Meter->count();
    }

    // wait that random period
    delay(period);

    // update the flow measurement calculations
    Meter->update(period);

    // fetch and output some measurement results
    Serial.println("FlowMeter - period: " + String(Meter->getCurrentDuration() / 1000.0f, 3) + "s, " +
                  "frequency: " + String(Meter->getCurrentFrequency(), 0) + "Hz, " +
                  "volume: " + Meter->getCurrentVolume() + "l, " +
                  "flow rate: " + Meter->getCurrentFlowrate() + "l/min, " +
                  "error: " + Meter->getCurrentError() + "%, " +
                  "total duration: " + Meter->getTotalDuration() / 1000.0f + "s, " +
                  "total volume: " + Meter->getTotalVolume() + "l, " +
                  "average flow rate: " + Meter->getTotalFlowrate() + "l/min, " +
                  "average error: " + Meter->getTotalError() + "%.");
}
