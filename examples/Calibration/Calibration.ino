#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// enter your own sensor properties here, including calibration points
FlowSensorProperties MySensor = {60.0f, 5.5f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowMeter Meter = FlowMeter(2, MySensor);

// timekeeping variables
long period = 1000;   // one second (in milliseconds)
long lastTime = 0;

// define an 'interrupt service routine' (ISR)
void MeterISR() {
    // let our flow meter count the pulses
    Meter.count();
}

void setup() {
    // prepare serial communication
    Serial.begin(9600);

    // enable a call to the 'interrupt service handler' (ISR) on every rising edge at the interrupt pin
    attachInterrupt(INT0, MeterISR, RISING);

    // sometimes initializing the gear generates some pulses that we should ignore
    Meter.reset();
}

void loop() {
    // do some timekeeping
    long currentTime = millis();
    long duration = currentTime - lastTime;

    // wait between display updates
    if (duration >= period) {

        // process the counted ticks
        Meter.tick(duration);

        // output some measurement result
        Serial.println("FlowMeter - current flow rate: " + String(Meter.getCurrentFlowrate()) + " l/min, " +
                       "nominal volume: " + String(Meter.getTotalVolume()) + " l, " +
                       "compensated error: " + String(Meter.getCurrentError()) + " %, " +
                       "duration: " + String(Meter.getTotalDuration() / 1000) + " s.");

        // prepare for next cycle
        lastTime = currentTime;
    }
}
