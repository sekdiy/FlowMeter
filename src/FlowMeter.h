/**
 * Flow Meter library
 *
 * @author sekdiy
 * @date 21.06.2015
 * @version 2
 */

#ifndef FLOWMETER_H
#define FLOWMETER_H

// Compatibility with the Arduino 1.0 library standard
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
 * flow meter pin
 * pin 2 for interrupt 0
 * pin 3 for interrupt 1
 */
const int flowPin = 2;

/**
 * FlowMeter
 *
 * Provides liquid flow and volume measurement by attaching a flow meter to an interrupt pin.
 *
 * @version 2
 */
class FlowMeter
{
  public:
    FlowMeter(int pin, float cal = 4.5); // Constructor

    void attach(void isr() = FlowMeter::interrupt);
    float getPulseRate();               // get current frequency (in pulses per sample duration)
    float getFlowRate();                // get current flow rate (in l/min)
    float getFlowVolume();              // get current volume flow (in ml/s)
    float getTotalVolume();             // get total volume since last reset (in ml)
    void tick(float duration);          // update internal calculations
    void reset();                       // reset all values
    inline void count();                // increment internal pulse counter

  protected:
    int _pin;                           // connection pin (has to be interrupt capable!)
    int _cal;                           // calibration factor
    float _frequency;                   // current frequency (in pulses per sample duration)
    float _flowrate;                    // current flow rate (in l/min)
    float _flowVolume;                  // current volume flow (in ml/s)
    float _totalVolume;                 // total volume since last reset (in ml)
    volatile int _pulses;               // pulses within current sample period
    static volatile unsigned long _totalPulses;

    static inline void interrupt();
};

extern FlowMeter Meter; // flow meter on pin 2

#endif   // FLOWMETER_H

