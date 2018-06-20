#include "pwrmsrcontainertest.h"

using namespace DataContainer::Power;


TEST(PowerMeasurementContainerTest, TestConstexpr){
    PowerMeasurement<kWh> PM(5.0, 200);

    double test[static_cast<int>(PM.getValue<kWh>())];
    test[2] = PM.getValue<Wh>();

    ASSERT_EQ(test[2], PM.getValue<Wh>());
}


/**
 * @brief Copy and move constructors/assignments
 */


TEST(PowerMeasurementContainerTest, DefaultConstructor){
    PowerMeasurement<kWh> PM;

    ASSERT_EQ(PM.getValue(), 0);
    ASSERT_EQ(PM.getUnixTimestamp(), 0);
}


TEST(PowerMeasurementContainerTest, ParameterConstructor){
    PowerMeasurement<kWh> PM(0, 100);

    ASSERT_EQ(PM.getValue(), 0);
    ASSERT_EQ(PM.getUnixTimestamp(), 100);
}

TEST(PowerMeasurementContainerTest, CopyConstructor){
    const PowerMeasurement<kWh> PM_1(100, 100);
    PowerMeasurement<Wh> PM_2(PM_1);
    PowerMeasurement<kWh> PM_3(PM_1);

    ASSERT_EQ(PM_2.getValue(), 100000);
    ASSERT_EQ(PM_3.getValue(), 100);
    ASSERT_EQ(PM_2.getUnixTimestamp(), 100);
    ASSERT_EQ(PM_3.getUnixTimestamp(), 100);
}

TEST(PowerMeasurementContainerTest, MoveConstructor){
    PowerMeasurement<kWh> PM_1(17, 100);
    PowerMeasurement<kWh> PM_2(34, 200);
    PowerMeasurement<kWh>&& PM_3(std::move(PM_1));
    PowerMeasurement<Wh>&& PM_4(std::move(PM_2));

    ASSERT_EQ(PM_3.getValue(), 17);
    ASSERT_EQ(PM_3.getUnixTimestamp(), 100);
    ASSERT_EQ(PM_4.getValue(), 34000);
    ASSERT_EQ(PM_4.getUnixTimestamp(), 200);
}

TEST(PowerMeasurementContainerTest, CopyAssignmentOperator){
    const PowerMeasurement<kWh> PM_1(100, 100);
    PowerMeasurement<Wh> PM_2 = PM_1;
    PowerMeasurement<kWh> PM_3 =PM_1;

    ASSERT_EQ(PM_2.getValue(), 100000);
    ASSERT_EQ(PM_3.getValue(), 100);
    ASSERT_EQ(PM_2.getUnixTimestamp(), 100);
    ASSERT_EQ(PM_3.getUnixTimestamp(), 100);

}

TEST(PowerMeasurementContainerTest, MoveAssignmentOperator){
    PowerMeasurement<kWh> PM_1(17, 100);
    PowerMeasurement<kWh> PM_2(34, 200);
    PowerMeasurement<kWh>&& PM_3 = std::move(PM_1);
    PowerMeasurement<Wh>&& PM_4 = std::move(PM_2);

    ASSERT_EQ(PM_3.getValue(), 17);
    ASSERT_EQ(PM_3.getUnixTimestamp(), 100);
    ASSERT_EQ(PM_4.getValue(), 34000);
    ASSERT_EQ(PM_4.getUnixTimestamp(), 200);
}


/**
 * @brief Test the order operators
 */

TEST(PowerMeasurementContainerTest, Less){
    PowerMeasurement<kWh> Base(34, 500);
    PowerMeasurement<kWh> Le(17, 500);
    PowerMeasurement<kWh> Le2(34, 200);
    PowerMeasurement<Wh> Le3(33999, 500);
    PowerMeasurement<kWh> Eq(34, 500);
    PowerMeasurement<kWh> Ge(35, 500);
    PowerMeasurement<kWh> Ge2(34, 600);

    ASSERT_LT(Le, Base);
    ASSERT_LT(Le2, Base);
    ASSERT_LT(Le3, Base);
    ASSERT_FALSE(Ge < Le);
    ASSERT_FALSE(Ge2 < Le);
    ASSERT_FALSE(Base < Eq);
}


TEST(PowerMeasurementContainerTest, LessEqual){
    PowerMeasurement<kWh> Base(34, 500);
    PowerMeasurement<kWh> Le(17, 500);
    PowerMeasurement<kWh> Le2(34, 200);
    PowerMeasurement<Wh> Le3(33999, 500);
    PowerMeasurement<kWh> Eq(34, 500);
    PowerMeasurement<kWh> Ge(35, 500);
    PowerMeasurement<kWh> Ge2(34, 600);

    ASSERT_LE(Le, Base);
    ASSERT_LE(Le2, Base);
    ASSERT_LE(Le3, Base);
    ASSERT_LE(Eq, Base);
    ASSERT_FALSE(Ge <= Le);
    ASSERT_FALSE(Ge2 <= Le);
}

TEST(PowerMeasurementContainerTest, Greater){
    PowerMeasurement<kWh> Base(34, 500);
    PowerMeasurement<kWh> Le(17, 500);
    PowerMeasurement<kWh> Le2(34, 200);
    PowerMeasurement<kWh> Eq(34, 500);
    PowerMeasurement<kWh> Ge(35, 500);
    PowerMeasurement<kWh> Ge2(34, 600);
    PowerMeasurement<Wh> Ge3(34001, 500);

    ASSERT_GT(Ge, Base);
    ASSERT_GT(Ge2, Base);
    ASSERT_GT(Ge3, Base);
    ASSERT_FALSE(Eq > Base);
    ASSERT_FALSE(Le > Ge);
    ASSERT_FALSE(Le2 > Ge2);
}

TEST(PowerMeasurementContainerTest, GreaterEqual){
    PowerMeasurement<kWh> Base(34, 500);
    PowerMeasurement<kWh> Le(17, 500);
    PowerMeasurement<kWh> Le2(34, 200);
    PowerMeasurement<kWh> Eq(34, 500);
    PowerMeasurement<kWh> Ge(35, 500);
    PowerMeasurement<kWh> Ge2(34, 600);
    PowerMeasurement<Wh> Ge3(34001, 500);

    ASSERT_GE(Ge, Base);
    ASSERT_GE(Ge2, Base);
    ASSERT_GE(Ge3, Base);
    ASSERT_GE(Eq, Base);
    ASSERT_FALSE(Le >= Ge);
    ASSERT_FALSE(Le2 >= Ge2);
}

TEST(PowerMeasurementContainerTest, Equal){
    PowerMeasurement<kWh> Base(34, 500);
    PowerMeasurement<kWh> Same(34, 500);
    PowerMeasurement<Wh> Same2(34000, 500);

    ASSERT_EQ(Base, Same);
    ASSERT_EQ(Base, Same2);
}

TEST(PowerMeasurementContainerTest, NotEqual){
    PowerMeasurement<kWh> Base(34, 500);
    PowerMeasurement<kWh> Le(17, 500);
    PowerMeasurement<Wh> Le2(17, 500);
    PowerMeasurement<kWh> Le3(34, 400);
    PowerMeasurement<Wh> Le4(34000, 400);
    PowerMeasurement<kWh> Ge(34, 600);
    PowerMeasurement<Wh> Ge2(34000, 600);
    PowerMeasurement<kWh> Ge3(35, 500);
    PowerMeasurement<Wh> Ge4(35000, 500);

    ASSERT_NE(Base, Le);
    ASSERT_NE(Base, Le2);
    ASSERT_NE(Base, Le3);
    ASSERT_NE(Base, Le4);
    ASSERT_NE(Base, Ge);
    ASSERT_NE(Base, Ge2);
    ASSERT_NE(Base, Ge3);
    ASSERT_NE(Base, Ge4);
}


/**
 * @brief Test custom setter and getters
 */

TEST(PowerMeasurementContainerTest, getValue){
    PowerMeasurement<kWh> PM(34, 500);

    ASSERT_EQ(PM.getValue(), 34);
    ASSERT_EQ(PM.getValue<kWh>(), 34);
    ASSERT_EQ(PM.getValue<Wh>(), 34000);
}

TEST(PowerMeasurementContainerTest, setValue){
    PowerMeasurement<kWh> PM(34, 500);
    auto value = 700;

    ASSERT_EQ(PM.getValue<kWh>(), 34);
    PM.setValue(value);
    ASSERT_EQ(PM.getValue<kWh>(), value);
    ASSERT_EQ(PM.getValue<Wh>(), value*1000);
    value = 3000;
    PM.setValue<Wh>(value);
    ASSERT_EQ(PM.getValue<kWh>(), value/1000);
    ASSERT_EQ(PM.getValue<Wh>(), value);
}

TEST(PowerMeasurementContainerTest, getTime){
    PowerMeasurement<kWh> PM(34, 500);

    ASSERT_EQ(PM.getUnixTimestamp(), 500);
}

TEST(PowerMeasurementContainerTest, setTime){
    PowerMeasurement<kWh> PM(34, 500);

    ASSERT_EQ(PM.getUnixTimestamp(), 500);
    PM.setTime(700);
    ASSERT_EQ(PM.getUnixTimestamp(), 700);
}
