#pragma once
#include <vector>
#include <boost/container/small_vector.hpp>

namespace Blz
{
	template<typename type>
	using Vector = boost::container::small_vector<type, 10>; 
}
