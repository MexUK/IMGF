#ifndef CMath_H
#define CMath_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Vector/Vec2f.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Type/Vector/Vec4u8.h"
#include "Type/Vector/Vec4u16.h"
#include "Type/Vector/Vec4u.h"
#include <vector>

#define SECTOR_BYTE_COUNT 2048

class bxcf::CMath
{
public:
	static float32				convertDegreesToRadians(float32 fDegrees);
	static float32				convertRadiansToDegrees(float32 fRadians);
	static float32				getDistanceBetweenPoints(bxcf::Vec2f& vecPosition1, bxcf::Vec2f& vecPosition2);
	static float32				getDistanceBetweenPoints(bxcf::Vec3f& vecPosition1, bxcf::Vec3f& vecPosition2);
	static float32				getAngleBetweenPoints(bxcf::Vec2f& vecPosition1, bxcf::Vec2f& vecPosition2);		// return: radians
	static float32				getAngleBetweenPoints(bxcf::Vec3f& vecPosition1, bxcf::Vec3f& vecPosition2);		// return: radians
	static bxcf::Vec2f			getPositionInFrontOfPosition(bxcf::Vec2f& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bxcf::Vec3f			getPositionInFrontOfPosition(bxcf::Vec3f& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bool					isPointInPolygon(bxcf::Vec2f& vecPoint, std::vector<bxcf::Vec2f>& vecPolygonPoints);
	static int					getFactorial(int iValue);
	static int					getBinomialCoefficient(int n, int k);
	static float32				getVelocitySpeed(bxcf::Vec3f& vecVelocity);
	static float32				getVelocityDirection(bxcf::Vec2f& vecVelocity);
	static bxcf::Vec2f			getVelocityFromSpeedAndDirection(float32 fSpeed, float32 fDirectionRad);
	static bxcf::Vec2f			getCartesianFromPolar(float32 fRadius, float32 fAngle);
	static void					getPolarFromCartesian(bxcf::Vec2f vecCartesian, float& fRadius, float& fAngle);
	static bxcf::Vec3f			getCartesianFromSpherical(float32 fRadius, float32 fInclination, float32 fAzimuthal);
	static void					getSphericalFromCartesian(bxcf::Vec3f vecCartesian, float& fRadius, float& fInclination, float& fAzimuthal);
	static bxcf::Vec3f			getPolygonCenter(std::vector<bxcf::Vec3f>& vecPoints);
	static bxcf::Vec3f			getBoundingCuboidMinFromSphere(bxcf::Vec3f& vecPosition, float32 fRadius);
	static bxcf::Vec3f			getBoundingCuboidMaxFromSphere(bxcf::Vec3f& vecPosition, float32 fRadius);
	static int32				limit(int32 iValue, int32 iMin, int32 iMax);
	static uint32				limit(uint32 uiValue, uint32 uiMin, uint32 uiMax);
	static float32				limit(float32 fValue, float32 fMin, float32 fMax);
	inline static uint32		convertSectorsToBytes(uint32 uiSectorCount);
	inline static uint32		convertBytesToSectors(uint32 uiByteCount);

	// open gl related
	static std::vector<bxcf::Vec3f>	getCuboidFaceVerticesAsQuads(bxcf::Vec3f& vecMinPosition, bxcf::Vec3f& vecMaxPosition);

	// vector or int related
	static bxcf::Vec4u8			createVector4ui8(uint8 ucByte1, uint8 ucByte2, uint8 ucByte3, uint8 ucByte4);
	static bxcf::Vec4u16			createVector4ui16(uint16 usWord1, uint16 usWord2, uint16 usWord3, uint16 usWord4);
	static bool					isPointInRectangle(bxcf::Vec2i& vecPoint, bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	static bool					isPointInEllipse(bxcf::Vec2i& vecPoint, bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);
	static bool					isPointOnLine(bxcf::Vec2i& vecPoint, bxcf::Vec2i& vecLinePoint1, bxcf::Vec2i& vecLinePoint2);
	static bool					isPointInPolygon(bxcf::Vec2i& vecPoint, std::vector<bxcf::Vec2i>& vecPolygonPoints);
	static bxcf::Vec4u			getRectangleFromCircle(bxcf::Vec2i vecCenterPosition, float32 fRadius);
	static uint32				getRowIndex(bxcf::Vec2i& vecPoint, bxcf::Vec2i& vecMinPosition, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRowIndexInRectangle(bxcf::Vec2i& vecPoint, bxcf::Vec2i& vecMinPosition, uint32 uiWidth, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRectangleResizeEdges(bxcf::Vec2i& vecPoint, bxcf::Vec2u& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static uint32				getRectangleResizeEdges(bxcf::Vec2i& vecPoint, bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static bxcf::Vec2i				getEllipseFromRectangle(bxcf::Vec2i& vecPoint, bxcf::Vec2u& vecSize);
	static uint32				convertDiameterToRadius(uint32 uiDiameter);
	static bxcf::Vec2u				get2DSizeFromCircle(bxcf::Vec2i& vecPoint, float32 fRadius);
	static uint32				getCenterX(uint32 uiWidth);
	static float32				getDistanceBetweenPoints(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);
	static float32				getAngleBetweenPoints(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);							// return: radians
	static bxcf::Vec2i				getPositionInFrontOfPosition(bxcf::Vec2i& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static float32				divide(int32 iInt1, int32 iInt2);
	static float32				divide(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static float32				multiply(int32 iInt1, int32 iInt2);
	static float32				multiply(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static bxcf::Vec2i				getBoundingRectanglePositionForLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);
	static bxcf::Vec2u				getBoundingRectangleSizeForLine(bxcf::Vec2i& vecPoint1, bxcf::Vec2i& vecPoint2);
	static bxcf::Vec2i				getBoundingRectanglePositionForPolygon(std::vector<bxcf::Vec2i>& vecPoints);
	static bxcf::Vec2u				getBoundingRectangleSizeForPolygon(std::vector<bxcf::Vec2i>& vecPoints);
	static void					getResizePositionAndSizeChange(bxcf::Vec2i& vecCursorChange, uint32 uiResizeEdges, bxcf::Vec2i& vecItemPositionChange, bxcf::Vec2i& vecItemSizeChange);	// [parameter uiResizeEdges] Edges: Left=1,Top=2,Right=4,Bottom=8
	static std::vector<bxcf::Vec2i>	getEquilateralTrianglePoints(bxcf::Vec2i& vecPoint, float32 fSideLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<bxcf::Vec2i>	getEquilateralTrianglePoints(bxcf::Vec2i& vecBottomLeftPoint, bxcf::Vec2i& vecBottomRightPoint);
	static std::vector<bxcf::Vec2i>	getEquilateralTrianglePoints(bxcf::Vec2i& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	static std::vector<bxcf::Vec2i>	getIsoscelesTrianglePoints(bxcf::Vec2i& vecPoint, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<bxcf::Vec2i>	getIsoscelesTrianglePoints(bxcf::Vec2i& vecBaseCenterPoint, bxcf::Vec2i& vecTipPoint, uint32 uiBaseHalfWidth);
	static std::vector<bxcf::Vec2i>	getIsoscelesTrianglePoints(bxcf::Vec2i& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	static float32				getEquilateralTriangleHeightFromSideLength(float32 fTriangleSideLength);
	static float32				getEquilateralTriangleSideLengthFromHeight(float32 fTriangleHeight);

	static uint32				getMaxEntryCount(uint32 uiAreaLengthPx, uint32 uiStepLengthPx);
	static uint32				getEntryStartIndex(uint32 uiTotalEntryCount, uint32 uiMaxEntryCount, float32 fProgress);
	static uint32				getEntryEndIndexExclusive(uint32 uiTotalEntryCount, uint32 uiEntryStartIndex, uint32 uiMaxEntryCount);

	static bool					doRectanglesCollide(bxcf::Vec2i& vecRectangle1Position, bxcf::Vec2u& vecRectangle1Size, bxcf::Vec2i& vecRectangle2Position, bxcf::Vec2u& vecRectangle2Size);
};

uint32				bxcf::CMath::convertSectorsToBytes(uint32 uiSectorCount)
{
	return uiSectorCount * SECTOR_BYTE_COUNT;
}

uint32				bxcf::CMath::convertBytesToSectors(uint32 uiByteCount)
{
	return (uint32) ceil(((float32)uiByteCount) / ((float32)SECTOR_BYTE_COUNT));
}

#endif