#include "powervaluecontainertest.h"


#include <limits>

using namespace DataContainer::Power;


TEST(PowerValueContainerTest, TestConstexpr){
    PowerValue<kWh> PM(5);
    //This is the real test. If this compiles PowerValue is constexpr
    double test[static_cast<int>(PM.getValue<kWh>())];
    test[2] = PM.getValue<kWh>();

    ASSERT_EQ(test[2], PM.getValue<kWh>());
}

/*
 *  Constructor and assignment tests
 */

TEST(PowerValueContainerTest, TestEmptyConstructor) {
    static_assert(std::is_move_assignable<PowerValue<kWh>>::value && std::is_move_constructible<PowerValue<kWh>>::value, "PowerValue should be move constructible and assignable");
    static_assert(std::is_nothrow_copy_constructible<PowerValue<kWh>>::value && std::is_nothrow_copy_assignable<PowerValue<kWh>>::value, "PowerValue should be nothrow copy constructible and assignable");

    PowerValue<kWh> PM;
    ASSERT_EQ(PM.getValue<kWh>(), 0);
}

TEST(PowerValueContainerTest, TestIntegralConstructor) {
    long long longlong = 100;
    int i = 99;
    short s = 98;
    char c = 97;
    kWh unit;

    PowerValue<decltype(unit)> longlongPM(longlong);
    PowerValue<decltype(unit)> iPM(i);
    PowerValue<decltype(unit)> sPM(s);
    PowerValue<decltype(unit)> cPM(c);

    ASSERT_EQ(longlongPM.getValue<decltype(unit)>(), longlong);
    ASSERT_EQ(iPM.getValue<decltype(unit)>(), i);
    ASSERT_EQ(sPM.getValue<decltype(unit)>(), s);
    ASSERT_EQ(cPM.getValue<decltype(unit)>(), c);
}

TEST(PowerValueContainerTest, TestFloatingPointConstrutor) {
    double d = 15.12345;
    float f = 16.54321;
    kWh unit;

    PowerValue<decltype(unit)> dPM(d);
    PowerValue<decltype(unit)> fPM(f);

    ASSERT_EQ(dPM.getValue<decltype(unit)>(), d);
    ASSERT_EQ(fPM.getValue<decltype(unit)>(), f);
}

TEST(PowerValueContainerTest, TestMoveAndCopyConstructor) {
    double value = 100.0;
    kWh unit;
    PowerValue<decltype(unit)> PM(value);

    PowerValue<decltype(unit)> copied(PM);
    ASSERT_EQ(copied.getValue<decltype(unit)>(), value);

    PowerValue moved(std::move(PM));
    ASSERT_EQ(moved.getValue<decltype(unit)>(), value);
}

TEST(PowerValueContainerTest, TestAssignmentOperator) {
    double value = 100.0;
    kWh unit;
    PowerValue<decltype(unit)> PM(value);

    auto copiedAs = (PM);
    ASSERT_EQ(copiedAs.getValue<decltype(unit)>(), value);

    auto movedAs = (std::move(PM));
    ASSERT_EQ(movedAs.getValue<decltype(unit)>(), value);
}
/*
 * Getter and setter tests
 */

TEST(PowerValueContainerTest, TestGetter){
    double value = 1000;

    PowerValue<kWh> PM_kWh(value);
    ASSERT_EQ(PM_kWh.getValue<kWh>(), value);
    ASSERT_EQ(PM_kWh.getValue<Wh>(), 1000000);

    PowerValue<Wh> PM_Wh(value);
    ASSERT_EQ(PM_Wh.getValue<kWh>(), 1);
    ASSERT_EQ(PM_Wh.getValue<Wh>(), value);
}

TEST(PowerValueContainerTest, TestSetter){
    double value = 1000;

    PowerValue<> PM_kWh;
    ASSERT_NE(PM_kWh.getValue<kWh>(), value);
    PM_kWh.setValue<kWh>(value);
    ASSERT_EQ(PM_kWh.getValue<kWh>(), value);
    ASSERT_EQ(PM_kWh.getValue<Wh>(), 1000000);

    PowerValue<> PM_Wh;
    ASSERT_NE(PM_Wh.getValue<Wh>(), value);
    PM_Wh.setValue<Wh>(value);
    ASSERT_EQ(PM_Wh.getValue<Wh>(), value);
    ASSERT_EQ(PM_Wh.getValue<kWh>(), 1);
}


/*
 *  boolean opeartor tests
 */

TEST(PowerValueContainerTest, TestBiggerThan) {
    PowerValue bigger(100);
    PowerValue smaller(10);
    PowerValue equal(100);

    ASSERT_GT(bigger, smaller);
    ASSERT_FALSE(smaller > bigger);
    ASSERT_FALSE(bigger > equal);
}

TEST(PowerValueContainerTest, TestBiggerThan_DifferenUnits) {
    PowerValue<kWh> bigger(1000);
    PowerValue<Wh> smaller(1000);
    PowerValue<Wh> equal(1000000);

    ASSERT_GT(bigger, smaller);
    ASSERT_FALSE(smaller > bigger);
    ASSERT_FALSE(bigger > equal);
}

TEST(PowerValueContainerTest, TestBiggerEqualsThan) {
    PowerValue bigger(100);
    PowerValue smaller(10);
    PowerValue equal(100);

    ASSERT_GE(bigger, smaller);
    ASSERT_GE(bigger, equal);
    ASSERT_FALSE(smaller > bigger);
}

TEST(PowerValueContainerTest, TestBiggerEqualsThan_DifferenUnits) {
    PowerValue<kWh> bigger(1000);
    PowerValue<Wh> smaller(1000);
    PowerValue<Wh> equal(1000000);

    ASSERT_GE(bigger, smaller);
    ASSERT_GE(bigger, equal);
    ASSERT_FALSE(smaller > bigger);
}

TEST(PowerValueContainerTest, TestSmallerThan) {
    PowerValue bigger(100);
    PowerValue smaller(10);
    PowerValue equal(10);

    ASSERT_LT(smaller, bigger);
    ASSERT_FALSE(bigger < smaller);
    ASSERT_FALSE(smaller < equal);
}

TEST(PowerValueContainerTest, TestSmallerThan_DifferenUnits) {
    PowerValue<kWh> bigger(1000);
    PowerValue<Wh> smaller(1000);
    PowerValue<kWh> equal(1);

    ASSERT_LT(smaller, bigger);
    ASSERT_FALSE(bigger < smaller);
    ASSERT_FALSE(smaller < equal);
}

TEST(PowerValueContainerTest, TestSmallerEqualsThan) {
    PowerValue bigger(100);
    PowerValue smaller(10);
    PowerValue equal(10);

    ASSERT_LE(smaller, bigger);
    ASSERT_LE(smaller, equal);
    ASSERT_FALSE(bigger <= smaller);
}

TEST(PowerValueContainerTest, TestSmallerEqualsThan_DifferenUnits) {
    PowerValue<kWh> bigger(1000);
    PowerValue<Wh> smaller(1000);
    PowerValue<kWh> equal(1);

    ASSERT_LE(smaller, bigger);
    ASSERT_LE(smaller, equal);
    ASSERT_FALSE(bigger <= smaller);
}

TEST(PowerValueContainerTest, TestEqual) {
    PowerValue base(1000);
    PowerValue equal(1000);
    PowerValue unequal(999);

    ASSERT_EQ(base, equal);
    ASSERT_FALSE(base == unequal);
}

TEST(PowerValueContainerTest, TestEqual_DifferenUnits) {
    PowerValue<kWh> base(1);
    PowerValue<Wh> equal(1000);
    PowerValue<Wh> unequal(1);

    ASSERT_EQ(base, equal);
    ASSERT_FALSE(base == unequal);
}

TEST(PowerValueContainerTest, TestUnequal) {
    PowerValue base(1000);
    PowerValue equal(1000);
    PowerValue unequal(999);

    ASSERT_NE(base, unequal);
    ASSERT_FALSE(base != equal);
}

TEST(PowerValueContainerTest, TestUnequal_DifferenUnits) {
    PowerValue<kWh> base(1);
    PowerValue<Wh> equal(1000);
    PowerValue<Wh> unequal(1);

    ASSERT_NE(base, unequal);
    ASSERT_FALSE(base != equal);

}
/*
 *  Arithmetic operator test
 */

TEST(PowerValueContainerTest, TestPlusOperator) {
    PowerValue<kWh> a(10);
    PowerValue<Wh> b(5000);

    ASSERT_EQ(a+a, PowerValue<kWh>(20));
    ASSERT_EQ(a+a, PowerValue<Wh>(20000));
    ASSERT_EQ(b+b, PowerValue<kWh>(10));
    ASSERT_EQ(b+b, PowerValue<Wh>(10000));
    ASSERT_EQ(a+b, PowerValue<kWh>(15));
    ASSERT_EQ(a+b, PowerValue<Wh>(15000));
    ASSERT_EQ(b+a, PowerValue<kWh>(15));
    ASSERT_EQ(b+a, PowerValue<Wh>(15000));
}

TEST(PowerValueContainerTest, TestMinusOperator) {
    PowerValue<kWh> a(10);
    PowerValue<Wh> b(5000);

    ASSERT_EQ(a-a, PowerValue<kWh>(0));
    ASSERT_EQ(a-a, PowerValue<Wh>(0));
    ASSERT_EQ(b-b, PowerValue<kWh>(0));
    ASSERT_EQ(b-b, PowerValue<Wh>(0));
    ASSERT_EQ(a-b, PowerValue<kWh>(5));
    ASSERT_EQ(a-b, PowerValue<Wh>(5000));
    ASSERT_EQ(b-a, PowerValue<kWh>(-5));
    ASSERT_EQ(b-a, PowerValue<Wh>(-5000));

}

TEST(PowerValueContainerTest, TestIntegralMultiplication) {
    PowerValue<kWh> PM_kWH(10);
    PowerValue<Wh> PM_WH(20000);

    ASSERT_EQ(PM_kWH*2, PowerValue<kWh>(20));
    ASSERT_EQ(PM_kWH*2, PowerValue<Wh>(20000));
    ASSERT_EQ(PM_WH*2, PowerValue<kWh>(40));
    ASSERT_EQ(PM_WH*2, PowerValue<Wh>(40000));

    ASSERT_EQ(PM_kWH*0, PowerValue<kWh>(0));
    ASSERT_EQ(PM_kWH*0, PowerValue<Wh>(0));
    ASSERT_EQ(PM_WH*0, PowerValue<kWh>(0));
    ASSERT_EQ(PM_WH*0, PowerValue<Wh>(0));

    ASSERT_EQ(PM_kWH*-2, PowerValue<kWh>(-20));
    ASSERT_EQ(PM_kWH*-2, PowerValue<Wh>(-20000));
    ASSERT_EQ(PM_WH*-2, PowerValue<kWh>(-40));
    ASSERT_EQ(PM_WH*-2, PowerValue<Wh>(-40000));
}

TEST(PowerValueContainerTest, TestFloatingPointMultiplication) {
    PowerValue<kWh> PM_kWH(10);
    PowerValue<Wh> PM_WH(20000);

    ASSERT_EQ(PM_kWH*0.5, PowerValue<kWh>(5));
    ASSERT_EQ(PM_kWH*0.5, PowerValue<Wh>(5000));
    ASSERT_EQ(PM_WH*0.5, PowerValue<kWh>(10));
    ASSERT_EQ(PM_WH*0.5, PowerValue<Wh>(10000));

    ASSERT_EQ(PM_kWH*0.0, PowerValue<kWh>(0));
    ASSERT_EQ(PM_kWH*0.0, PowerValue<Wh>(0));
    ASSERT_EQ(PM_WH*0.0, PowerValue<kWh>(0));
    ASSERT_EQ(PM_WH*0.0, PowerValue<Wh>(0));

    ASSERT_EQ(PM_kWH*-0.5, PowerValue<kWh>(-5));
    ASSERT_EQ(PM_kWH*-0.5, PowerValue<Wh>(-5000));
    ASSERT_EQ(PM_WH*-0.5, PowerValue<kWh>(-10));
    ASSERT_EQ(PM_WH*-0.5, PowerValue<Wh>(-10000));

}

TEST(PowerValueContainerTest, TestIntegralDivison) {
    PowerValue<kWh> PM_kWH(10);
    PowerValue<Wh> PM_WH(20000);

    ASSERT_EQ(PM_kWH/5, PowerValue<kWh>(2));
    ASSERT_EQ(PM_kWH/5, PowerValue<Wh>(2000));
    ASSERT_EQ(PM_WH/5, PowerValue<kWh>(4));
    ASSERT_EQ(PM_WH/5, PowerValue<Wh>(4000));

    ASSERT_EQ(PM_kWH/1, PM_kWH);
    ASSERT_EQ(PM_kWH/1, PM_kWH);
    ASSERT_EQ(PM_WH/1, PM_WH);
    ASSERT_EQ(PM_WH/1, PM_WH);

    ASSERT_EQ(PM_kWH/-5, PowerValue<kWh>(-2));
    ASSERT_EQ(PM_kWH/-5, PowerValue<Wh>(-2000));
    ASSERT_EQ(PM_WH/-5, PowerValue<kWh>(-4));
    ASSERT_EQ(PM_WH/-5, PowerValue<Wh>(-4000));
}

TEST(PowerValueContainerTest, TestFloatingPointDivison) {
    PowerValue<kWh> PM_kWH(15);
    PowerValue<Wh> PM_WH(30000);

    ASSERT_EQ(PM_kWH/1.5, PowerValue<kWh>(10));
    ASSERT_EQ(PM_kWH/1.5, PowerValue<Wh>(10000));
    ASSERT_EQ(PM_WH/1.5, PowerValue<kWh>(20));
    ASSERT_EQ(PM_WH/1.5, PowerValue<Wh>(20000));

    ASSERT_EQ(PM_kWH/1.0, PM_kWH);
    ASSERT_EQ(PM_kWH/1.0, PM_kWH);
    ASSERT_EQ(PM_WH/1.0, PM_WH);
    ASSERT_EQ(PM_WH/1.0, PM_WH);

    ASSERT_EQ(PM_kWH/-0.5, PowerValue<kWh>(-30));
    ASSERT_EQ(PM_kWH/-0.5, PowerValue<Wh>(-30000));
    ASSERT_EQ(PM_WH/-0.5, PowerValue<kWh>(-60));
    ASSERT_EQ(PM_WH/-0.5, PowerValue<Wh>(-60000));
}

/*
 *  Details test
 */

TEST(PowerValueContainerTest, TestNormalizationTokWh){
    ASSERT_EQ(Details::normalizeTokWh<kWh>(1000.0), 1000.0);
    ASSERT_EQ(Details::normalizeTokWh<Wh>(1000.0), 1.0);
}


TEST(PowerValueContainerTest, TestExtendFromkWh){
    ASSERT_EQ(Details::extendFromkWh<kWh>(1000.0), 1000.0);
    ASSERT_EQ(Details::extendFromkWh<Wh>(1.0), 1000.0);
}

