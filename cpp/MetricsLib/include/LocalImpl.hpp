#pragma once

#include "PowerMeasurementMetricsInterface.hpp"

namespace YAPM {
namespace Service {
namespace Implementation{

class LocalMetricsImplementation : public PowerMetricsInterface {
public:
    LocalMetricsImplementation();
    ~LocalMetricsImplementation() final;

    // PowerMetricsInterface interface
public:
    PowerMeasurement<kWh> getAverageConsumption(const std::vector<PowerMeasurement<kWh> > data, long interval);
    PowerMeasurement<kWh> getForecast(const std::vector<PowerMeasurement<kWh> > data, long timepoint);
};


} //namespace Implementation
} //namespace Service
} //YAPM
