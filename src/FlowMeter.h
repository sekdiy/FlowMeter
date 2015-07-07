/**
 * Flow Meter library
 *
 * Provides liquid flow and volume measurement by attaching a flow meter to an interrupt pin.
 *
 * @author sekdiy (https://github.com/sekdiy/FlowMeter)
 * @date 7.07.2015
 * @version See git comments for changes.
 */

#ifndef FLOWMETER_H
#define FLOWMETER_H

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class FlowMeter
{
  public:
    FlowMeter(unsigned int pin,                //!< The pin that the flow meter is connected to (has to be interrupt capable).
              float cal = 4.8                  //!< The calibration factor (in pulses per second per litre per minute).
            );                                 //!< Constructor. Initializes a new flow meter object.

    unsigned int getPin();                     //!< Returns the Arduino pin number that the flow meter is connected to.

    float getCurrentFlowrate();                //!< Returns the current flow rate since last reset (in l/min).
    float getCurrentVolume();                  //!< Returns the current volume since last reset (in l).

    float getAverageFlowrate();                //!< Returns the average flow rate in this flow meter instance (in l/min).
    float getTotalVolume();                    //!< Returns the total volume flown trough this flow meter instance (in l).
    float getTotalDuration();                  //!< Returns the total run time of this flow meter instance (in s).

    /**
     * Updates all internal calculations at the end of a measurement period.
     *
     * We're calculating flow and volume data over time.
     * The actual pulses have to be sampled using count().
     *
     * @param duration The sample duration (in s).
     */
    void tick(float duration);
    void count();                              //!< Increments the internal pulse counter. Serves as an interrupt callback routine.
    void reset();                              //!< Prepares the flow meter for a fresh measurement. Resets all current values.

  protected:
    unsigned int _pin;                         //!< connection pin (has to be interrupt capable!)
    float _cal;                                //!< calibration factor (in pulses / s / l / min), e.g.: 1 pulse / s = _cal * l / min

    float _currentFlowrate = 0.0f;             //!< current flow rate (in l/min), e.g.: 1 l / min = 1 pulse / s / (pulses / s / l / min)
    float _currentVolume = 0.0f;               //!< current volume (in l), e.g.: 1 l = 1 (l / min) / (60 * s)

    float _averageFlowrate = 0.0f;             //!< average flow rate since begin of measurement (in l/min)
    float _totalVolume = 0.0f;                 //!< total volume since begin of measurement (in l)
    float _totalDuration = 0.0f;               //!< total measured duration since begin of measurement (in s)

    volatile unsigned long _currentPulses = 0; //!< pulses within current sample period
};

#endif   // FLOWMETER_H
