#pragma once
#include "Animation/AnimationClip.h"
#include "Containers/SmallVector.h"
#include "../../Components/SpriteTileSheet.h"

namespace Blz
{
	namespace Animation 
	{
		namespace System
		{
			AnimClip CreateAnimation(const uint16 lowIndexRange, const uint16 highIndexRange);
			SpriteTileSheetComponent SetAnimation(SpriteTileSheetComponent fighterSprite, AnimClip animation);
		}
	}
}
