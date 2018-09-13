#include "interfacetest.h"

using PowerContainer = DataContainer::Power::PowerMeasurement<DataContainer::Power::kWh>;

namespace {
    constexpr long UNIX_MINUTE = 60;
    constexpr long UNIX_HOUR = UNIX_MINUTE * 60;
    constexpr long UNIX_DAY = UNIX_HOUR * 24;
    constexpr long UNIX_WEEK = UNIX_DAY * 7;
    constexpr long UNIX_MONTH = UNIX_WEEK * 4;
    constexpr long UNIX_YEAR = UNIX_MONTH * 12;
}

TEST_P(InterfaceTest, TestGetAverage){
    Interface* interface = m_interface.get();
    /*
     * in this szenario we have a steady consumption of 2 kWh per Minute, therefore
     * Minute = 2
     * Hour = 120
     * Day = 2880
     * Week = 20160
     * Month = 80640
     * Year = 967680
     */

    constexpr size_t NUMBER_OF_ITEMS = 200;

    std::vector<PowerContainer> measurements;
    //Every 12 hours we add 1440 kWh;
    for(size_t i = 0; i < NUMBER_OF_ITEMS; ++i){
        PowerContainer temp(static_cast<long>(i*1440), static_cast<long>(i * UNIX_HOUR * 12));
        measurements.push_back(std::move(temp));
    }

    auto minuteAverage = interface->getAverageConsumption(measurements, UNIX_MINUTE);
    auto hourAverage = interface->getAverageConsumption(measurements, UNIX_HOUR);
    auto dayAverage = interface->getAverageConsumption(measurements, UNIX_DAY);
    auto weekAverage = interface->getAverageConsumption(measurements, UNIX_WEEK);
    auto monthAverage = interface->getAverageConsumption(measurements, UNIX_MONTH);
    auto yearAverage = interface->getAverageConsumption(measurements, UNIX_YEAR);

    ASSERT_EQ(minuteAverage.getValue(), 2.0);
    ASSERT_EQ(hourAverage.getValue(), 120.0);
    ASSERT_EQ(dayAverage.getValue(), 2880.0);
    ASSERT_EQ(weekAverage.getValue(), 20160.0);
    ASSERT_EQ(monthAverage.getValue(), 80640.0);
    ASSERT_EQ(yearAverage.getValue(), 967680.0);
}


TEST_P(InterfaceTest, TestGetAverage_Custom){
    Interface* interface  = m_interface.get();
    std::vector<PowerContainer> measurements;

    measurements.emplace_back(0, 0);
    measurements.emplace_back(40, 1 * UNIX_HOUR);
    measurements.emplace_back(80, 3 * UNIX_HOUR);
    measurements.emplace_back(100, 4 * UNIX_HOUR);
    measurements.emplace_back(100, 8 * UNIX_HOUR);
    measurements.emplace_back(200, 10 * UNIX_HOUR);

    ASSERT_EQ(interface->getAverageConsumption(measurements, UNIX_HOUR).getValue(), 20);
}


TEST_P(InterfaceTest, TestForcast){
    Interface* interface = m_interface.get();
    std::vector<PowerContainer> measurements;

    for(size_t i = 0; i < 11; i++){
        measurements.emplace_back(i*100, i*UNIX_MONTH);
    }

    auto forecast = interface->getForecast(measurements, 12*UNIX_MONTH);
    ASSERT_EQ(forecast.getValue(), 1200);
}


TEST_P(InterfaceTest, TestForcast_Custom){
    Interface* interface = m_interface.get();
    std::vector<PowerContainer> measurements;

    measurements.emplace_back(0, 0);
    measurements.emplace_back(40, 1 * UNIX_HOUR);
    measurements.emplace_back(80, 3 * UNIX_HOUR);
    measurements.emplace_back(100, 4 * UNIX_HOUR);
    measurements.emplace_back(100, 8 * UNIX_HOUR);
    measurements.emplace_back(200, 10 * UNIX_HOUR);

    ASSERT_EQ(interface->getForecast(measurements, 20 * UNIX_HOUR).getValue(), 400);
    ASSERT_EQ(interface->getForecast(measurements, 24 * UNIX_HOUR).getValue(), 480);
    ASSERT_EQ(interface->getForecast(measurements, 30 * UNIX_HOUR).getValue(), 600);
}

INSTANTIATE_TEST_CASE_P(PowerMeasurementInterfaces, InterfaceTest,
                        ::testing::Values(&CreateLocalInterface
//                                          &CreateCsvInterface
                                          ));
