#pragma once
#include <map>

namespace Blz
{
	//C++11's way of typedef'ing with 'using'
	template<typename key, typename value>
	using Map = std::map<key, value>;
}
