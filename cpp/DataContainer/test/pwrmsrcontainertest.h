#pragma once

#include "gtest/gtest.h"

#include "powermeasurement.h"

//https://github.com/google/googletest/blob/master/googletest/docs/Primer.md#simple-tests
class PowerMeasurementContainerTest : public ::testing::Test {
 protected:
  PowerMeasurementContainerTest() {}
  virtual ~PowerMeasurementContainerTest() { }
  virtual void SetUp() {}
  virtual void TearDown() {}

};
