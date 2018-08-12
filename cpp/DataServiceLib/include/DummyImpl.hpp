#pragma once

#include "PowerMeasurementInterface.hpp"

#include <set>

namespace YAPM {
namespace Service {
namespace Implementation{


class DummyPowerServiceImpl : public YAPM::Service::PowerMeasurmentInterface{
public:
    DummyPowerServiceImpl();
    ~DummyPowerServiceImpl() = default;

    // PowerMeasurmentInterface interface
public:

private:
    std::vector<PowerMeasurement<kWh>> m_dataStorage;

    // PowerMeasurmentInterface interface
public:
    std::vector<PowerMeasurement<kWh> > getAllDataPoints() const;
    std::vector<PowerMeasurement<kWh> > getDataPoints(long startDate, long endDate) const;
    void addDataPoint(const PowerMeasurement<kWh> &measurement);
    void addMultipleDataPoints(const std::vector<PowerMeasurement<kWh> > &measurements);
    bool containsDataPoint(const PowerMeasurement<kWh> &measurement) const;
    long countDataPoints() const;
    long countDataPoints(long startDate, long endDate) const;
    bool removeDataPoint(const PowerMeasurement<kWh> &measurement);
    bool removeAllDatapoints();
};

} //namespace Implementation
} //namespace Service
} //YAPM
