/**
 * Flow Meter library
 *
 * @author sekdiy
 * @date 21.06.2015
 * @version 2
 */

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "FlowMeter.h"

/**
 * FlowMeter constructor
 *
 * Provides liquid flow and volume measurement by attaching a flow meter to an interrupt pin.
 *
 * @param int pin The pin that the flow meter is connected to.
 * @param float cal The calibration factor in pulses per litre per minute.
 * @version 2
 */
FlowMeter::FlowMeter(int pin, float cal) : _pin(pin), _cal(cal)
{
  this->reset();                            // initialize internal model

  pinMode(pin, INPUT);                      // initialize interrupt pin as input
  digitalWrite(pin, HIGH);                  // pull up flow meter signal line

  this->attach();
}

/**
 * attach
 *
 * @param int interrupt The interrupt associated with the input pin.
 * @param void isr() The interrupt service routine that calls countPulse().
 * @version 1
 */
void FlowMeter::attach(void isr()) {
  attachInterrupt(this->_pin - 2, isr, RISING);  // attached interrupt service routine
}

/**
 * getPulseRate
 *
 * @return The current frequency (in pulses per sample duration).
 * @version 1
 */
float FlowMeter::getPulseRate() {
    return this->_frequency;
}

/**
 * getFlowRate
 *
 * @return The current flow rate (in l/min).
 * @version 1
 */
float FlowMeter::getFlowRate() {
    return this->_flowrate;
}

/**
 * getFlowVolume
 *
 * @return The current volume flow (in ml/s).
 * @version 1
 */
float FlowMeter::getFlowVolume() {
    return this->_flowVolume;
}

/**
 * getTotalVolume
 *
 * @return The total volume since last reset (in ml).
 * @version 1
 */
float FlowMeter::getTotalVolume() {
    return this->_totalVolume;
}

/**
 * tick
 *
 * Updates all internal calculations at the end of a measurement period.
 *
 * We're sampling flow and volume data over time.
 * Note that the term sampling might be ambiguous.
 * The actual pulses have to be sampled elsewhere (i.e. using countPulse() on external interrupt).
 *
 * @param float duration The sample duration.
 * @version 1
 */
void FlowMeter::tick(float duration) {
    /* update rate */
    this->_frequency = this->_pulses / duration;
    this->_flowrate = this->_pulses / this->_cal;

    /* update volume */
    this->_flowVolume = (this->_flowrate / 60) * 1000;
    this->_totalVolume += this->_flowVolume;

    /* reset counter */
    this->_pulses = 0;
}

/**
 * count
 *
 * Increments the internal pulse counter.
 * Serves as an interrupt callback routine.
 *
 * @version 1
 */
void FlowMeter::count() {
    noInterrupts();

    this->_pulses++;

    interrupts();
}

/**
 * reset
 *
 * Prepares the flow meter for a fresh measurement.
 *
 * @version 1
 */
void FlowMeter::reset() {
    this->_pulses = 0;
    this->_frequency =  0.0;
    this->_flowrate = 0.0;
    this->_flowVolume = 0.0;
    this->_totalVolume = 0.0;
}

void FlowMeter::interrupt() {
    Meter.count();
}

FlowMeter Meter = FlowMeter(flowPin); // flow meter pin from header definition
