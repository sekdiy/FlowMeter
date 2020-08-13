#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// enter your own sensor properties here, including calibration points
FlowSensorProperties MySensor = {60.0f, 5.5f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowMeter *Meter;

// timekeeping variables
long period = 1000;   // one second (in milliseconds)
long lastTime = 0;

// define an 'interrupt service routine' (ISR)
void MeterISR() {
    // let our flow meter count the pulses
    Meter->count();
}

void setup() {
    // prepare serial communication
    Serial.begin(115200);

    // get a new FlowMeter instance for an uncalibrated flow sensor on pin 2
    Meter = new FlowMeter(digitalPinToInterrupt(2), MySensor, MeterISR, RISING);
}

void loop() {
    // do some timekeeping
    long currentTime = millis();
    long duration = currentTime - lastTime;

    // wait between display updates
    if (duration >= period) {

        // process the counted ticks
        Meter->tick(duration);

        // output some measurement result
        Serial.println("FlowMeter - current flow rate: " + String(Meter->getCurrentFlowrate()) + " l/min, " +
                       "nominal volume: " + String(Meter->getTotalVolume()) + " l, " +
                       "compensated error: " + String(Meter->getCurrentError()) + " %, " +
                       "duration: " + String(Meter->getTotalDuration() / 1000) + " s.");

        // prepare for next cycle
        lastTime = currentTime;
    }
}
