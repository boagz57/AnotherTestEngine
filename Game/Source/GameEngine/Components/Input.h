#pragma once

namespace Comp
{
	class Input
	{
	public:
		Input() = default;

		void MakeFighterControllable();
		bool IsFighterControllable();

	private:
		bool isControllable = false;
	};
}