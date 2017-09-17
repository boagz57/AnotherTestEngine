#pragma once
#include <functional>
#include "Containers/Map.h"

class Fighter;

namespace Comp
{
	class Input
	{
	public:
		Input() = default;

		void MakeFighterControllable();
		bool IsFighterControllable();
		void SetKeyBinding(const int32 key, std::function<void(Fighter*)> movementFunction);
		void KeyPressed(const int32 key, Fighter * const fighter);

	private:
		bool isControllable = false;
		Blz::Map<const int32, std::function<void(Fighter*)>> keyMovementBindings;
	};
}