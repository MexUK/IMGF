#pragma once

#include "Type/Types.h"
#include <string>
#include <unordered_map>

class CBXSFormat
{
public:
	void			unserialize
	(
		std::string strFilePath,
		std::unordered_map<std::string,
			std::unordered_map<uint32,
				std::unordered_map<uint32,
					std::unordered_map<uint32,
						std::unordered_map<uint32,
							std::unordered_map<uint32, void*>
						>
					>
				>
			>
		> &umapCustomStyleGroups,
		std::unordered_map<std::string,
			std::unordered_map<uint32,
				std::unordered_map<uint32,
					std::unordered_map<uint32,
						std::unordered_map<uint32,
							std::unordered_map<uint32, void*>
						>
					>
				>
			>
		> &umapControlStyleGroups
	);
	void			serialize(void);
};