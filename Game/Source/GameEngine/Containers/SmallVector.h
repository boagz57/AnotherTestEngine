#pragma once
#include <boost/container/small_vector.hpp>
#include <vector>

namespace Blz
{
	template<typename type>
	using SmallVector = boost::container::small_vector<type, 10>;
}

