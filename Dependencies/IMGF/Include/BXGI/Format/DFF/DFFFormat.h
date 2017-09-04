#pragma once

#include "nsbxgi.h"
#include "Format/RW/RWFormat.h"
#include "Intermediate/Model/IntermediateModelFormat.h"

class bxgi::DFFFormat : public bxgi::RWFormat
{
public:
	bxgi::IntermediateModelFormat*									convertToIntermediateModelFormat(void);
};