#pragma once

namespace Comp
{
	class Movement
	{
	public:
		auto GetGravity() const -> sfloat { return gravity; };

	private:
		sfloat gravity{ -40.8f };
	};
}