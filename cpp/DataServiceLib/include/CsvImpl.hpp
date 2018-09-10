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
    ~CsvPowerServiceImpl() override final;

private:
    std::vector<PowerMeasurement<kWh>> m_dataStorage;
    const std::string m_filename;

    void loadDataFromFile();
    void saveDataToFile();

    // PowerMeasurmentInterface interface
public:
    std::vector<PowerMeasurement<kWh> > getAllDataPoints() const override final;
    std::vector<PowerMeasurement<kWh> > getDataPoints(long startDate, long endDate) const override final;
    void addDataPoint(const PowerMeasurement<kWh> &measurement) override final;
    void addMultipleDataPoints(const std::vector<PowerMeasurement<kWh> > &measurements) override final;
    bool containsDataPoint(const PowerMeasurement<kWh> &measurement) const override final;
    long countDataPoints() const override final;
    long countDataPoints(long startDate, long endDate) const override final;
    bool removeDataPoint(const PowerMeasurement<kWh> &measurement) override final;
    bool removeAllDatapoints() override final;
};

} //namespace Implementation
} //namespace Service
} //YAPM
