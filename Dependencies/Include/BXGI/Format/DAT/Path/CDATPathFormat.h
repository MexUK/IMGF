#ifndef CDATPathFormat_H
#define CDATPathFormat_H

#include "bxgi.h"
#include "Format/CFormat.h"
#include "CDATPathEntry.h"
#include <string>
#include <vector>

class bxcf::Vec3f;

class bxgi::CDATPathFormat : public bxcf::CFormat
{
public:
	CDATPathFormat(void);
	
	void												unload(void);

	void												setPathsFormat(bxgi::eDATPathFormat eFormat) { m_header.m_ePathsFormat = eFormat; }
	bxgi::eDATPathFormat										getPathsFormat(void) { return m_header.m_ePathsFormat; }

	void												applyOffsetToPositions(bxcf::Vec3f& vecPositionOffset);

	void												addPathNode(CDATEntry_Paths_General_PathNode pathNode);
	void												addNaviNode(CDATEntry_Paths_General_NaviNode naviNode);
	void												addLink(CDATEntry_Paths_General_Link link);

	bxgi::CDATEntry_Paths_General_Header&						getHeader(void) { return m_header; }
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
	
	bxgi::eDATPathFormat										detectPathsFormat(void);

public: // todo - make this access specifier private
	uint32												m_uiFileIndex;
	bxgi::CDATEntry_Paths_General_Header						m_header;
	std::vector<bxgi::CDATEntry_Paths_General_PathNode>		m_vecPathNodes;
	std::vector<bxgi::CDATEntry_Paths_General_NaviNode>		m_vecNaviNodes;
	std::vector<bxgi::CDATEntry_Paths_General_Link>			m_vecLinks;
};

#endif