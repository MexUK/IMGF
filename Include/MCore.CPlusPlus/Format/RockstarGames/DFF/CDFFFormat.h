#ifndef CDFFFormat_H
#define CDFFFormat_H

#include "mcore.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Format/Intermediate/Model/CIntermediateModelFormat.h"
#include <string>
#include <vector>
#include <unordered_map>

class mcore::CRWVersion;
class mcore::CTextureEntry;
class mcore::C2dEffect;

class mcore::CDFFFormat : public mcore::CRWFormat
{
public:
	mcore::CIntermediateModelFormat*									convertToIntermediateModelFormat(void);
};

#endif