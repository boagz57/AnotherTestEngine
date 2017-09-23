#pragma once

namespace Comp
{
	class Movement
	{
	public:
		auto GetGravity() const -> sfloat { return gravity; };

	private:
		sfloat gravity{ -7.0f };
	};
}