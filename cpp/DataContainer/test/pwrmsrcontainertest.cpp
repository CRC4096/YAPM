#include "pwrmsrcontainertest.h"

#include <limits>

using namespace DataContainer;


TEST(PowerMeasurementContainerTest, TestConstexpr){
    PowerMeasurement PM(5, PowerUnit::kWh);
    //This is the real test. If this compiles PowerMeasurement is constexpr
    double test[static_cast<int>(PM.getValue(PowerUnit::kWh))];
    test[2] = PM.getValue(PowerUnit::Wh);

    ASSERT_EQ(test[2], PM.getValue(PowerUnit::Wh));
}

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
    PowerMeasurement a(10, PowerUnit::kWh);
    PowerMeasurement b(5000, PowerUnit::Wh);

    ASSERT_EQ(a+a, PowerMeasurement(20, PowerUnit::kWh));
    ASSERT_EQ(a+a, PowerMeasurement(20000, PowerUnit::Wh));
    ASSERT_EQ(b+b, PowerMeasurement(10, PowerUnit::kWh));
    ASSERT_EQ(b+b, PowerMeasurement(10000, PowerUnit::Wh));
    ASSERT_EQ(a+b, PowerMeasurement(15, PowerUnit::kWh));
    ASSERT_EQ(a+b, PowerMeasurement(15000, PowerUnit::Wh));
    ASSERT_EQ(b+a, PowerMeasurement(15, PowerUnit::kWh));
    ASSERT_EQ(b+a, PowerMeasurement(15000, PowerUnit::Wh));
}

TEST(PowerMeasurementContainerTest, TestMinusOperator) {
    PowerMeasurement a(10, PowerUnit::kWh);
    PowerMeasurement b(5000, PowerUnit::Wh);

    ASSERT_EQ(a-a, PowerMeasurement(0, PowerUnit::kWh));
    ASSERT_EQ(a-a, PowerMeasurement(0, PowerUnit::Wh));
    ASSERT_EQ(b-b, PowerMeasurement(0, PowerUnit::kWh));
    ASSERT_EQ(b-b, PowerMeasurement(0, PowerUnit::Wh));
    ASSERT_EQ(a-b, PowerMeasurement(5, PowerUnit::kWh));
    ASSERT_EQ(a-b, PowerMeasurement(5000, PowerUnit::Wh));
    ASSERT_EQ(b-a, PowerMeasurement(-5, PowerUnit::kWh));
    ASSERT_EQ(b-a, PowerMeasurement(-5000, PowerUnit::Wh));

}

TEST(PowerMeasurementContainerTest, TestIntegralMultiplication) {
    PowerMeasurement PM_kWH(10, PowerUnit::kWh);
    PowerMeasurement PM_WH(20000, PowerUnit::Wh);

    ASSERT_EQ(PM_kWH*2, PowerMeasurement(20, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH*2, PowerMeasurement(20000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH*2, PowerMeasurement(40, PowerUnit::kWh));
    ASSERT_EQ(PM_WH*2, PowerMeasurement(40000, PowerUnit::Wh));

    ASSERT_EQ(PM_kWH*0, PowerMeasurement(0, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH*0, PowerMeasurement(0, PowerUnit::Wh));
    ASSERT_EQ(PM_WH*0, PowerMeasurement(0, PowerUnit::kWh));
    ASSERT_EQ(PM_WH*0, PowerMeasurement(0, PowerUnit::Wh));

    ASSERT_EQ(PM_kWH*-2, PowerMeasurement(-20, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH*-2, PowerMeasurement(-20000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH*-2, PowerMeasurement(-40, PowerUnit::kWh));
    ASSERT_EQ(PM_WH*-2, PowerMeasurement(-40000, PowerUnit::Wh));
}

TEST(PowerMeasurementContainerTest, TestFloatingPointMultiplication) {
    PowerMeasurement PM_kWH(10, PowerUnit::kWh);
    PowerMeasurement PM_WH(20000, PowerUnit::Wh);

    ASSERT_EQ(PM_kWH*0.5, PowerMeasurement(5, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH*0.5, PowerMeasurement(5000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH*0.5, PowerMeasurement(10, PowerUnit::kWh));
    ASSERT_EQ(PM_WH*0.5, PowerMeasurement(10000, PowerUnit::Wh));

    ASSERT_EQ(PM_kWH*0.0, PowerMeasurement(0, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH*0.0, PowerMeasurement(0, PowerUnit::Wh));
    ASSERT_EQ(PM_WH*0.0, PowerMeasurement(0, PowerUnit::kWh));
    ASSERT_EQ(PM_WH*0.0, PowerMeasurement(0, PowerUnit::Wh));

    ASSERT_EQ(PM_kWH*-0.5, PowerMeasurement(-5, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH*-0.5, PowerMeasurement(-5000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH*-0.5, PowerMeasurement(-10, PowerUnit::kWh));
    ASSERT_EQ(PM_WH*-0.5, PowerMeasurement(-10000, PowerUnit::Wh));

}

TEST(PowerMeasurementContainerTest, TestIntegralDivison) {
    PowerMeasurement PM_kWH(10, PowerUnit::kWh);
    PowerMeasurement PM_WH(20000, PowerUnit::Wh);

    ASSERT_EQ(PM_kWH/5, PowerMeasurement(2, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH/5, PowerMeasurement(2000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH/5, PowerMeasurement(4, PowerUnit::kWh));
    ASSERT_EQ(PM_WH/5, PowerMeasurement(4000, PowerUnit::Wh));

    ASSERT_EQ(PM_kWH/1, PM_kWH);
    ASSERT_EQ(PM_kWH/1, PM_kWH);
    ASSERT_EQ(PM_WH/1, PM_WH);
    ASSERT_EQ(PM_WH/1, PM_WH);

    ASSERT_EQ(PM_kWH/-5, PowerMeasurement(-2, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH/-5, PowerMeasurement(-2000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH/-5, PowerMeasurement(-4, PowerUnit::kWh));
    ASSERT_EQ(PM_WH/-5, PowerMeasurement(-4000, PowerUnit::Wh));
}

TEST(PowerMeasurementContainerTest, TestFloatingPointDivison) {
    PowerMeasurement PM_kWH(15, PowerUnit::kWh);
    PowerMeasurement PM_WH(30000, PowerUnit::Wh);

    ASSERT_EQ(PM_kWH/1.5, PowerMeasurement(10, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH/1.5, PowerMeasurement(10000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH/1.5, PowerMeasurement(20, PowerUnit::kWh));
    ASSERT_EQ(PM_WH/1.5, PowerMeasurement(20000, PowerUnit::Wh));

    ASSERT_EQ(PM_kWH/1.0, PM_kWH);
    ASSERT_EQ(PM_kWH/1.0, PM_kWH);
    ASSERT_EQ(PM_WH/1.0, PM_WH);
    ASSERT_EQ(PM_WH/1.0, PM_WH);

    ASSERT_EQ(PM_kWH/-0.5, PowerMeasurement(-30, PowerUnit::kWh));
    ASSERT_EQ(PM_kWH/-0.5, PowerMeasurement(-30000, PowerUnit::Wh));
    ASSERT_EQ(PM_WH/-0.5, PowerMeasurement(-60, PowerUnit::kWh));
    ASSERT_EQ(PM_WH/-0.5, PowerMeasurement(-60000, PowerUnit::Wh));
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

