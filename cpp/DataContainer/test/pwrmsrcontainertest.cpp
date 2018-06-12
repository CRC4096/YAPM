#include "pwrmsrcontainertest.h"

#include <limits>

using namespace DataContainer;


TEST(PowerMeasurementContainerTest, TestConstexpr){
    PowerMeasurement<kWh> PM(5);
    //This is the real test. If this compiles PowerMeasurement is constexpr
    double test[static_cast<int>(PM.getValue<kWh>())];
    test[2] = PM.getValue<kWh>();

    ASSERT_EQ(test[2], PM.getValue<kWh>());
}

/*
 *  Constructor and assignment tests
 */

TEST(PowerMeasurementContainerTest, TestEmptyConstructor) {
    static_assert(std::is_move_assignable<PowerMeasurement<kWh>>::value && std::is_move_constructible<PowerMeasurement<kWh>>::value, "PowerMeasurement should be move constructible and assignable");
    static_assert(std::is_nothrow_copy_constructible<PowerMeasurement<kWh>>::value && std::is_nothrow_copy_assignable<PowerMeasurement<kWh>>::value, "PowerMeasurement should be nothrow copy constructible and assignable");

    PowerMeasurement<kWh> PM;
    ASSERT_EQ(PM.getValue<kWh>(), 0);
}

TEST(PowerMeasurementContainerTest, TestIntegralConstructor) {
    long long longlong = 100;
    int i = 99;
    short s = 98;
    char c = 97;
    kWh unit;

    PowerMeasurement<decltype(unit)> longlongPM(longlong);
    PowerMeasurement<decltype(unit)> iPM(i);
    PowerMeasurement<decltype(unit)> sPM(s);
    PowerMeasurement<decltype(unit)> cPM(c);

    ASSERT_EQ(longlongPM.getValue<decltype(unit)>(), longlong);
    ASSERT_EQ(iPM.getValue<decltype(unit)>(), i);
    ASSERT_EQ(sPM.getValue<decltype(unit)>(), s);
    ASSERT_EQ(cPM.getValue<decltype(unit)>(), c);
}

TEST(PowerMeasurementContainerTest, TestFloatingPointConstrutor) {
    double d = 15.12345;
    float f = 16.54321;
    kWh unit;

    PowerMeasurement<decltype(unit)> dPM(d);
    PowerMeasurement<decltype(unit)> fPM(f);

    ASSERT_EQ(dPM.getValue<decltype(unit)>(), d);
    ASSERT_EQ(fPM.getValue<decltype(unit)>(), f);
}

TEST(PowerMeasurementContainerTest, TestMoveAndCopyConstructor) {
    double value = 100.0;
    kWh unit;
    PowerMeasurement<decltype(unit)> PM(value);

    PowerMeasurement<decltype(unit)> copied(PM);
    ASSERT_EQ(copied.getValue<decltype(unit)>(), value);

    PowerMeasurement moved(std::move(PM));
    ASSERT_EQ(moved.getValue<decltype(unit)>(), value);
}

TEST(PowerMeasurementContainerTest, TestAssignmentOperator) {
    double value = 100.0;
    kWh unit;
    PowerMeasurement<decltype(unit)> PM(value);

    auto copiedAs = (PM);
    ASSERT_EQ(copiedAs.getValue<decltype(unit)>(), value);

    auto movedAs = (std::move(PM));
    ASSERT_EQ(movedAs.getValue<decltype(unit)>(), value);
}
/*
 * Getter and setter tests
 */

TEST(PowerMeasurementContainerTest, TestGetter){
    double value = 1000;

    PowerMeasurement<kWh> PM_kWh(value);
    ASSERT_EQ(PM_kWh.getValue<kWh>(), value);
    ASSERT_EQ(PM_kWh.getValue<Wh>(), 1000000);

    PowerMeasurement<Wh> PM_Wh(value);
    ASSERT_EQ(PM_Wh.getValue<kWh>(), 1);
    ASSERT_EQ(PM_Wh.getValue<Wh>(), value);
}

TEST(PowerMeasurementContainerTest, TestSetter){
    double value = 1000;

    PowerMeasurement<> PM_kWh;
    ASSERT_NE(PM_kWh.getValue<kWh>(), value);
    PM_kWh.setValue<kWh>(value);
    ASSERT_EQ(PM_kWh.getValue<kWh>(), value);
    ASSERT_EQ(PM_kWh.getValue<Wh>(), 1000000);

    PowerMeasurement<> PM_Wh;
    ASSERT_NE(PM_Wh.getValue<Wh>(), value);
    PM_Wh.setValue<Wh>(value);
    ASSERT_EQ(PM_Wh.getValue<Wh>(), value);
    ASSERT_EQ(PM_Wh.getValue<kWh>(), 1);
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
    PowerMeasurement<kWh> bigger(1000);
    PowerMeasurement<Wh> smaller(1000);
    PowerMeasurement<Wh> equal(1000000);

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
    PowerMeasurement<kWh> bigger(1000);
    PowerMeasurement<Wh> smaller(1000);
    PowerMeasurement<Wh> equal(1000000);

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
    PowerMeasurement<kWh> bigger(1000);
    PowerMeasurement<Wh> smaller(1000);
    PowerMeasurement<kWh> equal(1);

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
    PowerMeasurement<kWh> bigger(1000);
    PowerMeasurement<Wh> smaller(1000);
    PowerMeasurement<kWh> equal(1);

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
    PowerMeasurement<kWh> base(1);
    PowerMeasurement<Wh> equal(1000);
    PowerMeasurement<Wh> unequal(1);

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
    PowerMeasurement<kWh> base(1);
    PowerMeasurement<Wh> equal(1000);
    PowerMeasurement<Wh> unequal(1);

    ASSERT_NE(base, unequal);
    ASSERT_FALSE(base != equal);

}
/*
 *  Arithmetic operator test
 */

TEST(PowerMeasurementContainerTest, TestPlusOperator) {
    PowerMeasurement<kWh> a(10);
    PowerMeasurement<Wh> b(5000);

    ASSERT_EQ(a+a, PowerMeasurement<kWh>(20));
    ASSERT_EQ(a+a, PowerMeasurement<Wh>(20000));
    ASSERT_EQ(b+b, PowerMeasurement<kWh>(10));
    ASSERT_EQ(b+b, PowerMeasurement<Wh>(10000));
    ASSERT_EQ(a+b, PowerMeasurement<kWh>(15));
    ASSERT_EQ(a+b, PowerMeasurement<Wh>(15000));
    ASSERT_EQ(b+a, PowerMeasurement<kWh>(15));
    ASSERT_EQ(b+a, PowerMeasurement<Wh>(15000));
}

TEST(PowerMeasurementContainerTest, TestMinusOperator) {
    PowerMeasurement<kWh> a(10);
    PowerMeasurement<Wh> b(5000);

    ASSERT_EQ(a-a, PowerMeasurement<kWh>(0));
    ASSERT_EQ(a-a, PowerMeasurement<Wh>(0));
    ASSERT_EQ(b-b, PowerMeasurement<kWh>(0));
    ASSERT_EQ(b-b, PowerMeasurement<Wh>(0));
    ASSERT_EQ(a-b, PowerMeasurement<kWh>(5));
    ASSERT_EQ(a-b, PowerMeasurement<Wh>(5000));
    ASSERT_EQ(b-a, PowerMeasurement<kWh>(-5));
    ASSERT_EQ(b-a, PowerMeasurement<Wh>(-5000));

}

TEST(PowerMeasurementContainerTest, TestIntegralMultiplication) {
    PowerMeasurement<kWh> PM_kWH(10);
    PowerMeasurement<Wh> PM_WH(20000);

    ASSERT_EQ(PM_kWH*2, PowerMeasurement<kWh>(20));
    ASSERT_EQ(PM_kWH*2, PowerMeasurement<Wh>(20000));
    ASSERT_EQ(PM_WH*2, PowerMeasurement<kWh>(40));
    ASSERT_EQ(PM_WH*2, PowerMeasurement<Wh>(40000));

    ASSERT_EQ(PM_kWH*0, PowerMeasurement<kWh>(0));
    ASSERT_EQ(PM_kWH*0, PowerMeasurement<Wh>(0));
    ASSERT_EQ(PM_WH*0, PowerMeasurement<kWh>(0));
    ASSERT_EQ(PM_WH*0, PowerMeasurement<Wh>(0));

    ASSERT_EQ(PM_kWH*-2, PowerMeasurement<kWh>(-20));
    ASSERT_EQ(PM_kWH*-2, PowerMeasurement<Wh>(-20000));
    ASSERT_EQ(PM_WH*-2, PowerMeasurement<kWh>(-40));
    ASSERT_EQ(PM_WH*-2, PowerMeasurement<Wh>(-40000));
}

TEST(PowerMeasurementContainerTest, TestFloatingPointMultiplication) {
    PowerMeasurement<kWh> PM_kWH(10);
    PowerMeasurement<Wh> PM_WH(20000);

    ASSERT_EQ(PM_kWH*0.5, PowerMeasurement<kWh>(5));
    ASSERT_EQ(PM_kWH*0.5, PowerMeasurement<Wh>(5000));
    ASSERT_EQ(PM_WH*0.5, PowerMeasurement<kWh>(10));
    ASSERT_EQ(PM_WH*0.5, PowerMeasurement<Wh>(10000));

    ASSERT_EQ(PM_kWH*0.0, PowerMeasurement<kWh>(0));
    ASSERT_EQ(PM_kWH*0.0, PowerMeasurement<Wh>(0));
    ASSERT_EQ(PM_WH*0.0, PowerMeasurement<kWh>(0));
    ASSERT_EQ(PM_WH*0.0, PowerMeasurement<Wh>(0));

    ASSERT_EQ(PM_kWH*-0.5, PowerMeasurement<kWh>(-5));
    ASSERT_EQ(PM_kWH*-0.5, PowerMeasurement<Wh>(-5000));
    ASSERT_EQ(PM_WH*-0.5, PowerMeasurement<kWh>(-10));
    ASSERT_EQ(PM_WH*-0.5, PowerMeasurement<Wh>(-10000));

}

TEST(PowerMeasurementContainerTest, TestIntegralDivison) {
    PowerMeasurement<kWh> PM_kWH(10);
    PowerMeasurement<Wh> PM_WH(20000);

    ASSERT_EQ(PM_kWH/5, PowerMeasurement<kWh>(2));
    ASSERT_EQ(PM_kWH/5, PowerMeasurement<Wh>(2000));
    ASSERT_EQ(PM_WH/5, PowerMeasurement<kWh>(4));
    ASSERT_EQ(PM_WH/5, PowerMeasurement<Wh>(4000));

    ASSERT_EQ(PM_kWH/1, PM_kWH);
    ASSERT_EQ(PM_kWH/1, PM_kWH);
    ASSERT_EQ(PM_WH/1, PM_WH);
    ASSERT_EQ(PM_WH/1, PM_WH);

    ASSERT_EQ(PM_kWH/-5, PowerMeasurement<kWh>(-2));
    ASSERT_EQ(PM_kWH/-5, PowerMeasurement<Wh>(-2000));
    ASSERT_EQ(PM_WH/-5, PowerMeasurement<kWh>(-4));
    ASSERT_EQ(PM_WH/-5, PowerMeasurement<Wh>(-4000));
}

TEST(PowerMeasurementContainerTest, TestFloatingPointDivison) {
    PowerMeasurement<kWh> PM_kWH(15);
    PowerMeasurement<Wh> PM_WH(30000);

    ASSERT_EQ(PM_kWH/1.5, PowerMeasurement<kWh>(10));
    ASSERT_EQ(PM_kWH/1.5, PowerMeasurement<Wh>(10000));
    ASSERT_EQ(PM_WH/1.5, PowerMeasurement<kWh>(20));
    ASSERT_EQ(PM_WH/1.5, PowerMeasurement<Wh>(20000));

    ASSERT_EQ(PM_kWH/1.0, PM_kWH);
    ASSERT_EQ(PM_kWH/1.0, PM_kWH);
    ASSERT_EQ(PM_WH/1.0, PM_WH);
    ASSERT_EQ(PM_WH/1.0, PM_WH);

    ASSERT_EQ(PM_kWH/-0.5, PowerMeasurement<kWh>(-30));
    ASSERT_EQ(PM_kWH/-0.5, PowerMeasurement<Wh>(-30000));
    ASSERT_EQ(PM_WH/-0.5, PowerMeasurement<kWh>(-60));
    ASSERT_EQ(PM_WH/-0.5, PowerMeasurement<Wh>(-60000));
}

/*
 *  Details test
 */

TEST(PowerMeasurementContainerTest, TestNormalizationTokWh){
    ASSERT_EQ(Details::normalizeTokWh<kWh>(1000.0), 1000.0);
    ASSERT_EQ(Details::normalizeTokWh<Wh>(1000.0), 1.0);
}


TEST(PowerMeasurementContainerTest, TestExtendFromkWh){
    ASSERT_EQ(Details::extendFromkWh<kWh>(1000.0), 1000.0);
    ASSERT_EQ(Details::extendFromkWh<Wh>(1.0), 1000.0);
}

