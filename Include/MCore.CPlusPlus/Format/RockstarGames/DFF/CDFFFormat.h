#ifndef CDFFFormat_H
#define CDFFFormat_H

#include "bxa.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"
#include "Format/Intermediate/Model/CIntermediateModelFormat.h"
#include <string>
#include <vector>
#include <unordered_map>

class bxa::CRWVersion;
class bxa::CTextureEntry;
class bxa::C2dEffect;

class bxa::CDFFFormat : public bxa::CRWFormat
{
public:
	bxa::CIntermediateModelFormat*									convertToIntermediateModelFormat(void);
};

#endif