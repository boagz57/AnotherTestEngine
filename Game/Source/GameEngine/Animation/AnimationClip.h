#pragma once

namespace Blz
{
	namespace Animation
	{
		class AnimClip
		{
		public:
			uint16 lowIndexRange = 0;
			uint16 highIndexRange = 0;

			uint16 currentIndex = 0;
		};
	}
}