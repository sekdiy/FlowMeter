#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers)
FlowMeter *Meter;

// set the measurement update period to 1s (1000 ms)
const unsigned long period = 1000;

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void MeterISR() {
    // let our flow meter count the pulses
    Meter->count();
}

void setup() {
    // prepare serial communication
    Serial.begin(9600);

    Meter = new FlowMeter(digitalPinToInterrupt(2), UncalibratedSensor, MeterISR, RISING);

    // sometimes initializing the gear generates some pulses that we should ignore
    Meter->reset();
}

void loop() {
    // wait between output updates
    delay(period);

    // process the (possibly) counted ticks
    Meter->tick(period);

    // output some measurement result
    Serial.println("Currently " + String(Meter->getCurrentFlowrate()) + " l/min, " + String(Meter->getTotalVolume())+ " l total.");

    //
    // any other code can go here
    //
}
