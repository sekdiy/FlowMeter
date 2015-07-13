#include <Streaming.h>  // http://arduiniana.org/libraries/streaming/
#include <Relay.h>      // https://github.com/sekdiy/Relay
#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// simulation period and pulse rate
const unsigned long period = 1000;    // ms
const unsigned long frequency = 10;   // Hz

// create a flow meter and a simulator (see notes on your Arduino model for pin numbers)
FlowMeter Meter = FlowMeter(2);
Relay Simulator = Relay(13);

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void MeterISR() {
  // let our flow meter count the pulses
  Meter.count();
}

void setup() {
  // prepare serial communication
  Serial.begin(9600);

  // enable a call to the 'interrupt service handler' (ISR) on every rising edge at the interrupt pin
  // do this setup step for every ISR you have defined, depending on how many interrupts you use
  attachInterrupt(INT0, MeterISR, RISING);
}

void loop() {

  // process the counted ticks
  Meter.tick(period);

  // output some measurement result
  Serial << "FlowMeter "
         << "- flow rate: " << Meter.getCurrentFlowrate() << " l/min, "
         << "error (corrected): " << Meter.getCurrentError() * 100 << " %, "
         << "total volume: " << Meter.getTotalVolume() << " l, "
         << "average flow rate: " << Meter.getTotalFlowrate() << " l/min, "
         << "average error (corrected): " << Meter.getTotalError() * 100 << " %, "
         << "total duration: " << Meter.getTotalDuration() / period << " s."
         << endl;

  // simulate flow meter pulses inbetween output updates
  for (unsigned long int i = 0; i < period; i++) {
    if (0 == i % (int) ((1000.0f * 1/frequency) / 2.0f)) {
      Simulator.toggle();
    } else {
      delay(1);
    }
  }

}
