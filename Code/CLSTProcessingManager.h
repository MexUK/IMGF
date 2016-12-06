#ifndef CLSTProcessingManager_H
#define CLSTProcessingManager_H

#include "Object/CManager.h"
#include <string>

struct CLSTFormat;

class CLSTProcessingManager : public mcore::CManager
{
public:
	void							init(void);
	void							uninit(void);

	void							process(CLSTFormat *pLSTFile);
};

#endif