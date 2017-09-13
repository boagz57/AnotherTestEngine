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
		void SetKeyBinding(int32 key, std::function<void(Fighter*)> movementFunction);
		void KeyPressed(int32 key, Fighter* fighter);

	private:
		bool isControllable = false;
		Blz::Map<int32, std::function<void(Fighter*)>> keyMovementBindings;
	};
}