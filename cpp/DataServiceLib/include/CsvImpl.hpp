#pragma once

#include "PowerMeasurementInterface.hpp"

#include <set>

namespace YAPM {
namespace Service {
namespace Implementation{


class CsvPowerServiceImpl : public YAPM::Service::PowerMeasurmentInterface{
public:
    CsvPowerServiceImpl();
    CsvPowerServiceImpl(const std::string& filename);
    ~CsvPowerServiceImpl() final;

private:
    std::vector<PowerMeasurement<kWh>> m_dataStorage;
    const std::string m_filename;

    void loadDataFromFile();
    void saveDataToFile();

    // PowerMeasurmentInterface interface
public:
    std::vector<PowerMeasurement<kWh> > getAllDataPoints() const final;
    std::vector<PowerMeasurement<kWh> > getDataPoints(long startDate, long endDate) const final;
    void addDataPoint(const PowerMeasurement<kWh> &measurement) final;
    void addMultipleDataPoints(const std::vector<PowerMeasurement<kWh> > &measurements) final;
    bool containsDataPoint(const PowerMeasurement<kWh> &measurement) const final;
    long countDataPoints() const final;
    long countDataPoints(long startDate, long endDate) const final;
    bool removeDataPoint(const PowerMeasurement<kWh> &measurement) final;
    bool removeAllDatapoints() final;
};

} //namespace Implementation
} //namespace Service
} //YAPM
