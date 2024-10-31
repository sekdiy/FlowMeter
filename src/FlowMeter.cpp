/**
 * Flow Meter
 *
 * An Arduino flow meter library that provides calibrated liquid flow and volume measurement with flow sensors.
 *
 * @author sekdiy (https://github.com/sekdiy/FlowMeter)
 * @date 14.07.2015 Initial release.
 * @version See git comments for changes.
 */

#include <math.h>
#include "Arduino.h"
#include "FlowMeter.h"                                                      // https://github.com/sekdiy/FlowMeter

FlowMeter::FlowMeter(unsigned int pin, FlowSensorProperties prop, void (*callback)(void), uint8_t interruptMode) :
    _pin(pin),                                                              // store pin number
    _properties(prop),                                                      // store sensor properties
    _interruptCallback(callback),
    _interruptMode(interruptMode)                                            
{
    pinMode(this->_pin, INPUT_PULLUP);                                      // initialize interrupt pin as input with pullup

    if (this->_interruptCallback != NULL) {                                 // if ISR callback has been provided, attach it
        attachInterrupt(digitalPinToInterrupt(this->_pin), this->_interruptCallback, this->_interruptMode);
    }

    this->reset();                                                          // ignore pulses generated during initialisation
}

double FlowMeter::getCurrentFlowrate() {
    return this->_currentFlowrate;                                          // in l/min
}

double FlowMeter::getCurrentVolume() {
    return this->_currentVolume;                                            // in l
}

double FlowMeter::getTotalFlowrate() {
    return this->_totalVolume / (this->_totalDuration / 1000.0f) * 60.0f;   // in l/min
}

double FlowMeter::getTotalVolume() {
    return this->_totalVolume;                                              // in l
}

/**
 * The update method updates all internal calculations at the end of a measurement period.
 *
 * We're calculating flow and volume data over time.
 * The actual pulses have to be sampled using the count method (i.e. via an interrupt service routine).
 *s
 * Flow sensor formulae:
 *
 * Let K: pulses per second per unit of measure (i.e. (1/s)/(l/min)),
 *     f: pulse frequency (1/s),
 *     Q: flow rate (l/min),
 *     p: sensor pulses (no dimension/unit),
 *     t: time since last measurements (s).
 *
 * K = f / Q             | units: (1/s) / (l/min) = (1/s) / (l/min)
 * <=>                   | Substitute p / t for f in order to allow for different measurement intervals
 * K = (p / t) / Q       | units: ((1/s)/(l/min)) = (1/s) / (l/min)
 * <=>                   | Solve for Q:
 * Q = (p / t) / K       | untis: l/min = 1/s / (1/s / (l/min))
 * <=>                   | Volume in l:
 * V = Q / 60            | units: l = (l/min) / (min)
 *
 * The property K is sometimes stated in pulses per liter or pulses per gallon.
 * In these cases the unit of measure has to be converted accordingly (e.g. from gal/s to l/min).
 * See file G34_Flow_rate_to_frequency.jpg for reference.
 *
 * @param duration The update duration (in ms).
 */
void FlowMeter::update(unsigned long duration) {
    /* sampling */
    noInterrupts();                                                         // going to change interrupt variable(s)
    volatile unsigned long pulses = this->_currentPulses;                   // sample current pulses from counter
    this->_currentPulses = 0;                                               // reset pulse counter after successful sampling
    interrupts();                                                           // done changing interrupt variable(s)

    /* normalisation */
    double seconds = duration / 1000.0f;                                    // normalised duration (in s, i.e. per 1000ms)
    double frequency = pulses / seconds;                                    // normalised frequency (in 1/s)

    /* determine current correction factor (from sensor properties) */
    unsigned int decile = floor(10.0f * frequency / (this->_properties.capacity * this->_properties.kFactor));          // decile of current flow relative to sensor capacity
    unsigned int ceiling =  9;                                                                                          // highest possible decile index
    this->_currentCorrection = this->_properties.kFactor / this->_properties.mFactor[min(decile, ceiling)];             // combine constant k-factor and m-factor for decile

    /* update current calculations: */
    this->_currentFlowrate = frequency / this->_currentCorrection;          // get flow rate (in l/min) from normalised frequency and combined correction factor
    this->_currentVolume = this->_currentFlowrate / (60.0f/seconds);        // get volume (in l) from normalised flow rate and normalised time

    /* update statistics: */
    this->_currentDuration = duration;                                      // store current update duration (convenience, in ms)
    this->_currentFrequency = frequency;                                    // store current pulses per second (convenience, in 1/s)
    this->_totalDuration += duration;                                       // accumulate total duration (in ms)
    this->_totalVolume += this->_currentVolume;                             // accumulate total volume (in l)
    this->_totalCorrection += this->_currentCorrection * duration;          // accumulate corrections over time
}

void FlowMeter::count() {
    this->_currentPulses++;                                                 // this should be called from an interrupt service routine
}

void FlowMeter::reset() {
    noInterrupts();                                                         // going to change interrupt variable(s)
    this->_currentPulses = 0;                                               // reset pulse counter
    interrupts();                                                           // done changing interrupt variable(s)

    this->_currentFrequency = 0.0f;
    this->_currentDuration = 0.0f;
    this->_currentFlowrate = 0.0f;
    this->_currentVolume = 0.0f;
    this->_currentCorrection = 0.0f;
}

unsigned int FlowMeter::getPin() {
    return this->_pin;
}

unsigned long FlowMeter::getCurrentDuration() {
    return this->_currentDuration;                                          // in ms
}

double FlowMeter::getCurrentFrequency() {
    return this->_currentFrequency;                                         // in 1/s
}

double FlowMeter::getCurrentError() {
    // error (in %) = error * 100
    // error = correction rate - 1
    // correction rate = k-factor / correction
    return (this->_properties.kFactor / this->_currentCorrection - 1) * 100;  // in %
}

unsigned long FlowMeter::getTotalDuration() {
    return this->_totalDuration;                                            // in ms
}

double FlowMeter::getTotalError() {
    // average error (in %) = average error * 100
    // average error = average correction rate - 1
    // average correction rate = k-factor / corrections over time * total time
    return (this->_properties.kFactor / this->_totalCorrection * this->_totalDuration - 1) * 100;
}

FlowMeter* FlowMeter::setTotalDuration(unsigned long totalDuration) {
    this->_totalDuration = totalDuration;
    return this;
}

FlowMeter* FlowMeter::setTotalVolume(double totalVolume) {
    this->_totalVolume = totalVolume;
    return this;
}

FlowMeter* FlowMeter::setTotalCorrection(double totalCorrection) {
    this->_totalCorrection = totalCorrection;
    return this;
}
