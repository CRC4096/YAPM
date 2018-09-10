#include "interfacetest.h"

using PowerContainer = DataContainer::Power::PowerMeasurement<DataContainer::Power::kWh>;

namespace {
    constexpr int NUMBER_OF_ITEMS = 50;
}

TEST_P(InterfaceTest, TestAddDatapoint){
    Interface* interface = m_interface.get();

    std::vector<PowerContainer> measurements;
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        PowerContainer temp(i*100, i);;
        interface->addDataPoint(temp);
        measurements.push_back(std::move(temp));
    }

    auto retVal = interface->getAllDataPoints();

    ASSERT_EQ(measurements.size(), retVal.size());
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        //the container should keep its order since the ordering is based on the timestamp
        ASSERT_EQ(measurements.at(i), retVal.at(i));
    }
}


TEST_P(InterfaceTest, TestAddMultipleDataPoints){
    Interface* interface = m_interface.get();

    std::vector<PowerContainer> measurements;
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        measurements.push_back(PowerContainer(i*100, i));
    }

    ASSERT_EQ(measurements.size(), NUMBER_OF_ITEMS);

    interface->addMultipleDataPoints(measurements);
    auto retVal = interface->getAllDataPoints();

    ASSERT_EQ(measurements.size(), retVal.size());
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        //the container should keep its order since the ordering is based on the timestamp
        ASSERT_EQ(measurements.at(i), retVal.at(i));
    }
}

TEST_P(InterfaceTest, TestAddEmptyVector){
    Interface* interface = m_interface.get();
    std::vector<PowerContainer> emptyVector;

    interface->addMultipleDataPoints(emptyVector);
    ASSERT_EQ(interface->countDataPoints(), 0);

    std::vector<PowerContainer> measurements;
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        measurements.push_back(PowerContainer(i*100, i));
    }

    interface->addMultipleDataPoints(measurements);
    ASSERT_EQ(interface->countDataPoints(), NUMBER_OF_ITEMS);

    interface->addMultipleDataPoints(emptyVector);
    ASSERT_EQ(interface->countDataPoints(), NUMBER_OF_ITEMS);
}

TEST_P(InterfaceTest, TestContainsDataPoint) {
    Interface* interface = m_interface.get();

    std::vector<PowerContainer> measurements;
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        measurements.push_back(PowerContainer(i*100, i));
    }

    ASSERT_EQ(measurements.size(), NUMBER_OF_ITEMS);

    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        ASSERT_FALSE(interface->containsDataPoint(measurements.at(i)));
        interface->addDataPoint(measurements.at(i));
        ASSERT_TRUE(interface->containsDataPoint(measurements.at(i)));
    }
}


TEST_P(InterfaceTest, TestCountDataPoint) {
    Interface* interface = m_interface.get();

    std::vector<PowerContainer> measurements;
    measurements.push_back(PowerContainer(5, 5));
    measurements.push_back(PowerContainer(5, 10));
    measurements.push_back(PowerContainer(5, 15));
    measurements.push_back(PowerContainer(5, 20));
    measurements.push_back(PowerContainer(5, 25));

    interface->addMultipleDataPoints(measurements);

    ASSERT_EQ(interface->countDataPoints(-5,  0), 0);
    ASSERT_EQ(interface->countDataPoints(15, -5), 0);
    ASSERT_EQ(interface->countDataPoints( 0,  0), 0);
    ASSERT_EQ(interface->countDataPoints( 5,  0), 0);
    ASSERT_EQ(interface->countDataPoints(30,  0), 0);
    ASSERT_EQ(interface->countDataPoints( 0,  5), 1);
    ASSERT_EQ(interface->countDataPoints( 5,  5), 1);
    ASSERT_EQ(interface->countDataPoints( 0, 10), 2);
    ASSERT_EQ(interface->countDataPoints(10, 15), 2);
    ASSERT_EQ(interface->countDataPoints(20, 30), 2);
    ASSERT_EQ(interface->countDataPoints( 0, 15), 3);
    ASSERT_EQ(interface->countDataPoints( 0, 20), 4);
    ASSERT_EQ(interface->countDataPoints( 0, 25), 5);
    ASSERT_EQ(interface->countDataPoints( 0, 30), 5);
}

TEST_P(InterfaceTest, TestRemoveDataPoint) {
    Interface* interface = m_interface.get();

    std::vector<PowerContainer> measurements;
    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        measurements.push_back(PowerContainer(i*100, i));
    }

    interface->addMultipleDataPoints(measurements);

    for(auto i = 0; i < NUMBER_OF_ITEMS; ++i){
        ASSERT_TRUE(interface->containsDataPoint(measurements.at(i)));
        ASSERT_EQ(interface->countDataPoints(), (NUMBER_OF_ITEMS - i));
        ASSERT_TRUE(interface->removeDataPoint(measurements.at(i)));
        ASSERT_FALSE(interface->containsDataPoint(measurements.at(i)));
        ASSERT_EQ(interface->countDataPoints(), (NUMBER_OF_ITEMS - i - 1));
        ASSERT_FALSE(interface->removeDataPoint(measurements.at(i)));
    }
}

INSTANTIATE_TEST_CASE_P(PowerMeasurementInterfaces, InterfaceTest,
                        ::testing::Values(&CreateDummyInterface,
                                          &CreateCsvInterface
                                          ));

