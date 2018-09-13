#pragma once

#include "powermeasurement.h"
#include <vector>

namespace YAPM {
namespace Service {

using namespace DataContainer::Power;

/*
 * averageConsumptionPerInterval
 * forecastToDate
 */


class PowerMetricsInterface{
public:
    virtual ~PowerMetricsInterface() = default;

    /**
     * @brief getAverageConsumption - calculates the average consumption in the interval
     * @param data
     * @param interval - defines the interval which should be used in a unixtimestamp manner. i.e. one
     * minute equals 60, a hour 3600, a day 86400
     * @return the average consumption in kWh
     */
    virtual PowerMeasurement<kWh> getAverageConsumption(const std::vector<PowerMeasurement<kWh>> data, long interval) = 0;

    /**
     * @brief getForecast - tries to forecast the consumption based on the given data. The first entry will be taken as a base
     * and it may therefore be necessary that the starting point, i.e. the start of a year, must be inserted with a 0 value
     * @param data
     * @param timepoint - a point in the future (as a unix timestamp) for which the measurement should be forecasted
     * @return the forecasted consumption in kWh
     */
    virtual PowerMeasurement<kWh> getForecast(const std::vector<PowerMeasurement<kWh>> data, long timepoint) = 0;

};

} //namespace Service
} //namespace YAPM
