#include "pwrmsrcontainertest.h"

using namespace DataContainer;

TEST(PowerMeasurementContainerTest, TestEmptyConstructor) {
    PowerMeasurement PM;
    ASSERT_EQ(PM.getValue(MeasurementUnit::kWh), 0);
}

TEST(PowerMeasurementContainerTest, TestIntegralConstructor) {
    long long longlong = 100;
    int i = 99;
    short s = 98;
    char c = 97;
    MeasurementUnit unit = MeasurementUnit::kWh;
    PowerMeasurement longlongPM(longlong, unit);
    PowerMeasurement iPM(i, unit);
    PowerMeasurement sPM(s, unit);
    PowerMeasurement cPM(c, unit);

    ASSERT_EQ(longlongPM.getValue(unit), longlong);
    ASSERT_EQ(iPM.getValue(unit), i);
    ASSERT_EQ(sPM.getValue(unit), s);
    ASSERT_EQ(cPM.getValue(unit), c);
}

TEST(PowerMeasurementContainerTest, TestFloatingPointConstrutor) {
    double d = 15.12345;
    float f = 16.54321;
    MeasurementUnit unit = MeasurementUnit::kWh;
    PowerMeasurement dPM(d, unit);
    PowerMeasurement fPM(f, unit);

    ASSERT_EQ(dPM.getValue(unit), d);
    ASSERT_EQ(fPM.getValue(unit), f);
}

TEST(PowerMeasurementContainerTest, TestMoveAndCopyConstructor) {

}

TEST(PowerMeasurementContainerTest, TestAssignmentOperator) {

}
