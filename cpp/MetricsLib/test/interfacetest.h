#pragma once

#include <stdio.h>

#include "gtest/gtest.h"
#include <memory>

#include "PowerMeasurementMetricsInterface.hpp"
#include "LocalImpl.hpp"

using Interface = YAPM::Service::PowerMetricsInterface;

typedef Interface* CreateInterfaceFunc();

Interface* CreateLocalInterface(){
//    std::cout << "[          ] Testing CSV Implementation\n";
    return new YAPM::Service::Implementation::LocalMetricsImplementation();
}

//Interface* CreateDumm/yInterface(){
//    std::cout << "[          ] Testing Dummy Implementation\n";
//    return new YAPM::Service::Implementation::DummyPowerServiceImpl();
//}

class InterfaceTest : public ::testing::TestWithParam<CreateInterfaceFunc*>
{
public:
    InterfaceTest() {m_interface.reset((*GetParam())());}
    virtual ~InterfaceTest() {
    }


protected:
    std::unique_ptr<Interface> m_interface;
};
