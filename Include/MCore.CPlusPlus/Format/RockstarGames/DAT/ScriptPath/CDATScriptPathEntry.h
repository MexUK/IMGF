#ifndef CDATScriptPathEntry_H
#define CDATScriptPathEntry_H

#include "mcore.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"

class mcore::CDATScriptPathEntry
{
public:
	CDATScriptPathEntry(void);
	
	void					unload(void) {}

	void					setPosition(mcore::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	mcore::CVector3D&				getPosition(void) { return m_vecPosition; }
	
	void					unserialize(void); // todo
	void					serialize(void); // todo
	
private:
	mcore::CVector3D				m_vecPosition;
};

#endif