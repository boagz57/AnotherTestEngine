#pragma once
#include <boost/container/small_vector.hpp>

namespace Blz
{
	template<typename type, unsigned int size>
	using SmallVector = boost::container::small_vector<type, size>;
}

