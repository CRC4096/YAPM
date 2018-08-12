#pragma once

#include <stdio.h>

#include "gtest/gtest.h"
#include <memory>

#include "PowerMeasurementService.hpp"
#include "CsvImpl.hpp"
#include "DummyImpl.hpp"

using Interface = YAPM::Service::PowerMeasurmentInterface;

typedef Interface* CreateInterfaceFunc();

Interface* CreateCsvInterface(){
//    std::cout << "[          ] Testing CSV Implementation\n";
    return new YAPM::Service::Implementation::CsvPowerServiceImpl();
}

Interface* CreateDummyInterface(){
//    std::cout << "[          ] Testing Dummy Implementation\n";
    return new YAPM::Service::Implementation::DummyPowerServiceImpl();
}

class InterfaceTest : public ::testing::TestWithParam<CreateInterfaceFunc*>
{
public:
    InterfaceTest() {m_interface.reset((*GetParam())());}
    virtual ~InterfaceTest() {
        m_interface.get()->removeAllDatapoints();
    }


protected:
    std::unique_ptr<Interface> m_interface;
};
