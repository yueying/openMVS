////////////////////////////////////////////////////////////////////
// Plane.h
//
// Copyright 2007 cDc@seacave
// Distributed under the Boost Software License, Version 1.0
// (See http://www.boost.org/LICENSE_1_0.txt)

#ifndef __SEACAVE_PLANE_H__
#define __SEACAVE_PLANE_H__


// I N C L U D E S /////////////////////////////////////////////////


// D E F I N E S ///////////////////////////////////////////////////


namespace SEACAVE {

// S T R U C T S ///////////////////////////////////////////////////

// Basic plane class
// (represented in Hessian Normal Form: n.x+d=0 <=> ax+by+cz+d=0)
template <typename TYPE>
class TPlane
{
public:
	typedef Eigen::Matrix<TYPE,4,1> VECTOR4;
	typedef Eigen::Matrix<TYPE,3,1> VECTOR;
	typedef Eigen::Matrix<TYPE,3,1> POINT;
	typedef SEACAVE::TAABB<TYPE,3> AABB;
	typedef SEACAVE::TRay<TYPE,3> RAY;

	VECTOR	m_vN;	// plane normal vector
	TYPE	m_fD;	// distance to origin

	//---------------------------------------

	inline TPlane() {}
	inline TPlane(const VECTOR&, TYPE);
	inline TPlane(const VECTOR&, const POINT&);
	inline TPlane(const POINT&, const POINT&, const POINT&);
	inline TPlane(const VECTOR4&);
	inline TPlane(const TYPE p[4]);

	inline void Set(const VECTOR&, TYPE);
	inline void Set(const VECTOR&, const POINT&);
	inline void Set(const POINT&, const POINT&, const POINT&);
	inline void Set(const VECTOR4&);
	inline void Set(const TYPE p[4]);
	inline void Negate();
	inline TYPE Distance(const TPlane&) const;
	inline TYPE DistanceAbs(const POINT&) const;
	inline TYPE Distance(const POINT&) const;
	inline UINT Classify(const POINT&) const;
	inline UINT Classify(const AABB&) const;

	bool Clip(const RAY&, TYPE, RAY*, RAY*) const;

	bool Intersects(const POINT& p0, const POINT& p1, const POINT& p2) const;
	bool Intersects(const TPlane& plane, RAY& ray) const;
	bool Intersects(const AABB& aabb) const;

	inline TYPE& operator [] (BYTE i) { ASSERT(i<4); return m_vN.data()[i]; }
	inline TYPE operator [] (BYTE i) const { ASSERT(i<4); return m_vN.data()[i]; }
}; // class TPlane
/*----------------------------------------------------------------*/


// Basic frustum class
// (represented as 6 planes)
template <typename TYPE, int DIMS=6>
class TFrustum
{
	COMPILE_TIME_ASSERT(DIMS > 0 && DIMS <= 6);

public:
	typedef Eigen::Matrix<TYPE,4,4,Eigen::RowMajor> MATRIX4x4;
	typedef Eigen::Matrix<TYPE,3,4,Eigen::RowMajor> MATRIX3x4;
	typedef Eigen::Matrix<TYPE,4,1> VECTOR4;
	typedef Eigen::Matrix<TYPE,3,1> VECTOR;
	typedef Eigen::Matrix<TYPE,3,1> POINT;
	typedef SEACAVE::TPlane<TYPE> PLANE;
	typedef SEACAVE::TAABB<TYPE,3> AABB;

	PLANE	m_planes[DIMS];	// left, right, top, bottom, near and far planes

	//---------------------------------------

	inline TFrustum() {}
	inline TFrustum(const MATRIX4x4&);
	inline TFrustum(const MATRIX3x4&);
	inline TFrustum(const MATRIX4x4&, TYPE width, TYPE height, TYPE near=TYPE(0.0001), TYPE far=TYPE(1000));
	inline TFrustum(const MATRIX3x4&, TYPE width, TYPE height, TYPE near=TYPE(0.0001), TYPE far=TYPE(1000));

	template <int MODE> void Set(const MATRIX4x4&);
	template <int MODE> void Set(const MATRIX3x4&);
	void Set(const MATRIX4x4&, TYPE width, TYPE height, TYPE near=TYPE(0.0001), TYPE far=TYPE(1000));
	void Set(const MATRIX3x4&, TYPE width, TYPE height, TYPE near=TYPE(0.0001), TYPE far=TYPE(1000));

	UINT Classify(const POINT&) const;
	UINT Classify(const AABB&) const;

	inline TYPE& operator [] (BYTE i) { ASSERT(i<DIMS); return m_planes[i]; }
	inline TYPE operator [] (BYTE i) const { ASSERT(i<DIMS); return m_planes[i]; }
}; // class TPlane
/*----------------------------------------------------------------*/


#include "Plane.inl"
/*----------------------------------------------------------------*/

} // namespace SEACAVE

#endif // __SEACAVE_PLANE_H__
