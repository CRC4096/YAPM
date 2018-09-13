#include "MetricsService.hpp"

#include "LocalImpl.hpp"

using namespace YAPM::Service;
using namespace YAPM::Service::Implementation;

std::unique_ptr<PowerMetricsInterface> getLocalImplementation()
{
    auto retVal = std::make_unique<LocalMetricsImplementation>();
    return retVal;
}
