#ifndef CDATScriptPathEntry_H
#define CDATScriptPathEntry_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"

class bxcf::CDATScriptPathEntry
{
public:
	CDATScriptPathEntry(void);
	
	void					unload(void) {}

	void					setPosition(bxcf::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::CVector3D&				getPosition(void) { return m_vecPosition; }
	
	void					unserialize(void); // todo
	void					serialize(void); // todo
	
private:
	bxcf::CVector3D				m_vecPosition;
};

#endif