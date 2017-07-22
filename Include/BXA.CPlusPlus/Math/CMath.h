#ifndef CMath_H
#define CMath_H

#include "BXA.h"
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

class bxa::CMath
{
public:
	static float32				convertDegreesToRadians(float32 fDegrees);
	static float32				convertRadiansToDegrees(float32 fRadians);
	static float32				getDistanceBetweenPoints(bxa::CVector2D& vecPosition1, bxa::CVector2D& vecPosition2);
	static float32				getDistanceBetweenPoints(bxa::CVector3D& vecPosition1, bxa::CVector3D& vecPosition2);
	static float32				getAngleBetweenPoints(bxa::CVector2D& vecPosition1, bxa::CVector2D& vecPosition2);		// return: radians
	static float32				getAngleBetweenPoints(bxa::CVector3D& vecPosition1, bxa::CVector3D& vecPosition2);		// return: radians
	static bxa::CVector2D			getPositionInFrontOfPosition(bxa::CVector2D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bxa::CVector3D			getPositionInFrontOfPosition(bxa::CVector3D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bool					isPointInPolygon(bxa::CVector2D& vecPoint, std::vector<bxa::CVector2D>& vecPolygonPoints);
	static int					getFactorial(int iValue);
	static int					getBinomialCoefficient(int n, int k);
	static float32				getVelocitySpeed(bxa::CVector3D& vecVelocity);
	static float32				getVelocityDirection(bxa::CVector2D& vecVelocity);
	static bxa::CVector2D			getVelocityFromSpeedAndDirection(float32 fSpeed, float32 fDirectionRad);
	static bxa::CVector2D			getCartesianFromPolar(float32 fRadius, float32 fAngle);
	static void					getPolarFromCartesian(bxa::CVector2D vecCartesian, float& fRadius, float& fAngle);
	static bxa::CVector3D			getCartesianFromSpherical(float32 fRadius, float32 fInclination, float32 fAzimuthal);
	static void					getSphericalFromCartesian(bxa::CVector3D vecCartesian, float& fRadius, float& fInclination, float& fAzimuthal);
	static bxa::CVector3D			getPolygonCenter(std::vector<bxa::CVector3D>& vecPoints);
	static bxa::CVector3D			getBoundingCuboidMinFromSphere(bxa::CVector3D& vecPosition, float32 fRadius);
	static bxa::CVector3D			getBoundingCuboidMaxFromSphere(bxa::CVector3D& vecPosition, float32 fRadius);
	static float32				cap(float32 fValue, float32 fMin, float32 fMax);
	inline static uint32		convertSectorsToBytes(uint32 uiSectorCount);
	inline static uint32		convertBytesToSectors(uint32 uiByteCount);

	// open gl related
	static std::vector<bxa::CVector3D>	getCuboidFaceVerticesAsQuads(bxa::CVector3D& vecMinPosition, bxa::CVector3D& vecMaxPosition);

	// vector or int related
	static bxa::CVector4ui8			createVector4ui8(uint8 ucByte1, uint8 ucByte2, uint8 ucByte3, uint8 ucByte4);
	static bxa::CVector4ui16			createVector4ui16(uint16 usWord1, uint16 usWord2, uint16 usWord3, uint16 usWord4);
	static bool					isPointInRectangle(bxa::CPoint2D& vecPoint, bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize);
	static bool					isPointInEllipse(bxa::CPoint2D& vecPoint, bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize);
	static bool					isPointOnLine(bxa::CPoint2D& vecPoint, bxa::CPoint2D& vecLinePoint1, bxa::CPoint2D& vecLinePoint2);
	static bool					isPointInPolygon(bxa::CPoint2D& vecPoint, std::vector<bxa::CPoint2D>& vecPolygonPoints);
	static bxa::CVector4ui32			getRectangleFromCircle(bxa::CPoint2D vecCenterPosition, float32 fRadius);
	static uint32				getRowIndex(bxa::CPoint2D& vecPoint, bxa::CPoint2D& vecMinPosition, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRowIndexInRectangle(bxa::CPoint2D& vecPoint, bxa::CPoint2D& vecMinPosition, uint32 uiWidth, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRectangleResizeEdges(bxa::CPoint2D& vecPoint, bxa::CSize2D& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static uint32				getRectangleResizeEdges(bxa::CPoint2D& vecPoint, bxa::CPoint2D& vecPosition, bxa::CSize2D& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static bxa::CPoint2D				getEllipseFromRectangle(bxa::CPoint2D& vecPoint, bxa::CSize2D& vecSize);
	static uint32				convertDiameterToRadius(uint32 uiDiameter);
	static bxa::CSize2D				get2DSizeFromCircle(bxa::CPoint2D& vecPoint, float32 fRadius);
	static uint32				getCenterX(uint32 uiWidth);
	static float32				getDistanceBetweenPoints(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2);
	static float32				getAngleBetweenPoints(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2);							// return: radians
	static bxa::CPoint2D				getPositionInFrontOfPosition(bxa::CPoint2D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static float32				divide(int32 iInt1, int32 iInt2);
	static float32				divide(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static float32				multiply(int32 iInt1, int32 iInt2);
	static float32				multiply(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static bxa::CPoint2D				getBoundingRectanglePositionForLine(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2);
	static bxa::CSize2D				getBoundingRectangleSizeForLine(bxa::CPoint2D& vecPoint1, bxa::CPoint2D& vecPoint2);
	static bxa::CPoint2D				getBoundingRectanglePositionForPolygon(std::vector<bxa::CPoint2D>& vecPoints);
	static bxa::CSize2D				getBoundingRectangleSizeForPolygon(std::vector<bxa::CPoint2D>& vecPoints);
	static void					getResizePositionAndSizeChange(bxa::CVector2i32& vecCursorChange, uint32 uiResizeEdges, bxa::CVector2i32& vecItemPositionChange, bxa::CVector2i32& vecItemSizeChange);	// [parameter uiResizeEdges] Edges: Left=1,Top=2,Right=4,Bottom=8
	static std::vector<bxa::CPoint2D>	getEquilateralTrianglePoints(bxa::CPoint2D& vecPoint, float32 fSideLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<bxa::CPoint2D>	getEquilateralTrianglePoints(bxa::CPoint2D& vecBottomLeftPoint, bxa::CPoint2D& vecBottomRightPoint);
	static std::vector<bxa::CPoint2D>	getEquilateralTrianglePoints(bxa::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	static std::vector<bxa::CPoint2D>	getIsoscelesTrianglePoints(bxa::CPoint2D& vecPoint, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<bxa::CPoint2D>	getIsoscelesTrianglePoints(bxa::CPoint2D& vecBaseCenterPoint, bxa::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth);
	static std::vector<bxa::CPoint2D>	getIsoscelesTrianglePoints(bxa::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	static float32				getEquilateralTriangleHeightFromSideLength(float32 fTriangleSideLength);
	static float32				getEquilateralTriangleSideLengthFromHeight(float32 fTriangleHeight);
};

uint32				bxa::CMath::convertSectorsToBytes(uint32 uiSectorCount)
{
	return uiSectorCount * SECTOR_BYTE_COUNT;
}

uint32				bxa::CMath::convertBytesToSectors(uint32 uiByteCount)
{
	return (uint32) ceil(((float32)uiByteCount) / ((float32)SECTOR_BYTE_COUNT));
}

#endif