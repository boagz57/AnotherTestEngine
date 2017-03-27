#pragma once
#include "gtest/gtest.h"
#include "Window.h"

TEST(Arbitruatry, alkjd)
{
	Window mywindow;
	EXPECT_TRUE(mywindow.Initialize());
}
