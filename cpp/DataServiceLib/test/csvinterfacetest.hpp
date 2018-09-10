#pragma once

#include <stdio.h>

#include "gtest/gtest.h"

#include "PowerMeasurementService.hpp"
#include "CsvImpl.hpp"

using PowerContainer = DataContainer::Power::PowerMeasurement<DataContainer::Power::kWh>;
using CsvInterface = YAPM::Service::Implementation::CsvPowerServiceImpl;

CsvInterface getInterface();
std::vector<PowerContainer> getData();

//https://github.com/google/googletest/blob/master/googletest/docs/Primer.md#simple-tests
class CsvInterfaceTest : public ::testing::Test
{
public:
    CsvInterfaceTest() {}
    virtual ~CsvInterfaceTest() { }
    virtual void SetUp() {}
    virtual void TearDown() {
        auto interface = getInterface();
        interface.removeAllDatapoints();
    }
};

