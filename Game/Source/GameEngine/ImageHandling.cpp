#include "STB_Img\stb_image.h"
#include "ImageHandling.h"

namespace Blz
{
	namespace ImgHandling
	{
		uchar8* LoadImage(const Blz::string c_filePath)
		{
			int32 x, y, currentChannels;
			int32 forceChannels = 4;
			uchar8* imageData = 0;
			imageData = stbi_load(c_filePath.c_str(), &x, &y, &currentChannels, forceChannels);

			if (imageData == nullptr)
			{
				LOG("ERROR: Could not load image file %s", c_filePath);
			};
			
			return imageData;
		}
	}
}