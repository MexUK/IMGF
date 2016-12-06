#ifndef CDumpManager_H
#define CDumpManager_H

#include <string>

class CDumpManager
{
public:
	void			process(void);

private:
	std::string		getEncoderClassIdFromImageExtension(std::string strFileExtension);
};

#endif