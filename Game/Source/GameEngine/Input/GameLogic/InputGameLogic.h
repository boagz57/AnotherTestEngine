#pragma once

class Fighter;

namespace Blz::Input
{
	class GameLogic
	{
	public:
		static auto Bind(const int32 key, Fighter* const fighter, std::function<void(Fighter*)> actionFunc) -> void;
	};
}

using BlzInput = Blz::Input::GameLogic;