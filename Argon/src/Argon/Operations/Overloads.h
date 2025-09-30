#pragma once
#include "../DataTypes/Vector.h"

#ifdef ARGON_SIMD_ENABLED
#ifdef ARGON_SIMD_DISABLED
#error clashing simd definitions
#endif
#include "simd/Vector_Operations_SIMD.h"
#include "simd/Matrix_Operations_SIMD.h"

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator+(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_add_SIMD(A, B);
}
template<typename _T, unsigned int _L>

static void operator+=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_add_SIMD(A, B);
}

template<typename _T, unsigned int _L>

static argon::ArgonVector<_T, _L> operator*(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_mul_SIMD(A, B);
}
template<typename _T, unsigned int _L>

static void operator*=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_mul_SIMD(A, B);
}

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator-(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_sub_SIMD(A, B);
}
template<typename _T, unsigned int _L>
static void operator-=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_sub_SIMD(A, B);
}

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator/(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_div_SIMD(A, B);
}
template<typename _T, unsigned int _L>
static void operator/=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_div_SIMD(A, B);
}

template<typename _T, unsigned int _L>
static _T vecDistance(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
    return argon::ArgonVector_distance_SIMD(A, B);
}

template<typename _T, unsigned int _rows, unsigned int _cols>
static argon::ArgonMatrix<_T, _rows, _cols> operator*(const argon::ArgonMatrix<_T, _rows, _cols>& A, const argon::ArgonMatrix<_T, _cols, _rows>& B)
{
	return argon::ArgonMatrix_mul_SIMD(A, B);
}
template<typename _T, unsigned int _rows, unsigned int _cols>
static argon::ArgonVector<_T, _rows> operator*(const argon::ArgonMatrix<_T, _rows, _cols>& mat, const argon::ArgonVector<_T, _cols>& vec)
{
	return argon::ArgonMatrix_transform_ArgonVector_SIMD(mat, vec);
}


#elif defined ARGON_SIMD_DISABLED
#include "linear/Vector_Operations.h"
#include "linear/Matrix_Operations.h"

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator+(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_add(A, B);
}
template<typename _T, unsigned int _L>
static void operator+=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_add(A, B);
}

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator*(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_mul(A, B);
}
template<typename _T, unsigned int _L>
static void operator*=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_mul(A, B);
}

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator-(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_mul(A, B);
}
template<typename _T, unsigned int _L>
static void operator-=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_sub(A, B);
}

template<typename _T, unsigned int _L>
static argon::ArgonVector<_T, _L> operator/(const argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	return argon::ArgonVector_div(A, B);
}
template<typename _T, unsigned int _L>
static void operator/=(argon::ArgonVector<_T, _L>& A, const argon::ArgonVector<_T, _L>& B)
{
	A = argon::ArgonVector_div(A, B);
}

template<typename _T, unsigned int _L>
static _T vecDistance(const argon::ArgonVector<_T, _L>& A, conse argon::ArgonVector<_T, _L>& B)
{
    return argon::ArgonVector_distance(A, B);
}

template<typename _T, unsigned int _rows, unsigned int _cols>
static argon::ArgonMatrix<_T, _rows, _cols> operator*(const argon::ArgonMatrix<_T, _rows, _cols>& A, const argon::ArgonMatrix<_T, _cols, _rows>& B)
{ 
	return argon::ArgonMatrix_mul(A, B);
}
template<typename _T, unsigned int _rows, unsigned int _cols>
static argon::ArgonVector<_T, _rows> operator*(const argon::ArgonMatrix<_T, _rows, _cols>& mat, const argon::ArgonVector<_T, _cols>& vec)
{
	return argon::ArgonMatrix_transform_ArgonVector(mat, vec);
}

#else
#error [argon]: !simd not set as enabled or disabled!
#endif