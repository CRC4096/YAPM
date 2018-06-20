#pragma once

#include "powermeasurement.h"
#include <vector>

namespace PowerMeasurementService{

using namespace DataContainer::Power;

/*
 * To Dos
 * - strong type: create class for startData and endData
 * - error type: create class for return values which returns bool
 */

class PowerMeasurmentInterface{
    virtual ~PowerMeasurmentInterface() = default;

    virtual std::vector<PowerMeasurement> getAllDataPoints() const = 0;
    virtual std::vector<PowerMeasurement> getDataPoints(long startData, long endData) const = 0;

    virtual bool addDataPoint(const PowerMeasurement& measurement) = 0;
    virtual bool addMultipleDataPoints(const std::vector<PowerMeasurement>& measurements) = 0;

    virtual bool containsDataPoint(const PowerMeasurement& measurement) const = 0;
    virtual long countDataPoints(long startData, long endData) const = 0;

    virtual bool removeDataPoint(const PowerMeasurement& measurement) = 0;

};


} //Namespace PowerMeasurementService
