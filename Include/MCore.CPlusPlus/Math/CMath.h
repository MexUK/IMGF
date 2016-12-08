#ifndef CMath_H
#define CMath_H

#include "mcore.h"
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

class mcore::CMath
{
public:
	static float32				convertDegreesToRadians(float32 fDegrees);
	static float32				convertRadiansToDegrees(float32 fRadians);
	static float32				getDistanceBetweenPoints(mcore::CVector2D& vecPosition1, mcore::CVector2D& vecPosition2);
	static float32				getDistanceBetweenPoints(mcore::CVector3D& vecPosition1, mcore::CVector3D& vecPosition2);
	static float32				getAngleBetweenPoints(mcore::CVector2D& vecPosition1, mcore::CVector2D& vecPosition2);		// return: radians
	static float32				getAngleBetweenPoints(mcore::CVector3D& vecPosition1, mcore::CVector3D& vecPosition2);		// return: radians
	static mcore::CVector2D			getPositionInFrontOfPosition(mcore::CVector2D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static mcore::CVector3D			getPositionInFrontOfPosition(mcore::CVector3D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static bool					isPointInPolygon(mcore::CVector2D& vecPoint, std::vector<mcore::CVector2D>& vecPolygonPoints);
	static int					getFactorial(int iValue);
	static int					getBinomialCoefficient(int n, int k);
	static float32				getVelocitySpeed(mcore::CVector3D& vecVelocity);
	static float32				getVelocityDirection(mcore::CVector2D& vecVelocity);
	static mcore::CVector2D			getVelocityFromSpeedAndDirection(float32 fSpeed, float32 fDirectionRad);
	static mcore::CVector2D			getCartesianFromPolar(float32 fRadius, float32 fAngle);
	static void					getPolarFromCartesian(mcore::CVector2D vecCartesian, float& fRadius, float& fAngle);
	static mcore::CVector3D			getCartesianFromSpherical(float32 fRadius, float32 fInclination, float32 fAzimuthal);
	static void					getSphericalFromCartesian(mcore::CVector3D vecCartesian, float& fRadius, float& fInclination, float& fAzimuthal);
	static mcore::CVector3D			getPolygonCenter(std::vector<mcore::CVector3D>& vecPoints);
	static mcore::CVector3D			getBoundingCuboidMinFromSphere(mcore::CVector3D& vecPosition, float32 fRadius);
	static mcore::CVector3D			getBoundingCuboidMaxFromSphere(mcore::CVector3D& vecPosition, float32 fRadius);
	static float32				cap(float32 fValue, float32 fMin, float32 fMax);
	inline static uint32		convertSectorsToBytes(uint32 uiSectorCount);
	inline static uint32		convertBytesToSectors(uint32 uiByteCount);

	// open gl related
	static std::vector<mcore::CVector3D>	getCuboidFaceVerticesAsQuads(mcore::CVector3D& vecMinPosition, mcore::CVector3D& vecMaxPosition);

	// vector or int related
	static mcore::CVector4ui8			createVector4ui8(uint8 ucByte1, uint8 ucByte2, uint8 ucByte3, uint8 ucByte4);
	static mcore::CVector4ui16			createVector4ui16(uint16 usWord1, uint16 usWord2, uint16 usWord3, uint16 usWord4);
	static bool					isPointInRectangle(mcore::CPoint2D& vecPoint, mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize);
	static bool					isPointInEllipse(mcore::CPoint2D& vecPoint, mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize);
	static bool					isPointOnLine(mcore::CPoint2D& vecPoint, mcore::CPoint2D& vecLinePoint1, mcore::CPoint2D& vecLinePoint2);
	static bool					isPointInPolygon(mcore::CPoint2D& vecPoint, std::vector<mcore::CPoint2D>& vecPolygonPoints);
	static mcore::CVector4ui32			getRectangleFromCircle(mcore::CPoint2D vecCenterPosition, float32 fRadius);
	static uint32				getRowIndex(mcore::CPoint2D& vecPoint, mcore::CPoint2D& vecMinPosition, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRowIndexInRectangle(mcore::CPoint2D& vecPoint, mcore::CPoint2D& vecMinPosition, uint32 uiWidth, float32 fRowHeight, uint32 uiRowCount);
	static uint32				getRectangleResizeEdges(mcore::CPoint2D& vecPoint, mcore::CSize2D& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static uint32				getRectangleResizeEdges(mcore::CPoint2D& vecPoint, mcore::CPoint2D& vecPosition, mcore::CSize2D& vecSize, uint32 uiEdgeDistance); // [return] Edges: Left=1,Top=2,Right=4,Bottom=8
	static mcore::CPoint2D				getEllipseFromRectangle(mcore::CPoint2D& vecPoint, mcore::CSize2D& vecSize);
	static uint32				convertDiameterToRadius(uint32 uiDiameter);
	static mcore::CSize2D				get2DSizeFromCircle(mcore::CPoint2D& vecPoint, float32 fRadius);
	static uint32				getCenterX(uint32 uiWidth);
	static float32				getDistanceBetweenPoints(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2);
	static float32				getAngleBetweenPoints(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2);							// return: radians
	static mcore::CPoint2D				getPositionInFrontOfPosition(mcore::CPoint2D& vecPosition, float32 fAngleRad, float32 fRadius);		// parameter 2: radians
	static float32				divide(int32 iInt1, int32 iInt2);
	static float32				divide(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static float32				multiply(int32 iInt1, int32 iInt2);
	static float32				multiply(float32 fValue1, float32 fValue2);	// intended for sending non float values as parameters
	static mcore::CPoint2D				getBoundingRectanglePositionForLine(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2);
	static mcore::CSize2D				getBoundingRectangleSizeForLine(mcore::CPoint2D& vecPoint1, mcore::CPoint2D& vecPoint2);
	static mcore::CPoint2D				getBoundingRectanglePositionForPolygon(std::vector<mcore::CPoint2D>& vecPoints);
	static mcore::CSize2D				getBoundingRectangleSizeForPolygon(std::vector<mcore::CPoint2D>& vecPoints);
	static void					getResizePositionAndSizeChange(mcore::CVector2i32& vecCursorChange, uint32 uiResizeEdges, mcore::CVector2i32& vecItemPositionChange, mcore::CVector2i32& vecItemSizeChange);	// [parameter uiResizeEdges] Edges: Left=1,Top=2,Right=4,Bottom=8
	static std::vector<mcore::CPoint2D>	getEquilateralTrianglePoints(mcore::CPoint2D& vecPoint, float32 fSideLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<mcore::CPoint2D>	getEquilateralTrianglePoints(mcore::CPoint2D& vecBottomLeftPoint, mcore::CPoint2D& vecBottomRightPoint);
	static std::vector<mcore::CPoint2D>	getEquilateralTrianglePoints(mcore::CPoint2D& vecBottomLeftPoint, float32 fSideLength, float32 fBaseAngle);
	static std::vector<mcore::CPoint2D>	getIsoscelesTrianglePoints(mcore::CPoint2D& vecPoint, float32 fBaseLength, float32 fLegLength, uint32 uiPointingDirection);	// [parameter vecPoint] Represents top left point of triangle.
	static std::vector<mcore::CPoint2D>	getIsoscelesTrianglePoints(mcore::CPoint2D& vecBaseCenterPoint, mcore::CPoint2D& vecTipPoint, uint32 uiBaseHalfWidth);
	static std::vector<mcore::CPoint2D>	getIsoscelesTrianglePoints(mcore::CPoint2D& vecBottomLeftPoint, float32 fBaseLength, float32 fTipAngle, float32 fBaseAngle);
	static float32				getEquilateralTriangleHeightFromSideLength(float32 fTriangleSideLength);
	static float32				getEquilateralTriangleSideLengthFromHeight(float32 fTriangleHeight);
};

uint32				mcore::CMath::convertSectorsToBytes(uint32 uiSectorCount)
{
	return uiSectorCount * SECTOR_BYTE_COUNT;
}

uint32				mcore::CMath::convertBytesToSectors(uint32 uiByteCount)
{
	return (uint32) ceil(((float32)uiByteCount) / ((float32)SECTOR_BYTE_COUNT));
}

#endif