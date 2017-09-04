#pragma once

#include "Format/EFileType.h"
#include <string>

class GameFormat
{
public:
	static bool					isKnownGameExtension(std::string& strFileExtension);
	static bool					isModelExtension(std::string& strFileExtension);
	static bool					isTextureExtension(std::string& strFileExtension);
	static bool					isCollisionExtension(std::string& strFileExtension);
	static bool					isAnimationExtension(std::string& strFileExtension);

	static bxcf::fileType::EFileType		getRWFileType(std::string& strFileExtension);
};