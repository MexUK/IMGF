#ifndef CDFFFormat_H
#define CDFFFormat_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Format/Intermediate/Model/CIntermediateModelFormat.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxcf::CRWVersion;
class bxcf::CTextureEntry;
class bxcf::C2dEffect;

class bxcf::CDFFFormat : public bxcf::CRWFormat
{
public:
	bxcf::CIntermediateModelFormat*									convertToIntermediateModelFormat(void);
};

#endif