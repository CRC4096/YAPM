#pragma once

#include "PowerMeasurementInterface.hpp"

#include <memory>

namespace YAPM {
namespace Service {

    std::unique_ptr<PowerMeasurmentInterface> getCSVImplementation(const char* filename);
    std::unique_ptr<PowerMeasurmentInterface> getWebServiceImplementation();

} //namespace Service
} //namespace YAPM
