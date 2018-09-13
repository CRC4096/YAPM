#include "LocalImpl.hpp"

#include <algorithm>

using namespace YAPM::Service::Implementation;
using namespace DataContainer::Power;


LocalMetricsImplementation::LocalMetricsImplementation()
{

}

LocalMetricsImplementation::~LocalMetricsImplementation()
{

}

PowerMeasurement<kWh> LocalMetricsImplementation::getAverageConsumption(const std::vector<PowerMeasurement<kWh> > data, long interval)
{
    PowerMeasurement<kWh> retVal;

    auto elements = std::minmax_element(data.begin(), data.end(), [](const PowerMeasurement<kWh>& a, const PowerMeasurement<kWh>& b){
       return a.getUnixTimestamp() < b.getUnixTimestamp();
    });

    PowerMeasurement<kWh> min = *(elements.first);
    PowerMeasurement<kWh> max = *(elements.second);

    auto consumptionDifference = max.getValue() - min.getValue();
    auto timeDifference = max.getUnixTimestamp() - min.getUnixTimestamp();

    retVal.setValue((consumptionDifference*interval)/timeDifference);
    retVal.setTime(interval);

    return retVal;
}

PowerMeasurement<kWh> LocalMetricsImplementation::getForecast(const std::vector<PowerMeasurement<kWh> > data, long timepoint)
{
    PowerMeasurement<kWh> retVal;

    auto elements = std::minmax_element(data.begin(), data.end(), [](const PowerMeasurement<kWh>& a, const PowerMeasurement<kWh>& b){
       return a.getUnixTimestamp() < b.getUnixTimestamp();
    });

    PowerMeasurement<kWh> min = *(elements.first);
    PowerMeasurement<kWh> max = *(elements.second);

    auto consumptionDifference = max.getValue() - min.getValue();
    auto timeDifference = max.getUnixTimestamp() - min.getUnixTimestamp();
    auto consumptionPerSecond = (consumptionDifference)/timeDifference;

    retVal.setValue(consumptionPerSecond * timepoint);
    retVal.setTime(timepoint);

    return retVal;

}
