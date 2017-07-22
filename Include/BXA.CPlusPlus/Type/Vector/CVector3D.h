#ifndef CVector3D_H
#define CVector3D_H

#define _USE_MATH_DEFINES

#include "BXA.h"
#include "Type/Types.h"
#include <math.h>

class bxa::CVector3D
{
public:
	float32	m_x;	// todo - rename to .x and .y and .z
	float32	m_y;
	float32	m_z;
	
public:
	bxa::CVector3D(void);
	bxa::CVector3D(float32 fX, float32 fY, float32 fZ);
	
	/*
	bxa::CVector3D&	operator=	(VC::CVector& vecVectorVC)
	//operator VC::CVector&()
	{
		//return bxa::CVector3D::operator=(vecVectorVC);
		//m_X = vecVectorVC.m_X;
		//m_Y = vecVectorVC.m_Y;
		//m_Z = vecVectorVC.m_Z;

		//return *this;

		bxa::CVector3D vec(vecVectorVC.m_X, vecVectorVC.m_Y, vecVectorVC.m_Z);
		return vec;
	}
	*/

	/*
	bxa::CVector3D&	operator=(VC::CVector& vecVectorVC)
	{
		this->m_X = 1.0f;
		this->m_Y = 1.0f;
		this->m_Z = 15.0f;
	}
	*/

	bxa::CVector3D&		operator=(const bxa::CVector3D &vecVector3D);
	bxa::CVector3D		operator+(const bxa::CVector3D &vecVector3D);
	bxa::CVector3D		operator-(const bxa::CVector3D &vecVector3D);
	bxa::CVector3D		operator*(const bxa::CVector3D &vecVector3D);
	bxa::CVector3D		operator/(const bxa::CVector3D &vecVector3D);
	bxa::CVector3D		operator%(const bxa::CVector3D &vecVector3D);
	bool			operator!=(float32 fValue);
	bool			operator!=(const bxa::CVector3D &vecVector3D);
	bxa::CVector3D		operator-(void);
	template <class T>	bxa::CVector3D		operator+(const T value);
	template <class T>	bxa::CVector3D		operator-(const T value);
	template <class T>	bxa::CVector3D		operator*(const T value);
	template <class T>	bxa::CVector3D		operator/(const T value);
	template <class T>	bxa::CVector3D		operator%(const T value);

	void			toRadians(void);
	void			toDegrees(void);

	void			capAngleRadians(void);
	void			capAngleDegrees(void);

	bxa::CVector3D		getCrossProduct(bxa::CVector3D &vecVector3D);
	float32			getLength(void);
};

template <class T>
bxa::CVector3D		bxa::CVector3D::operator+(const T value)
{
	return bxa::CVector3D(
		m_x + value,
		m_y + value,
		m_z + value
		);
}
template <class T>
bxa::CVector3D		bxa::CVector3D::operator-(const T value)
{
	return bxa::CVector3D(
		m_x - value,
		m_y - value,
		m_z - value
		);
}
template <class T>
bxa::CVector3D		bxa::CVector3D::operator*(const T value)
{
	return bxa::CVector3D(
		m_x * value,
		m_y * value,
		m_z * value
		);
}
template <class T>
bxa::CVector3D		bxa::CVector3D::operator/(const T value)
{
	return bxa::CVector3D(
		m_x / value,
		m_y / value,
		m_z / value
		);
}
template <class T>
bxa::CVector3D		bxa::CVector3D::operator%(const T value)
{
	return bxa::CVector3D(
		fmod(m_x, value),
		fmod(m_y, value),
		fmod(m_z, value)
		);
}

#endif