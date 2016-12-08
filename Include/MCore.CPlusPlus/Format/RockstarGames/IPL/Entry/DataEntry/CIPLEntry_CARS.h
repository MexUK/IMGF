#ifndef CIPLEntry_CARS_H
#define CIPLEntry_CARS_H

#include "mcore.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector2i32.h"

class mcore::CIPLEntry_CARS : public mcore::CIPLEntry_Data
{
public:
	CIPLEntry_CARS(mcore::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_CARS),
		m_vecPosition{ 0.0f, 0.0f, 0.0f },
		m_zRotation(0.0f),
		m_iVehicleModelId(0),
		m_uiForceSpawn(0),
		m_uiAlarmTriggerProbability(0),
		m_uiDoorLockProbability(0),
		m_uiUnknown1(0),
		m_uiUnknown2(0)
	{
		m_iVehicleColour.m_x = 0;
		m_iVehicleColour.m_y = 0;
	};

	void						unserialize(void);
	void						serialize(void);

	void						unserialize_Text(void);
	void						unserialize_Binary(void);

	void						serialize_Text(void);
	void						serialize_Binary(void);

	void						setPosition(mcore::CVector3D& vecPosition) { m_vecPosition = vecPosition; }
	mcore::CVector3D&					getPosition(void) { return m_vecPosition; }

	void						setZRotation(float32 m_zRotation) { m_zRotation = m_zRotation; } // in radians
	float32						getZRotation(void) { return m_zRotation; } // in radians

	void						setVehicleModelId(uint32 iVehicleModelId) { m_iVehicleModelId = iVehicleModelId; }
	uint32						getVehicleModelId(void) { return m_iVehicleModelId; }

	void						setVehicleColour(mcore::CVector2i32& vecVehicleColour) { m_iVehicleColour = vecVehicleColour; }
	mcore::CVector2i32&				getVehicleColour(void) { return m_iVehicleColour; }

	void						setForceSpawn(uint32 uiForceSpawn) { m_uiForceSpawn = uiForceSpawn; }
	uint32						getForceSpawn(void) { return m_uiForceSpawn; }

	void						setAlarmTriggerProbability(uint32 uiAlarmTriggerProbability) { m_uiAlarmTriggerProbability = uiAlarmTriggerProbability; }
	uint32						getAlarmTriggerProbability(void) { return m_uiAlarmTriggerProbability; }

	void						setDoorLockProbability(uint32 uiDoorLockProbability) { m_uiDoorLockProbability = uiDoorLockProbability; }
	uint32						getDoorLockProbability(void) { return m_uiDoorLockProbability; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setUnknown2(uint32 uiUnknown2) { m_uiUnknown2 = uiUnknown2; }
	uint32						getUnknown2(void) { return m_uiUnknown2; }

private:
	// GTA SA only
	mcore::CVector3D					m_vecPosition;
	float32						m_zRotation; // in radians
	int32						m_iVehicleModelId;
	mcore::CVector2i32					m_iVehicleColour;
	uint32						m_uiForceSpawn;
	uint32						m_uiAlarmTriggerProbability;
	uint32						m_uiDoorLockProbability;
	uint32						m_uiUnknown1;
	uint32						m_uiUnknown2;
};

#endif