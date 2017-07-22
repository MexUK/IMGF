#ifndef CDATScriptPathEntry_H
#define CDATScriptPathEntry_H

#include "bxa.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"

class bxa::CDATScriptPathEntry
{
public:
	CDATScriptPathEntry(void);
	
	void					unload(void) {}

	void					setPosition(bxa::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	bxa::CVector3D&				getPosition(void) { return m_vecPosition; }
	
	void					unserialize(void); // todo
	void					serialize(void); // todo
	
private:
	bxa::CVector3D				m_vecPosition;
};

#endif