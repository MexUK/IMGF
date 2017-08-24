#ifndef CIPLEntry_CARS_H
#define CIPLEntry_CARS_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec2i.h"

class bxgi::CIPLEntry_CARS : public bxgi::CIPLEntry_Data
{
public:
	CIPLEntry_CARS(bxgi::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_CARS),
		m_vecPosition{ 0.0f, 0.0f, 0.0f },
		zRotation(0.0f),
		m_iVehicleModelId(0),
		m_uiForceSpawn(0),
		m_uiAlarmTriggerProbability(0),
		m_uiDoorLockProbability(0),
		m_uiUnknown1(0),
		m_uiUnknown2(0)
	{
		m_iVehicleColour.x = 0;
		m_iVehicleColour.y = 0;
	};

	void						unserialize(void);
	void						serialize(void);

	void						unserialize_Text(void);
	void						unserialize_Binary(void);

	void						serialize_Text(void);
	void						serialize_Binary(void);

	void						setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&					getPosition(void) { return m_vecPosition; }

	void						setZRotation(float32 zRotation) { zRotation = zRotation; } // in radians
	float32						getZRotation(void) { return zRotation; } // in radians

	void						setVehicleModelId(uint32 iVehicleModelId) { m_iVehicleModelId = iVehicleModelId; }
	uint32						getVehicleModelId(void) { return m_iVehicleModelId; }

	void						setVehicleColour(bxcf::Vec2i& vecVehicleColour) { m_iVehicleColour = vecVehicleColour; }
	bxcf::Vec2i&				getVehicleColour(void) { return m_iVehicleColour; }

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
	bxcf::Vec3f					m_vecPosition;
	float32						zRotation; // in radians
	int32						m_iVehicleModelId;
	bxcf::Vec2i					m_iVehicleColour;
	uint32						m_uiForceSpawn;
	uint32						m_uiAlarmTriggerProbability;
	uint32						m_uiDoorLockProbability;
	uint32						m_uiUnknown1;
	uint32						m_uiUnknown2;
};

#endif