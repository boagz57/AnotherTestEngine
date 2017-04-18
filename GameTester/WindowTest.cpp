#pragma once
#include "gtest/gtest.h"
#include "Window.h"

//Setup objects to be used in all tests for Window class
struct WindowTest : public testing::Test
{
	Window window;
};
