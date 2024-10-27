/**
 * Flow Meter
 *
 * An Arduino flow meter library that provides calibrated liquid flow and volume measurement with flow sensors.
 *
 * @author sekdiy (https://github.com/sekdiy/FlowMeter)
 * @date 14.07.2024 Initial release.
 * @version See git comments for changes.
 */

#ifndef _FLOWSENSORCALIBRATION_H_
#define _FLOWSENSORCALIBRATION_H_s

#include "FlowSensorProperties.h"

/**
 * FlowSensorCalibration
 *
 * Convenience class for manipulating sensor properties.
 */
class FlowSensorCalibration {
  public:
    FlowSensorCalibration() {};
    FlowSensorCalibration(FlowSensorProperties properties): _properties(properties) {};

    FlowSensorCalibration* setProperties(FlowSensorProperties properties) {
        this->_properties = properties;
        return this;
    };

    FlowSensorCalibration* setCapacity(double capacity) {
        this->_properties.capacity = capacity;
        return this;
    }

    FlowSensorCalibration* setKFactor(double kFactor) {
        this->_properties.kFactor = kFactor;
        return this;
    }

    FlowSensorCalibration* setMeterFactorPerDecile(unsigned int decile, unsigned int mFactor) {
        this->_properties.mFactor[decile] = mFactor;
        return this;
    }

    FlowSensorProperties getProperties() {
        return this->_properties;
    }

    double getCapacity() {
        return this->_properties.capacity;
    }

    double getKFactor() {
        return this->_properties.kFactor;
    }

    unsigned int getMeterFactorPerDecile(unsigned int decile) {
        return this->_properties.mFactor[decile];
    }

  protected:
    FlowSensorProperties _properties;
};

#endif  // _FLOWSENSORCALIBRATION_H_
