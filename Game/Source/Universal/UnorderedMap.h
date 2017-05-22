#pragma once
#include <unordered_map>

namespace Blz
{
	template<typename key, typename value>
	using UMap = std::unordered_map<key, value>;
}
