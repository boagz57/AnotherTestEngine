#pragma once

namespace Comp
{
	class Movement
	{
	public:
		auto GetGravity() const -> sfloat { return gravity; };

	private:
		sfloat gravity{ -70.8f };
	};
}