#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers)
FlowMeter Meter1 = FlowMeter(2);
FlowMeter Meter2 = FlowMeter(3);

// set the measurement update period to 1s (1000 ms)
const unsigned long period = 1000;

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void Meter1ISR() {
    // let our flow meter count the pulses
    Meter1.count();
}

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void Meter2ISR() {
    // let our flow meter count the pulses
    Meter2.count();
}

void setup() {
    // prepare serial communication
    Serial.begin(9600);

    // enable a call to the 'interrupt service handler' (ISR) on every rising edge at the interrupt pin
    // do this setup step for every ISR you have defined, depending on how many interrupts you use
    attachInterrupt(INT0, Meter1ISR, RISING);
    attachInterrupt(INT1, Meter2ISR, RISING);

    // sometimes initializing the gear generates some pulses that we should ignore
    Meter1.reset();
    Meter2.reset();
}

void loop() {
    // wait between output updates
    delay(period);

    // process the (possibly) counted ticks
    Meter1.tick(period);
    Meter2.tick(period);

    // output some measurement result
    Serial.println("Meter 1 currently " + String(Meter1.getCurrentFlowrate()) + " l/min, " + String(Meter1.getTotalVolume())+ " l total.");
    Serial.println("Meter 2 currently " + String(Meter2.getCurrentFlowrate()) + " l/min, " + String(Meter2.getTotalVolume())+ " l total.");

    //
    // any other code can go here
    //
}