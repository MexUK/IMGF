#ifndef CDFFFormat_H
#define CDFFFormat_H

#include "bxgi.h"
#include "Format/RW/CRWFormat.h"
#include "Intermediate/Model/CIntermediateModelFormat.h"

class bxgi::CDFFFormat : public bxgi::CRWFormat
{
public:
	bxgi::CIntermediateModelFormat*									convertToIntermediateModelFormat(void);
};

#endif