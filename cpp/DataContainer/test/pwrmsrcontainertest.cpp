#include "pwrmsrcontainertest.h"

#include <limits>

using namespace DataContainer;

/*
 *  Constructor and assignment tests
 */

TEST(PowerMeasurementContainerTest, TestEmptyConstructor) {
    static_assert(std::is_move_assignable<PowerMeasurement>::value && std::is_move_constructible<PowerMeasurement>::value, "PowerMeasurement should be move constructible and assignable");
    static_assert(std::is_nothrow_copy_constructible<PowerMeasurement>::value && std::is_nothrow_copy_assignable<PowerMeasurement>::value, "PowerMeasurement should be nothrow copy constructible and assignable");

    PowerMeasurement PM;
    ASSERT_EQ(PM.getValue(PowerUnit::kWh), 0);
}

TEST(PowerMeasurementContainerTest, TestIntegralConstructor) {
    long long longlong = 100;
    int i = 99;
    short s = 98;
    char c = 97;
    PowerUnit unit = PowerUnit::kWh;

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
    PowerUnit unit = PowerUnit::kWh;

    PowerMeasurement dPM(d, unit);
    PowerMeasurement fPM(f, unit);

    ASSERT_EQ(dPM.getValue(unit), d);
    ASSERT_EQ(fPM.getValue(unit), f);
}

TEST(PowerMeasurementContainerTest, TestMoveAndCopyConstructor) {
    double value = 100.0;
    PowerUnit unit = PowerUnit::kWh;
    PowerMeasurement PM(value, unit);

    PowerMeasurement copied(PM);
    ASSERT_EQ(copied.getValue(unit), value);

    PowerMeasurement moved(std::move(PM));
    ASSERT_EQ(moved.getValue(unit), value);
}

TEST(PowerMeasurementContainerTest, TestAssignmentOperator) {
    double value = 100.0;
    PowerUnit unit = PowerUnit::kWh;
    PowerMeasurement PM(value, unit);

    PowerMeasurement copiedAs = (PM);
    ASSERT_EQ(copiedAs.getValue(unit), value);

    PowerMeasurement movedAs = (std::move(PM));
    ASSERT_EQ(movedAs.getValue(unit), value);
}
/*
 * Getter and setter tests
 */

TEST(PowerMeasurementContainerTest, TestGetter){
    double value = 1000;

    PowerMeasurement PM_kWh(value, PowerUnit::kWh);
    ASSERT_EQ(PM_kWh.getValue(PowerUnit::kWh), value);
    ASSERT_EQ(PM_kWh.getValue(PowerUnit::Wh), 1000000);

    PowerMeasurement PM_Wh(value, PowerUnit::Wh);
    ASSERT_EQ(PM_Wh.getValue(PowerUnit::kWh), 1);
    ASSERT_EQ(PM_Wh.getValue(PowerUnit::Wh), value);
}

TEST(PowerMeasurementContainerTest, TestSetter){
    double value = 1000;

    PowerMeasurement PM_kWh;
    ASSERT_NE(PM_kWh.getValue(PowerUnit::kWh), value);
    PM_kWh.setValue(value, PowerUnit::kWh);
    ASSERT_EQ(PM_kWh.getValue(PowerUnit::kWh), value);
    ASSERT_EQ(PM_kWh.getValue(PowerUnit::Wh), 1000000);

    PowerMeasurement PM_Wh;
    ASSERT_NE(PM_Wh.getValue(PowerUnit::Wh), value);
    PM_Wh.setValue(value, PowerUnit::Wh);
    ASSERT_EQ(PM_Wh.getValue(PowerUnit::Wh), value);
    ASSERT_EQ(PM_Wh.getValue(PowerUnit::kWh), 1);
}


/*
 *  boolean opeartor tests
 */

TEST(PowerMeasurementContainerTest, TestBiggerThan) {
    PowerMeasurement bigger(100);
    PowerMeasurement smaller(10);
    PowerMeasurement equal(100);

    ASSERT_GT(bigger, smaller);
    ASSERT_FALSE(smaller > bigger);
    ASSERT_FALSE(bigger > equal);
}

TEST(PowerMeasurementContainerTest, TestBiggerThan_DifferenUnits) {
    PowerMeasurement bigger(1000, PowerUnit::kWh);
    PowerMeasurement smaller(1000, PowerUnit::Wh);
    PowerMeasurement equal(1000000, PowerUnit::Wh);

    ASSERT_GT(bigger, smaller);
    ASSERT_FALSE(smaller > bigger);
    ASSERT_FALSE(bigger > equal);
}

TEST(PowerMeasurementContainerTest, TestBiggerEqualsThan) {
    PowerMeasurement bigger(100);
    PowerMeasurement smaller(10);
    PowerMeasurement equal(100);

    ASSERT_GE(bigger, smaller);
    ASSERT_GE(bigger, equal);
    ASSERT_FALSE(smaller > bigger);
}

TEST(PowerMeasurementContainerTest, TestBiggerEqualsThan_DifferenUnits) {
    PowerMeasurement bigger(1000, PowerUnit::kWh);
    PowerMeasurement smaller(1000, PowerUnit::Wh);
    PowerMeasurement equal(1000000, PowerUnit::Wh);

    ASSERT_GE(bigger, smaller);
    ASSERT_GE(bigger, equal);
    ASSERT_FALSE(smaller > bigger);
}

TEST(PowerMeasurementContainerTest, TestSmallerThan) {
    PowerMeasurement bigger(100);
    PowerMeasurement smaller(10);
    PowerMeasurement equal(10);

    ASSERT_LT(smaller, bigger);
    ASSERT_FALSE(bigger < smaller);
    ASSERT_FALSE(smaller < equal);
}

TEST(PowerMeasurementContainerTest, TestSmallerThan_DifferenUnits) {
    PowerMeasurement bigger(1000, PowerUnit::kWh);
    PowerMeasurement smaller(1000, PowerUnit::Wh);
    PowerMeasurement equal(1, PowerUnit::kWh);

    ASSERT_LT(smaller, bigger);
    ASSERT_FALSE(bigger < smaller);
    ASSERT_FALSE(smaller < equal);
}

TEST(PowerMeasurementContainerTest, TestSmallerEqualsThan) {
    PowerMeasurement bigger(100);
    PowerMeasurement smaller(10);
    PowerMeasurement equal(10);

    ASSERT_LE(smaller, bigger);
    ASSERT_LE(smaller, equal);
    ASSERT_FALSE(bigger <= smaller);
}

TEST(PowerMeasurementContainerTest, TestSmallerEqualsThan_DifferenUnits) {
    PowerMeasurement bigger(1000, PowerUnit::kWh);
    PowerMeasurement smaller(1000, PowerUnit::Wh);
    PowerMeasurement equal(1, PowerUnit::kWh);

    ASSERT_LE(smaller, bigger);
    ASSERT_LE(smaller, equal);
    ASSERT_FALSE(bigger <= smaller);
}

TEST(PowerMeasurementContainerTest, TestEqual) {
    PowerMeasurement base(1000);
    PowerMeasurement equal(1000);
    PowerMeasurement unequal(999);

    ASSERT_EQ(base, equal);
    ASSERT_FALSE(base == unequal);
}

TEST(PowerMeasurementContainerTest, TestEqual_DifferenUnits) {
    PowerMeasurement base(1, PowerUnit::kWh);
    PowerMeasurement equal(1000, PowerUnit::Wh);
    PowerMeasurement unequal(1, PowerUnit::Wh);

    ASSERT_EQ(base, equal);
    ASSERT_FALSE(base == unequal);
}

TEST(PowerMeasurementContainerTest, TestUnequal) {
    PowerMeasurement base(1000);
    PowerMeasurement equal(1000);
    PowerMeasurement unequal(999);

    ASSERT_NE(base, unequal);
    ASSERT_FALSE(base != equal);
}

TEST(PowerMeasurementContainerTest, TestUnequal_DifferenUnits) {
    PowerMeasurement base(1, PowerUnit::kWh);
    PowerMeasurement equal(1000, PowerUnit::Wh);
    PowerMeasurement unequal(1, PowerUnit::Wh);

    ASSERT_NE(base, unequal);
    ASSERT_FALSE(base != equal);

}
/*
 *  Arithmetic operator test
 */

TEST(PowerMeasurementContainerTest, TestPlusOperator) {
}

TEST(PowerMeasurementContainerTest, TestMinusOperator) {

}

TEST(PowerMeasurementContainerTest, TestIntegralMultiplication) {

}

TEST(PowerMeasurementContainerTest, TestFloatingPointMultiplicatoin) {

}

TEST(PowerMeasurementContainerTest, TestIntegralDivison) {

}

TEST(PowerMeasurementContainerTest, TestFloatingPointDivison) {

}

/*
 *  Details test
 */

TEST(PowerMeasurementContainerTest, TestNormalizationTokWh){
    ASSERT_EQ(Details::normalizeTokWh(1000.0, PowerUnit::kWh), 1000.0);
    ASSERT_EQ(Details::normalizeTokWh(1000.0, PowerUnit::Wh), 1.0);
}


TEST(PowerMeasurementContainerTest, TestExtendFromkWh){
    ASSERT_EQ(Details::extendFromkWh(1000.0, PowerUnit::kWh), 1000.0);
    ASSERT_EQ(Details::extendFromkWh(1.0, PowerUnit::Wh), 1000.0);
}

