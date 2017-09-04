#pragma once

#include "Type/Types.h"

namespace bxgi
{
	enum EEvent;

	class GameManager;
	class Game;
	class PlatformedGame;
	enum EGame;
	enum EGameFlag;
	enum EPlatformedGame;

	class RageManager;
	class RageResourceType;
	class RageResourceTypeManager;
	enum ERageResourceType;

	class RWFormat;
	class RWManager;
	class RWSection;
	class RWSectionContainer;
	class _2dEffect;
	class RWSectionDepthData;
	class RWVersion;
	class RWVersionManager;
	class TextureEntry;
	enum ERWSection;
	enum ERWVersion;
	class RWEntry_BinMeshPLG_Mesh;
	class RWEntry_TextureNative_MipMap;
	class RWEntry_2dEffect_CoverPoint;
	class RWEntry_2dEffect_EnterExit;
	class RWEntry_2dEffect_Escalator;
	class RWEntry_2dEffect_Light;
	class RWEntry_2dEffect_ParticleEffect;
	class RWEntry_2dEffect_PedAttractor;
	class RWEntry_2dEffect_SlotmachineWheel;
	class RWEntry_2dEffect_StreetSign;
	class RWEntry_2dEffect_SunGlare;
	class _2dEffectsPool;
	class RWGeometryBoundingInfo;
	class RWSection_2dEffect;
	class RWSection_Atomic;
	class RWSection_BinMeshPLG;
	class RWSection_Clump;
	class RWSection_Extension;
	class RWSection_ExtraVertColour;
	class RWSection_Frame;
	class RWSection_FrameList;
	class RWSection_Geometry;
	class RWSection_GeometryList;
	class RWSection_Light;
	class RWSection_Material;
	class RWSection_MaterialList;
	class RWSection_String;
	class RWSection_Texture;
	class RWSection_TextureDictionary;
	class RWSection_TextureNative;
	class RWSection_UnknownSection;

	enum E2DFXType;
	class COLEntry;
	class COLFormat;
	class COLManager;
	class COLVersion;
	class COLVersionManager;
	enum ECOLVersion;
	struct TBounds;
	struct TSurface;
	struct TSphere;
	struct TBox;
	struct TFaceGroup;
	struct TVertex;
	struct TFace;

	class DATAnimgrpSection;
	class DATAnimgrpEntry;
	class DATAnimgrpFormat;

	class DATCAPSFormat;

	class DATChaseEntry;
	class DATChaseFormat;
	class DATChaseEntry_Raw;

	struct DATEntry_Paths_Default_Header;
	struct DATEntry_Paths_Default_PathNode;
	struct DATEntry_Paths_Default_NaviNode;
	struct DATEntry_Paths_Default_Link;
	struct DATEntry_Paths_Default_NaviLink;
	struct DATEntry_Paths_Default_LinkLength;
	struct DATEntry_Paths_Default_Link_Wrapper;
	class CompressedVector;
	class CompressedVector_extended;
	struct NodeAddress;
	struct DATEntry_Paths_Fastman92_Header;
	struct DATEntry_Paths_Fastman92_PathNode;
	struct DATEntry_Paths_Fastman92_PathNode_extended;
	struct DATEntry_Paths_Fastman92_NaviNode;
	struct DATEntry_Paths_Fastman92_NaviNode_extended;
	struct DATEntry_Paths_Fastman92_Link;
	struct DATEntry_Paths_Fastman92_NaviLink;
	struct DATEntry_Paths_Fastman92_LinkLength;
	struct DATEntry_Paths_Fastman92_PathIntersectionFlags;
	struct DATEntry_Paths_General_Header;
	struct DATEntry_Paths_General_PathNode;
	struct DATEntry_Paths_General_NaviNode;
	struct DATEntry_Paths_General_Link;
	class DATPathFormat;
	class DATPathManager;
	enum EDATPathFormat;

	class DATLoaderEntry;
	class DATLoaderFormat;
	enum EDATLoaderEntryType;
	class DATLoaderManager;

	class DATScriptPathEntry;
	class DATScriptPathFormat;

	class DATWaterproEntry;
	class DATWaterproFormat;

	class DFFFormat;
	class DFFManager;

	class IDEEntry;
	class IDEFormat;
	class IDEManager;
	enum EIDEPathType;
	enum EIDESection;
	class IDEEntry_Data;
	class IDEEntry_Other;
	class IDEEntry_Section;
	class IDEEntry_2DFX;
	class IDEEntry_AGRPS;
	class IDEEntry_AMAT;
	class IDEEntry_ANIM;
	class IDEEntry_CARS;
	class IDEEntry_HAND;
	class IDEEntry_HIER;
	class IDEEntry_LINK;
	class IDEEntry_LODM;
	class IDEEntry_MLO;
	class IDEEntry_OBJS;
	class IDEEntry_PATH;
	class IDEEntry_PEDS;
	class IDEEntry_TANM;
	class IDEEntry_TOBJ;
	class IDEEntry_TREE;
	class IDEEntry_TXDP;
	class IDEEntry_UnknownSection;
	class IDEEntry_VNOD;
	class IDEEntry_WEAP;
	class IDEEntry_2DFX_Audio;
	class IDEEntry_2DFX_BouyancyAttr;
	class IDEEntry_2DFX_Escalator;
	class IDEEntry_2DFX_Explosion;
	class IDEEntry_2DFX_Ladder;
	class IDEEntry_2DFX_Light;
	class IDEEntry_2DFX_LightShaft;
	class IDEEntry_2DFX_Particle;
	class IDEEntry_2DFX_Ped;
	class IDEEntry_2DFX_ProcObject;
	class IDEEntry_2DFX_ScrollBar;
	class IDEEntry_2DFX_SpawnPoint;
	class IDEEntry_2DFX_SunReflection;
	class IDEEntry_2DFX_SwayableAttr;
	class IDEEntry_2DFX_Unknown1;
	class IDEEntry_2DFX_WalkDontWalkAttr;
	class IDEEntry_2DFX_WorldPoint;
	class IDEEntry_PATH_Group;
	class IDEEntry_PATH_Node;

	class IMGEntry;
	class IMGFormat;
	class IMGManager;
	enum EIMGEntryProperty;
	enum EIMGVersion;
	struct IMGEntry_Fastman92;
	struct IMGFormat_VersionFastman92_Header1;
	struct IMGFormat_VersionFastman92_Header2;
	enum EIMGVersionFastman92CompressionAlgorithm;
	struct RG_IMGEntry_Version1Or2;
	struct RG_IMGEntry_Version3;
	struct RG_IMGFormat_Version2_Header1;
	struct RG_IMGFormat_Version3_Header1;

	class IntermediateBoundingObject;
	class IntermediateGeometry;
	class IntermediateIndexData;
	class IntermediateVertexData;
	enum EIntermediateBoundingObjectType;
	class IntermediateModel;
	class IntermediateModelFormat;

	class IntermediateTextureMipmap;
	class IntermediateTexture;
	class IntermediateTextureFormat;

	class IPLEntry_PATH_Group;
	class IPLEntry_PATH_Node;
	class IPLEntry_2DFX;
	class IPLEntry_AUZO;
	class IPLEntry_BLOK;
	class IPLEntry_CARS;
	class IPLEntry_CULL;
	class IPLEntry_ENEX;
	class IPLEntry_GRGE;
	class IPLEntry_INST;
	class IPLEntry_JUMP;
	class IPLEntry_LINK;
	class IPLEntry_LODM;
	class IPLEntry_MLOPLUS;
	class IPLEntry_MULT;
	class IPLEntry_MZON;
	class IPLEntry_OCCL;
	class IPLEntry_PATH;
	class IPLEntry_PICK;
	class IPLEntry_RTFX;
	class IPLEntry_SLOW;
	class IPLEntry_TCYC;
	class IPLEntry_UnknownSection;
	class IPLEntry_VNOD;
	class IPLEntry_ZONE;
	class IPLEntry_Data;
	class IPLEntry_Other;
	class IPLEntry_Section;
	class IPLEntry;
	class IPLFormat;
	class IPLManager;
	enum EIPLPathType;
	enum EIPLSection;

	template<class FormatClass, typename SectionEnum> class SectionLinesEntry;
	template<class FormatClass, class EntryClass, typename SectionEnum, class OtherEntryClass, class SectionEntryClass, class DataEntryClass> class SectionLinesFormat;
	enum ESectionLinesEntryType;
	class SectionLinesEntry_Data;
	class SectionLinesEntry_Other;

	class TXDFormat;
	class TXDManager;
	enum ETXDRasterDataFormat;

	class WDRBlock_Geometry;
	class WDRBlock_IndexData;
	class WDRBlock_Model;
	class WDRBlock_VertexData;
	class WDRBoundingObject;
	class WDRFormat;
	class WDRManager;

	class WTDEntry;
	class WTDFormat;
	class WTDManager;
	class WTDMipmap;
	struct RG_WTDEntry;
	struct RG_WTDFormat_Header1;
	struct RG_WTDFormat_Header2;
};