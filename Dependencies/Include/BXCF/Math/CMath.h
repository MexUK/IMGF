#ifndef CMath_H
#define CMath_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Type/Vector/CVector4ui8.h"
#include "Type/Vector/CVector4ui16.h"
#include "Type/Vector/CVector4ui32.h"
#include <vector>

#define SECTOR_BYTE_COUNT 2048

class bxcf::CMath
{
public:
	static float32				convertDegreesToRadians(float32 fDegrees);
	static float32				convertRadiansToDegrees(float32 fRadians);
	static float32				getDistanceBetweenPoints(bxcf::CVector2D& vecPosition1, bxcf::CVector2D& vecPosition2);
	static float32				getDistanceBetweenPoints(bxcf::CVector3D& vecPosition1, bxcf::CVector3D& vecPosition2);
	static float32				getAngleBetweenPoints(bxcf::CVector2D& vecPosition1, bxcf::CVector2D& vecPosition2);		// return: radians
	static float32				getAngleBetweenPoints(bxcf::CVector3D& vecPosition1, bxcf::CVector3D& vecPosition2);		// return: radians
	static bxcf::CVector2D			getPositionInFrontOfPosition(bxcf::CVector2D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bxcf::CVector3D			getPositionInFrontOfPosition(bxcf::CVector3D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bool					isPointInPolygon(bxcf::CVector2D& vecPoint, std::vector<bxcf::CVector2D>& vecPolygonPoints);
	static int					getFactorial(int iValue);
	static int					getBinomialCoefficient(int n, int k);
	static float32				getVelocitySpeed(bxcf::CVector3D& vecVelocity);
	static float32				getVelocityDirection(bxcf::CVector2D& vecVelocity);
	static bxcf::CVector2D			getVelocityFromSpeedAndDirection(float32 fSpeed, float32 fDirectionRad);
	static bxcf::CVector2D			getCartesianFromPolar(float32 fRadius, float32 fAngle);
	static void					getPolarFromCartesian(bxcf::CVector2D vecCartesian, float& fRadius, float& fAngle);
	static bxcf::CVector3D			getCartesianFromSpherical(float32 fRadius, float32 fInclination, float32 fAzimuthal);
	static void					getSphericalFromCartesian(bxcf::CVector3D vecCartesian, float& fRadius, float& fInclination, float& fAzimuthal);
	static bxcf::CVector3D			getPolygonCenter(std::vector<bxcf::CVector3D>& vecPoints);
	static bxcf::CVector3D			getBoundingCuboidMinFromSphere(bxcf::CVector3D& vecPosition, float32 fRadius);
	static bxcf::CVector3D			getBoundingCuboidMaxFromSphere(bxcf::CVector3D& vecPosition, float32 fRadius);
	static float32				cap(float32 fValue, float32 fMin, float32 fMax);
	inline static uint32		convertSectorsToBytes(uint32 uiSectorCount);
	inline static uint32		convertBytesToSectors(uint32 uiByteCount);

	// open gl related
	static std::vector<bxcf::CVector3D>	getCuboidFaceVerticesAsQuads(bxcf::CVector3D& vecMinPosition, bxcf::CVector3D& vecMaxPosition);

	// vector or int related
	static bxcf::CVector4ui8			createVector4ui8(uint8 ucByte1, uint8 ucByte2, uint8 ucByte3, uint8 ucByte4);
	static bxcf::CVector4ui16			createVector4ui16(uint16 usWord1, uint16 usWord2, uint16 usWord3, uint16 usWord4);
	static bool					isPointInRectangle(bxcf::CPoint2D& vecPoint, bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	static bool					isPointInEllipse(bxcf::CPoint2D& vecPoint, bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize);
	static bool					isPointOnLine(bxcf::CPoint2D& vecPoint, bxcf::CPoint2D& vecLinePoint1, bxcf::CPoint2D& vecLinePoint2);
	static bool					isPointInPolygon(bxcf::CPoint2D& vecPoint, std::vector<bxcf::CPoint2D>& vecPolygonPoints);
	static bxcf::CVector4ui32			getRectangleFromCircle(bxcf::CPoint2D vecCenterPosition, float32 fRadius);
	static uint32				getRowIndex(bxcf::CPoint2D& vecPoint, bxcf::CPoint2D& vecMinPosition, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRowIndexInRectangle(bxcf::CPoint2D& vecPoint, bxcf::CPoint2D& vecMinPosition, uint32 uiWidth, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRectangleResizeEdges(bxcf::CPoint2D& vecPoint, bxcf::CSize2D& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static uint32				getRectangleResizeEdges(bxcf::CPoint2D& vecPoint, bxcf::CPoint2D& vecPosition, bxcf::CSize2D& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static bxcf::CPoint2D				getEllipseFromRectangle(bxcf::CPoint2D& vecPoint, bxcf::CSize2D& vecSize);
	static uint32				convertDiameterToRadius(uint32 uiDiameter);
	static bxcf::CSize2D				get2DSizeFromCircle(bxcf::CPoint2D& vecPoint, float32 fRadius);
	static uint32				getCenterX(uint32 uiWidth);
	static float32				getDistanceBetweenPoints(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2);
	static float32				getAngleBetweenPoints(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2);							// return: radians
	static bxcf::CPoint2D				getPositionInFrontOfPosition(bxcf::CPoint2D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static float32				divide(int32 iInt1, int32 iInt2);
	static float32				divide(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static float32				multiply(int32 iInt1, int32 iInt2);
	static float32				multiply(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static bxcf::CPoint2D				getBoundingRectanglePositionForLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2);
	static bxcf::CSize2D				getBoundingRectangleSizeForLine(bxcf::CPoint2D& vecPoint1, bxcf::CPoint2D& vecPoint2);
	static bxcf::CPoint2D				getBoundingRectanglePositionForPolygon(std::vector<bxcf::CPoint2D>& vecPoints);
	static bxcf::CSize2D				getBoundingRectangleSizeForPolygon(std::vector<bxcf::CPoint2D>& vecPoints);
	static void					getResizePositionAndSizeChange(bxcf::CVector2i32& vecCursorChange, uint32 uiResizeEdges, bxcf::CVector2i32& vecItemPositionChange, bxcf::CVector2i32& vecItemSizeChange);	// [parameter uiResizeEdges] Edges: Left=1,Top=2,Right=4,Bottom=8
	static std::vector<bxcf::CPoint2D>	getEquilateralTrianglePoints(bxcf::CPoint2D& vecPoint, float32 fSideLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<bxcf::CPoint2D>	getEquilateralTrianglePoints(bxcf::CPoint2D& vecBottomLeftPoint, bxcf::CPoint2D& vecBottomRightPoint);
	static std::vector<bxcf::CPoint2D>	getEquilateralTrianglePoints(bxcf::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	static std::vector<bxcf::CPoint2D>	getIsoscelesTrianglePoints(bxcf::CPoint2D& vecPoint, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<bxcf::CPoint2D>	getIsoscelesTrianglePoints(bxcf::CPoint2D& vecBaseCenterPoint, bxcf::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth);
	static std::vector<bxcf::CPoint2D>	getIsoscelesTrianglePoints(bxcf::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	static float32				getEquilateralTriangleHeightFromSideLength(float32 fTriangleSideLength);
	static float32				getEquilateralTriangleSideLengthFromHeight(float32 fTriangleHeight);
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