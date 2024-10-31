/**
 * Flow Meter
 *
 * An Arduino flow meter library that provides calibrated liquid flow and volume measurement with flow sensors.
 *
 * @author sekdiy (https://github.com/sekdiy/FlowMeter)
 * @date 14.07.2015 Initial release.
 * @version See git comments for changes.
 */

#include "FlowSensorProperties.h"

FlowSensorProperties UncalibratedSensor = {60.0f, 5.0f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowSensorProperties FS300A = {60.0f, 5.5f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowSensorProperties FS400A = {60.0f, 4.8f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowSensorProperties FS400A_cal = {30.0f, 4.25f, {1.01695, 1.01695, 1.01695, 1.01695, 1, 0.99767, 0.99767, 0.99767, 1, 1.01695}};
FlowSensorProperties FHKCS_1mm_0deg = {0.4, 39.7, {1.0, 0.995, 0.9925, 0.992, 0.9925, 0.994, 0.995, 0.9975, 1.00125, 1.006}};
