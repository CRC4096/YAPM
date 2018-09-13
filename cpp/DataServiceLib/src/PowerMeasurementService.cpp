#include "PowerMeasurementService.hpp"

#include "CsvImpl.hpp"


using namespace YAPM::Service;
using namespace YAPM::Service::Implementation;

std::unique_ptr<PowerMeasurmentInterface> getCSVImplementation(const char *filename)
{
    auto retVal = std::make_unique<CsvPowerServiceImpl>(filename);
    return retVal;
}
