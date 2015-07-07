// #include <EnableInterrupt.h>  // https://github.com/GreyGnome/EnableInterrupt
#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter

// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers)
FlowMeter Meter = FlowMeter(2);

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
//  enableInterrupt(Meter.getPin(), MeterISR, RISING);
  attachInterrupt(0, MeterISR, RISING);
}

void loop() {
  // wait between output updates
  delay(1000);

  // process the (possibly) counted ticks
  Meter.tick(1.0f);

  // output some measurement result
  Serial.print("Meter has measured: ");
  Serial.print(Meter.getTotalVolume());
  Serial.println(" ml so far.");
}
