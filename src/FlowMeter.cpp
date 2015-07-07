/*
 * Flow Meter library
 */

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "FlowMeter.h"

FlowMeter::FlowMeter(unsigned int pin, float cal) :
    _pin(pin),                              //!< store pin number
    _cal(cal)                               //!< store calibration factor
{
  pinMode(pin, INPUT_PULLUP);               //!< initialize interrupt pin as input with pullup
}

unsigned int FlowMeter::getPin() {
  return this->_pin;
}

float FlowMeter::getCurrentFlowrate() {
    return this->_currentFlowrate;
}

float FlowMeter::getCurrentVolume() {
    return this->_currentVolume;
}

float FlowMeter::getAverageFlowrate() {
    return this->_averageFlowrate;
}

float FlowMeter::getTotalVolume() {
    return this->_totalVolume;
}

float FlowMeter::getTotalDuration() {
    return this->_totalDuration;
}

void FlowMeter::tick(float duration) {
    /* update rate */
    this->_currentFlowrate = this->_currentPulses / this->_cal;

    /* update volume: */
    this->_currentVolume = this->_currentFlowrate / 60;

    // TODO does this miss the duration part?
    // diymaster03: "F=4.8 * units von flow (L / min) * time (seconds)"

    /// update rate: l / min = pulses / s / (pulses / s / l / min)
    // this->_currentFlowrate = this->_currentPulses / duration / this->_cal;

    /// update volume: l = (l / min) / (60 * s)
    // this->_currentVolume = this->_currentFlowrate / (60 * duration);

    /* update statistics */
    this->_totalDuration += duration;
    this->_totalVolume += this->_currentVolume;
    this->_averageFlowrate = this->_totalVolume / this->_totalDuration;

    /* reset counter */
    this->_currentPulses = 0;
}

void FlowMeter::count() {
    this->_currentPulses++;
}

void FlowMeter::reset() {
    this->_currentPulses = 0;
    this->_currentFlowrate = 0.0;
    this->_currentVolume = 0.0;
}
