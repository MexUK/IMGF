#ifndef CDATPathFormat_H
#define CDATPathFormat_H

#include "mcore.h"
#include "Format/CFormat.h"
#include "CDATPathEntry.h"
#include <string>
#include <vector>

class mcore::CVector3D;

class mcore::CDATPathFormat : public mcore::CFormat
{
public:
	CDATPathFormat(void);
	
	void												unload(void);

	void												setPathsFormat(mcore::eDATPathFormat eFormat) { m_header.m_ePathsFormat = eFormat; }
	mcore::eDATPathFormat										getPathsFormat(void) { return m_header.m_ePathsFormat; }

	void												applyOffsetToPositions(mcore::CVector3D& vecPositionOffset);

	void												addPathNode(CDATEntry_Paths_General_PathNode pathNode);
	void												addNaviNode(CDATEntry_Paths_General_NaviNode naviNode);
	void												addLink(CDATEntry_Paths_General_Link link);

	mcore::CDATEntry_Paths_General_Header&						getHeader(void) { return m_header; }
	std::vector<CDATEntry_Paths_General_PathNode>&		getPathNodes(void) { return m_vecPathNodes; }
	std::vector<CDATEntry_Paths_General_NaviNode>&		getNaviNodes(void) { return m_vecNaviNodes; }
	std::vector<CDATEntry_Paths_General_Link>&			getLinks(void) { return m_vecLinks; }

	/*
	todo - [after DAT Paths rewrite] these 3 lines still needed?
	CDATPathFormat*			unserializeViaData_Paths(std::string strEntryData, uint32 uiAreaId, eDATPathFormat eDATPathFormatValue = DAT_PATH_UNKNOWN);
	CDATPathFormat*			parseViaData_Paths_Default(std::string strEntryData, uint32 uiAreaId);
	CDATPathFormat*			parseViaData_Paths_Fastman92(std::string strEntryData, uint32 uiAreaId);
	*/

private:
	void												unserialize(void);
	void												serialize(void);

	void												unserializeDefault(void);
	void												unserializeFastman92(void);

	void												serializeDefault(void);
	void												serializeFastman92(void); 
	
	mcore::eDATPathFormat										detectPathsFormat(void);

public: // todo - make this access specifier private
	uint32												m_uiFileIndex;
	mcore::CDATEntry_Paths_General_Header						m_header;
	std::vector<mcore::CDATEntry_Paths_General_PathNode>		m_vecPathNodes;
	std::vector<mcore::CDATEntry_Paths_General_NaviNode>		m_vecNaviNodes;
	std::vector<mcore::CDATEntry_Paths_General_Link>			m_vecLinks;
};

#endif