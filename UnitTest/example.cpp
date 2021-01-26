/*
 * example.cpp
 *
 *  Created on: 22-Jan-2021
 *      Author: piyush-bisen
 */

#include "gtest/gtest.h"
#include "SampleClass.h"
TEST(Test1,print){
    SampleClass obj;
    obj.print();
    EXPECT_EQ(1,1);
}


