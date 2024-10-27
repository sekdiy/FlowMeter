/**
 * Flow Meter
 *
 * An Arduino flow meter library that provides calibrated liquid flow and volume measurement with flow sensors.
 *
 * @author sekdiy (https://github.com/sekdiy/FlowMeter)
 * @date 14.07.2015 Initial release.
 * @version See git comments for changes.
 */

#ifndef __FLOWSENSORPROPERTIES_H_
#define __FLOWSENSORPROPERTIES_H_

/**
 * FlowSensorProperties
 *
 * Structure that holds essential information about a flow sensor.
 * Stores general sensor properties and calibration points.
 *
 * See file G34_Flow_rate_to_frequency.jpg for reference.
 */
typedef struct {
  double capacity;                              // capacity, upper limit of flow rate (in l/min)
  double kFactor;                               // "k-factor" (in (pulses/s) / (l/min)), e.g.: 1 pulse/s = kFactor * l/min
  double mFactor[10];                           // multiplicative correction factor near unity, "meter factor" (per decile of flow)
} FlowSensorProperties;

extern FlowSensorProperties UncalibratedSensor; // default sensor
extern FlowSensorProperties FS300A;             // see documentation about FS300A/SEN02141B
extern FlowSensorProperties FS400A;             // see documentation about FS400A/USN-HS10TA

#endif   // __FLOWSENSORPROPERTIES_H_
