#include "csvinterfacetest.hpp"

namespace {
constexpr int NUMER_OF_ITEMS = 5;
}


TEST_F(CsvInterfaceTest, TestLoadingAndSaving){

    const auto data = getData();
    {
        CsvInterface interface = getInterface();
        interface.addMultipleDataPoints(data);
    }
    {
        CsvInterface interface = getInterface();
        ASSERT_EQ(interface.countDataPoints(), data.size());
        for(const auto& measurement : data){
            ASSERT_TRUE(interface.containsDataPoint(measurement));
        }
    }

}
CsvInterface getInterface()
{
    CsvInterface retVal;
    return retVal;
}

std::vector<PowerContainer> getData()
{
    std::vector<PowerContainer> retVal;
    for(auto i = 0; i < NUMER_OF_ITEMS; ++i){
        retVal.push_back(PowerContainer(i*10, i*10));
    }
    return retVal;
}
