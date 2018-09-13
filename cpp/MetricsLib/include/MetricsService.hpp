#pragma once

#include "PowerMeasurementMetricsInterface.hpp"

#include <memory>


namespace YAPM {
namespace Service {

    std::unique_ptr<PowerMetricsInterface> getLocalImplementation();
    std::unique_ptr<PowerMetricsInterface> getWebServiceImplementation();
}
}
