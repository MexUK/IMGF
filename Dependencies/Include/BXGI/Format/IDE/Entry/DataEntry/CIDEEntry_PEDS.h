#ifndef CIDEEntry_PEDS_H
#define CIDEEntry_PEDS_H

#include "bxgi.h"
#include "Type/Types.h"
#include "Format/IDE/Entry/CIDEEntry_Data.h"
#include "Type/Vector/Vec2u.h"
#include <string>

class bxgi::CIDEEntry_PEDS : public bxgi::CIDEEntry_Data
{
public:
	CIDEEntry_PEDS(bxgi::CIDEFormat *pIDEFormat) :
		CIDEEntry_Data(pIDEFormat, IDE_SECTION_PEDS),
		m_uiObjectId(0),
		m_uiCarsCanDrive(0)
	{
		m_vecPreferredRadioStations.x = 0;
		m_vecPreferredRadioStations.y = 0;
	};

	void						unserialize(void);
	void						serialize(void);

	void						setObjectId(uint32 uiObjectId) { m_uiObjectId = uiObjectId; }
	uint32						getObjectId(void) { return m_uiObjectId; }

	void						setModelName(std::string& strModelName) { m_strModelName = strModelName; }
	std::string&				getModelName(void) { return m_strModelName; }

	void						setTXDName(std::string& strTXDName) { m_strTXDName = strTXDName; }
	std::string&				getTXDName(void) { return m_strTXDName; }

	void						setDefaultPedType(std::string& strDefaultPedType) { m_strDefaultPedType = strDefaultPedType; }
	std::string&				getDefaultPedType(void) { return m_strDefaultPedType; }

	void						setBehaviour(std::string& strBehaviour) { m_strBehaviour = strBehaviour; }
	std::string&				getBehaviour(void) { return m_strBehaviour; }

	void						setAnimationGroup(std::string& strAnimationGroup) { m_strAnimationGroup = strAnimationGroup; }
	std::string&				getAnimationGroup(void) { return m_strAnimationGroup; }

	void						setCarsCanDrive(uint32 uiCarsCanDrive) { m_uiCarsCanDrive = uiCarsCanDrive; }
	uint32						getCarsCanDrive(void) { return m_uiCarsCanDrive; }

	void						setAnimationFile(std::string& strAnimationFile) { m_strAnimationFile = strAnimationFile; }
	std::string&				getAnimationFile(void) { return m_strAnimationFile; }

	void						setPreferredRadioStations(bxcf::Vec2u& vecPreferredRadioStations) { m_vecPreferredRadioStations = vecPreferredRadioStations; }
	bxcf::Vec2u&				getPreferredRadioStations(void) { return m_vecPreferredRadioStations; }

	void						setVoiceArchive(std::string& strVoiceArchive) { m_strVoiceArchive = strVoiceArchive; }
	std::string&				getVoiceArchive(void) { return m_strVoiceArchive; }

	void						setAnimationFile(std::string& strVoice, uint32 uiVoiceIndex) { m_strVoices[uiVoiceIndex] = strVoice; }
	std::string&				getAnimationFile(uint32 uiVoiceIndex) { return m_strVoices[uiVoiceIndex]; }

	void						setProps(std::string& strProps) { m_strProps = strProps; }
	std::string&				getProps(void) { return m_strProps; }

	void						setGestureGroup(std::string& strGestureGroup) { m_strGestureGroup = strGestureGroup; }
	std::string&				getGestureGroup(void) { return m_strGestureGroup; }

	void						setGesturePhoneGroup(std::string& strGesturePhoneGroup) { m_strGesturePhoneGroup = strGesturePhoneGroup; }
	std::string&				getGesturePhoneGroup(void) { return m_strGesturePhoneGroup; }

	void						setFacialGroup(std::string& strFacialGroup) { m_strFacialGroup = strFacialGroup; }
	std::string&				getFacialGroup(void) { return m_strFacialGroup; }

	void						setVisemeGroup(std::string& strVisemeGroup) { m_strVisemeGroup = strVisemeGroup; }
	std::string&				getVisemeGroup(void) { return m_strVisemeGroup; }

	void						setFlags(std::string& strFlags) { m_strFlags = strFlags; } // hex
	std::string&				getFlags(void) { return m_strFlags; } // hex

	void						setBlendShapeFile(std::string& strBlendShapeFile) { m_strBlendShapeFile = strBlendShapeFile; }
	std::string&				getBlendShapeFile(void) { return m_strBlendShapeFile; }

	void						setAudioType(std::string& strAudioType) { m_strAudioType = strAudioType; }
	std::string&				getAudioType(void) { return m_strAudioType; }

	void						setFirstVoice(std::string& strFirstVoice) { m_strFirstVoice = strFirstVoice; }
	std::string&				getFirstVoice(void) { return m_strFirstVoice; }

	void						setLastVoice(std::string& strLastVoice) { m_strLastVoice = strLastVoice; }
	std::string&				getLastVoice(void) { return m_strLastVoice; }

private:
	// GTA III era & GTA IV
	std::string					m_strModelName;
	std::string					m_strDefaultPedType;
	std::string					m_strAnimationGroup;
	std::string					m_strAnimationFile;
	bxcf::Vec2u				m_vecPreferredRadioStations;
	std::string					m_strVoices[2];

	// GTA III era only
	uint32						m_uiObjectId;
	std::string					m_strTXDName;
	std::string					m_strBehaviour;
	uint32						m_uiCarsCanDrive;
	std::string					m_strVoiceArchive;

	// GTA IV only
	std::string					m_strProps;
	std::string					m_strGestureGroup;
	std::string					m_strGesturePhoneGroup;
	std::string					m_strFacialGroup;
	std::string					m_strVisemeGroup;
	std::string					m_strFlags; // hex
	std::string					m_strBlendShapeFile;
	std::string					m_strAudioType;
	std::string					m_strFirstVoice;
	std::string					m_strLastVoice;
};

#endif