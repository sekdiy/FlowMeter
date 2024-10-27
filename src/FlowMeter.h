/**
 * Flow Meter
 *
 * An Arduino flow meter library that provides calibrated liquid flow and volume measurement with flow sensors.
 *
 * @author sekdiy (https://github.com/sekdiy/FlowMeter)
 * @date 14.07.2015 Initial release.
 * @version See git comments for changes.
 */

#ifndef _FLOWMETER_H_
#define _FLOWMETER_H_

#include "FlowSensorProperties.h"
#include "FlowSensorCalibration.h"

/**
 * FlowMeter
 */
class FlowMeter {
  public:
    /**
     * Initializes a new flow meter object.
     * 
     * @param pin  The pin that the flow sensor is connected to (has to be interrupt capable, default: INT0).
     * @param prop The properties of the actual flow sensor being used (default: UncalibratedSensor).
     */
    FlowMeter(unsigned int pin = 2, FlowSensorProperties prop = UncalibratedSensor, void (*callback)(void) = NULL, uint8_t interruptMode = RISING);

    double getCurrentFlowrate();                 // Returns the current flow rate since last tick (in l/min).
    double getCurrentVolume();                   // Returns the current volume since last tick (in l).

    double getTotalFlowrate();                   // Returns the (linear) average flow rate in this flow meter instance (in l/min).
    double getTotalVolume();                     // Returns the total volume flown trough this flow meter instance (in l).

    void tick(unsigned long duration = 1000);    // Updates all internal calculations at the end of a measurement period.
    void count();                                // Increments the internal pulse counter. Serves as an interrupt callback routine.
    void reset();                                // Prepares the flow meter for a fresh measurement. Resets all current values, but not the totals.

    /*
     * setters enabling continued metering across power cycles
     */ 

    FlowMeter* setTotalDuration(unsigned long totalDuration); // Sets the total (overall) duration (i.e. after power up).
    FlowMeter* setTotalVolume(double totalVolume);            // Sets the total (overall) volume (i.e. after power up).
    FlowMeter* setTotalCorrection(double totalCorrection);    // Sets the total (overall) correction factor (i.e. after power up).

    /*
     * convenience methods and calibration helpers
     */

    unsigned int getPin();                       // Returns the Arduino pin number that the flow sensor is connected to.

    unsigned long getCurrentDuration();          // Returns the duration of the current tick (in ms).
    double getCurrentFrequency();                // Returns the pulse rate in the current tick (in 1/s).
    double getCurrentError();                    // Returns the error resulting from the current measurement (in %).

    unsigned long getTotalDuration();            // Returns the total run time of this flow meter instance (in ms).
    double getTotalError();                      // Returns the (linear) average error of this flow meter instance (in %).

  protected:
    unsigned int _pin;                           // connection pin (has to be interrupt capable!)
    FlowSensorProperties _properties;            // sensor properties (including calibration data)
    void (*_interruptCallback)(void);            // interrupt callback
    uint8_t _interruptMode;                      // interrupt mode (LOW, CHANGE, RISING, FALLING, HIGH)

    unsigned long _currentDuration;              // current tick duration (convenience, in ms)
    double _currentFrequency;                    // current pulses per second (convenience, in 1/s)
    double _currentFlowrate = 0.0f;              // current flow rate (in l/tick), e.g.: 1 l / min = 1 pulse / s / (pulses / s / l / min)
    double _currentVolume = 0.0f;                // current volume (in l), e.g.: 1 l = 1 (l / min) / (60 * s)
    double _currentCorrection;                   // currently applied correction factor

    unsigned long _totalDuration = 0.0f;         // total measured duration since begin of measurement (in ms)
    double _totalVolume = 0.0f;                  // total volume since begin of measurement (in l)
    double _totalCorrection = 0.0f;              // accumulated correction factors

    volatile unsigned long _currentPulses = 0;   // pulses within current sample period
};

#endif   // _FLOWMETER_H_
