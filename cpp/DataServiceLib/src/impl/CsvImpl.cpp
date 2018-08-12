#include "CsvImpl.hpp"

#include <algorithm>
#include <fstream>

using namespace YAPM::Service::Implementation;
using namespace DataContainer::Power;


CsvPowerServiceImpl::CsvPowerServiceImpl() : m_dataStorage(), m_filename("data.csv")
{
    loadDataFromFile();
}

CsvPowerServiceImpl::CsvPowerServiceImpl(const std::string &filename) : m_dataStorage(), m_filename(filename)
{
    loadDataFromFile();
}

CsvPowerServiceImpl::~CsvPowerServiceImpl()
{
    saveDataToFile();
}

void CsvPowerServiceImpl::loadDataFromFile()
{
    std::ifstream file(m_filename);
    long unixTimestamp; char delimiter; double powerValue;

    while( (file >> unixTimestamp >> delimiter >> powerValue) ){
        m_dataStorage.push_back(PowerMeasurement(PowerValue<kWh>(powerValue), unixTimestamp));
    }
}

void CsvPowerServiceImpl::saveDataToFile()
{
    std::ofstream file(m_filename);
    for(size_t i = 0; i < m_dataStorage.size(); ++i){
        const auto& measurement = m_dataStorage.at(i);
        file << measurement.getUnixTimestamp() << ',' << measurement.getValue() << "\n";
    }
}

std::vector<PowerMeasurement<kWh> > CsvPowerServiceImpl::getAllDataPoints() const
{
    return m_dataStorage;
}

std::vector<PowerMeasurement<kWh> > CsvPowerServiceImpl::getDataPoints(long startDate, long endDate) const
{
    std::vector<PowerMeasurement<kWh>> retVal;
    std::copy_if(m_dataStorage.cbegin(), m_dataStorage.cend(), retVal.begin(), [startDate, endDate](const PowerMeasurement<kWh>& item){
        auto timestamp = item.getUnixTimestamp();
        return timestamp >= startDate && timestamp <= endDate;
    });
    return retVal;
}

void CsvPowerServiceImpl::addDataPoint(const PowerMeasurement<kWh> &measurement)
{
    //for more performant inserting, find the correct place and insert it directly instead of sorting it afterwards. the storage is sorted
    m_dataStorage.emplace_back(measurement);
    std::sort(m_dataStorage.begin(), m_dataStorage.end());
}

void CsvPowerServiceImpl::addMultipleDataPoints(const std::vector<PowerMeasurement<kWh> > &measurements)
{
    //for more performant inserting, find the correct place and insert it directly instead of sorting it afterwards
    m_dataStorage.reserve(m_dataStorage.size() + measurements.size());
    for(const auto& measurement : measurements){
        m_dataStorage.push_back(measurement);
    }
    std::sort(m_dataStorage.begin(), m_dataStorage.end());
}

bool CsvPowerServiceImpl::containsDataPoint(const PowerMeasurement<kWh> &measurement) const
{
    auto i = std::find(m_dataStorage.cbegin(), m_dataStorage.cend(), measurement);
    return i != m_dataStorage.cend();
}

long CsvPowerServiceImpl::countDataPoints() const
{
    return m_dataStorage.size();
}

long CsvPowerServiceImpl::countDataPoints(long startDate, long endDate) const
{
    return std::count_if(m_dataStorage.cbegin(), m_dataStorage.cend(), [startDate, endDate](const PowerMeasurement<kWh>& item){
        auto timestamp = item.getUnixTimestamp();
        return timestamp >= startDate && timestamp <= endDate;
    });
}

bool CsvPowerServiceImpl::removeDataPoint(const PowerMeasurement<kWh> &measurement)
{
    auto i = std::remove(m_dataStorage.begin(), m_dataStorage.end(), measurement);
    if(i != m_dataStorage.end()){
        m_dataStorage.erase(i, m_dataStorage.end());
        return true;
    }
    else
        return false;
}

bool CsvPowerServiceImpl::removeAllDatapoints()
{
    m_dataStorage.clear();
    return m_dataStorage.size() == 0;
}