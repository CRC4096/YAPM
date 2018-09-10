#include "DummyImpl.hpp"

#include <algorithm>

using namespace YAPM::Service::Implementation;
using namespace DataContainer::Power;


DummyPowerServiceImpl::DummyPowerServiceImpl() : m_dataStorage()
{
}

std::vector<PowerMeasurement<kWh> > DummyPowerServiceImpl::getAllDataPoints() const
{
    return m_dataStorage;
}

std::vector<PowerMeasurement<kWh> > DummyPowerServiceImpl::getDataPoints(long startDate, long endDate) const
{
    std::vector<PowerMeasurement<kWh>> retVal;
    std::copy_if(m_dataStorage.cbegin(), m_dataStorage.cend(), retVal.begin(), [startDate, endDate](const PowerMeasurement<kWh>& item){
        auto timestamp = item.getUnixTimestamp();
        return timestamp >= startDate && timestamp <= endDate;
    });
    return retVal;
}

void DummyPowerServiceImpl::addDataPoint(const PowerMeasurement<kWh> &measurement)
{
    //for more performant inserting, find the correct place and insert it directly instead of sorting it afterwards. the storage is sorted
    m_dataStorage.emplace_back(measurement);
    std::sort(m_dataStorage.begin(), m_dataStorage.end());
}

void DummyPowerServiceImpl::addMultipleDataPoints(const std::vector<PowerMeasurement<kWh> > &measurements)
{
    //for more performant inserting, find the correct place and insert it directly instead of sorting it afterwards
    m_dataStorage.reserve(m_dataStorage.size() + measurements.size());
    for(const auto& measurement : measurements){
        m_dataStorage.push_back(measurement);
    }
    std::sort(m_dataStorage.begin(), m_dataStorage.end());
}

bool DummyPowerServiceImpl::containsDataPoint(const PowerMeasurement<kWh> &measurement) const
{
    auto i = std::find(m_dataStorage.cbegin(), m_dataStorage.cend(), measurement);
    return i != m_dataStorage.cend();
}

long DummyPowerServiceImpl::countDataPoints() const
{
    return m_dataStorage.size();
}

long DummyPowerServiceImpl::countDataPoints(long startDate, long endDate) const
{
    return std::count_if(m_dataStorage.cbegin(), m_dataStorage.cend(), [startDate, endDate](const PowerMeasurement<kWh>& item){
        auto timestamp = item.getUnixTimestamp();
        return timestamp >= startDate && timestamp <= endDate;
    });
}

bool DummyPowerServiceImpl::removeDataPoint(const PowerMeasurement<kWh> &measurement)
{
    auto i = std::remove(m_dataStorage.begin(), m_dataStorage.end(), measurement);
    if(i != m_dataStorage.end()){
        m_dataStorage.erase(i, m_dataStorage.end());
        return true;
    }
    else
        return false;
}

bool DummyPowerServiceImpl::removeAllDatapoints()
{
    m_dataStorage.clear();
    return m_dataStorage.size() == 0;
}
