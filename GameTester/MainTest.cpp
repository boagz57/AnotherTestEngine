#include <gmock\gmock.h>
#include <gtest\gtest.h>

GTEST_API_ int main(int argc, char* argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	RUN_ALL_TESTS();

	std::cin.get();
	return 0;
}