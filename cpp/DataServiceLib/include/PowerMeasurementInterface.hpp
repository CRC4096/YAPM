#pragma once

#include "powermeasurement.h"
#include <vector>

namespace YAPM{
namespace Service{

using namespace DataContainer::Power;

/*
 * To Dos
 * - strong type: create class for startData and endData
 * - error type: create class for return values which returns bool
 *   or define exceptions
 */


class PowerMeasurmentInterface{
public:
    virtual ~PowerMeasurmentInterface() = default;

    /**
     * @brief getAllDataPoints - retriev each and every single datapoint
     * @return
     */
    virtual std::vector<PowerMeasurement<kWh>> getAllDataPoints() const = 0;

    /**
     * @brief getDataPoints - retrieve datapoints from startDate to endDate
     * @param startDate - inclusive
     * @param endDate - inclusive
     * @return
     */
    virtual std::vector<PowerMeasurement<kWh>> getDataPoints(long startDate, long endDate) const = 0;

    /**
     * @brief addDataPoint - add a single datapoint to the database
     * @param measurement - kWh based
     */
    virtual void addDataPoint(const PowerMeasurement<kWh>& measurement) = 0;

    /**
     * @brief addMultipleDataPoints - add multiple datapoints to the database
     * @param measurements
     */
    virtual void addMultipleDataPoints(const std::vector<PowerMeasurement<kWh>>& measurements) = 0;

    /**
     * @brief containsDataPoint - does the database contain the measurement
     * @param measurement
     * @return
     */
    virtual bool containsDataPoint(const PowerMeasurement<kWh>& measurement) const = 0;

    /**
     * @brief countDataPoints - count the total number of datapoints;
     * @return
     */
    virtual long countDataPoints() const = 0;

    /**
     * @brief countDataPoints - count the amount of datapoints between the startDate and endDate
     * @param startDate - inclusive
     * @param endDate - inclusive
     * @return
     */
    virtual long countDataPoints(long startDate, long endDate) const = 0;

    /**
     * @brief removeDataPoint - removes the datapoint from the database
     * @param measurement
     * @return - if the database contains the datapoint and the removal was successfull the function returns true,
     *           false otherwise
     */
    virtual bool removeDataPoint(const PowerMeasurement<kWh>& measurement) = 0;

    /**
     * @brief removeAllDatapoints - removes each and every single datapoint
     * @return
     */
    virtual bool removeAllDatapoints() = 0;
};


} //namespace Service
} //Namespace YAPM
