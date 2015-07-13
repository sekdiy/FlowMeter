/*
 * Flow Meter
 */

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "FlowMeter.h"                                                      // https://github.com/sekdiy/FlowMeter
#include <math.h>

FlowMeter::FlowMeter(unsigned int pin, FlowSensorProperties prop) :
    _pin(pin),                                                              //!< store pin number
    _properties(prop)                                                       //!< store sensor properties
{
  pinMode(pin, INPUT_PULLUP);                                               //!< initialize interrupt pin as input with pullup
}

unsigned int FlowMeter::getPin() {
    return this->_pin;
}

double FlowMeter::getCurrentFlowrate() {
    return this->_currentFlowrate;
}

double FlowMeter::getCurrentVolume() {
    return this->_currentVolume;
}

double FlowMeter::getCurrentError() {
    return this->_currentCorrection / this->_properties.kFactor - 1;
}

unsigned long FlowMeter::getCurrentDuration() {
    return this->_currentDuration;
}

double FlowMeter::getTotalFlowrate() {
    return this->_totalVolume / (this->_totalDuration / 1000.0f) * 60.0f;
}

double FlowMeter::getTotalVolume() {
    return this->_totalVolume;
}

double FlowMeter::getTotalError() {
    return (this->_totalCorrection / this->_properties.kFactor) / (this->_totalDuration / 1000.0f) - 1;
}

unsigned long FlowMeter::getTotalDuration() {
    return this->_totalDuration;
}

void FlowMeter::tick(unsigned long duration) {
    /* some convenience values */
    double seconds = duration / 1000.0f;                                    //!< normalised duration (in s, i.e. per 1000ms)
    double frequency = this->_currentPulses / seconds;                      //!< normalised frequency (in 1/s)

    /* determine current correction factor from static k-factor and flow dependend m-factor (both from sensor properties) */
    unsigned int decile = round(10 * frequency / (this->_properties.capacity * this->_properties.kFactor));  //!< decile of flow rate relative to sensor capacity
    this->_currentCorrection = this->_properties.kFactor * this->_properties.mFactor[decile];  //!< get k-factor and m-factor for decile from sensor properties

    /* update current calculations: */
    this->_currentFlowrate = frequency / this->_currentCorrection;          //!< apply correction factor to normalised frequency
    this->_currentVolume = this->_currentFlowrate / (60.0f/seconds);        //!< get volume from flow rate and normalised time

    /* update statistics: */
    this->_currentDuration = duration;                                      //!< store current tick duration (for normalisation purposes, in ms)
    this->_totalDuration += duration;                                       //!< accumulate total duration (in ms)
    this->_totalVolume += this->_currentVolume;                             //!< accumulate total volume (in l)
    this->_totalCorrection += this->_currentCorrection;                     //!< accumulated total correction sum

    /** reset counter: */
    this->_currentPulses = 0;
}

void FlowMeter::count() {
    this->_currentPulses++;
}

void FlowMeter::reset() {
    noInterrupts();                                                         //!< going to change interrupt variables...

    this->_currentPulses = 0;
    this->_currentDuration = 0.0f;
    this->_currentFlowrate = 0.0f;
    this->_currentVolume = 0.0f;
    this->_currentCorrection = 0.0f;

    interrupts();
}

/**
 * FS400A
 */
FlowSensorProperties FS400A = {60.0f, 4.5f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
