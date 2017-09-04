#pragma once

#include "nsbxcf.h"
#include "Format/Network/JSON/JSONValue.h"

class bxcf::JSONContainer : public bxcf::JSONValue
{
public:
	bxcf::JSONContainer*									m_pParentContainer;
};