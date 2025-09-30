#pragma once

#include "Apothic/Core.h"

#define ARGON_SIMD_ENABLED
#define ARGON_SIMD_USE_AVX
#include <argon.h>

namespace apothic
{

	typedef unsigned int uint;

	enum class ApothicDataType
	{
		Nil = 0,

		Float,
		Double,
		Int,
		Uint,

		fvec2,
		fvec3,
		fvec4,

		dvec2,
		dvec3,
		dvec4,

		ivec2,
		ivec3,
		ivec4,

		uivec2,
		uivec3,
		uivec4,

		fmat2,
		fmat3,
		fmat4,
		fmat2x3,
		fmat3x2,
		fmat3x4,
		fmat4x3,

		dmat2,
		dmat3,
		dmat4,
		dmat2x3,
		dmat3x2,
		dmat3x4,
		dmat4x3,

		imat2,
		imat3,
		imat4,
		imat2x3,
		imat3x2,
		imat3x4,
		imat4x3,

		uimat2,
		uimat3,
		uimat4,
		uimat2x3,
		uimat3x2,
		uimat3x4,
		uimat4x3,

	};

	static size_t GetDataTypeSize(ApothicDataType type)
	{
		switch (type)
		{
		// primatives
		case ApothicDataType::Nil:
			return 0;
		case ApothicDataType::Float:
			return sizeof(float);
		case ApothicDataType::Double:
			return sizeof(double);
		case ApothicDataType::Int:
			return sizeof(int);
		case ApothicDataType::Uint:
			return sizeof(unsigned int);
		// vectors
		case ApothicDataType::fvec2:
			return sizeof(float) * 2;
		case ApothicDataType::fvec3:
			return sizeof(float) * 3;
		case ApothicDataType::fvec4:
			return sizeof(float) * 4;

		case ApothicDataType::dvec2:
			return sizeof(double) * 2;
		case ApothicDataType::dvec3:
			return sizeof(double) * 3;
		case ApothicDataType::dvec4:
			return sizeof(double) * 4;

		case ApothicDataType::ivec2:
			return sizeof(int) * 2;
		case ApothicDataType::ivec3:
			return sizeof(int) * 3;
		case ApothicDataType::ivec4:
			return sizeof(int) * 4;

		case ApothicDataType::uivec2:
			return sizeof(unsigned int) * 2;
		case ApothicDataType::uivec3:
			return sizeof(unsigned int) * 3;
		case ApothicDataType::uivec4:
			return sizeof(unsigned int) * 4;
		// matrices
		case ApothicDataType::fmat2:
			return sizeof(float) * 2 * 2;
		case ApothicDataType::fmat3:
			return sizeof(float) * 3 * 3;
		case ApothicDataType::fmat4:
			return sizeof(float) * 4 * 4;
		case ApothicDataType::fmat2x3:
			return sizeof(float) * 2 * 3;
		case ApothicDataType::fmat3x2:
			return sizeof(float) * 3 * 2;
		case ApothicDataType::fmat3x4:
			return sizeof(float) * 3 * 4;
		case ApothicDataType::fmat4x3:
			return sizeof(float) * 4 * 3;

		case ApothicDataType::dmat2:
			return sizeof(double) * 2 * 2;
		case ApothicDataType::dmat3:
			return sizeof(double) * 3 * 3;
		case ApothicDataType::dmat4:
			return sizeof(double) * 4 * 4;
		case ApothicDataType::dmat2x3:
			return sizeof(double) * 2 * 3;
		case ApothicDataType::dmat3x2:
			return sizeof(double) * 3 * 2;
		case ApothicDataType::dmat3x4:
			return sizeof(double) * 3 * 4;
		case ApothicDataType::dmat4x3:
			return sizeof(double) * 4 * 3;

		case ApothicDataType::imat2:
			return sizeof(int) * 2 * 2;
		case ApothicDataType::imat3:
			return sizeof(int) * 3 * 3;
		case ApothicDataType::imat4:
			return sizeof(int) * 4 * 4;
		case ApothicDataType::imat2x3:
			return sizeof(int) * 2 * 3;
		case ApothicDataType::imat3x2:
			return sizeof(int) * 3 * 2;
		case ApothicDataType::imat3x4:
			return sizeof(int) * 3 * 4;
		case ApothicDataType::imat4x3:
			return sizeof(int) * 4 * 3;

		case ApothicDataType::uimat2:
			return sizeof(unsigned int) * 2 * 2;
		case ApothicDataType::uimat3:
			return sizeof(unsigned int) * 3 * 3;
		case ApothicDataType::uimat4:
			return sizeof(unsigned int) * 4 * 4;
		case ApothicDataType::uimat2x3:
			return sizeof(unsigned int) * 2 * 3;
		case ApothicDataType::uimat3x2:
			return sizeof(unsigned int) * 3 * 2;
		case ApothicDataType::uimat3x4:
			return sizeof(unsigned int) * 3 * 4;
		case ApothicDataType::uimat4x3:
			return sizeof(unsigned int) * 4 * 3;
		}
		return 0;
	}

	static size_t GetComponentCount(ApothicDataType type)
	{
		switch (type)
		{
		// primatives
		case ApothicDataType::Nil:
			return 0;
		case ApothicDataType::Float:
			return 1;
		case ApothicDataType::Double:
			return 1;
		case ApothicDataType::Int:
			return 1;
		case ApothicDataType::Uint:
			return 1;
		// vectors
		case ApothicDataType::fvec2:
			return 2;
		case ApothicDataType::fvec3:
			return 3;
		case ApothicDataType::fvec4:
			return 4;

		case ApothicDataType::dvec2:
			return 2;
		case ApothicDataType::dvec3:
			return 3;
		case ApothicDataType::dvec4:
			return 4;

		case ApothicDataType::ivec2:
			return 2;
		case ApothicDataType::ivec3:
			return 3;
		case ApothicDataType::ivec4:
			return 4;

		case ApothicDataType::uivec2:
			return 2;
		case ApothicDataType::uivec3:
			return 3;
		case ApothicDataType::uivec4:
			return 4;
		// matrices
		case ApothicDataType::fmat2:
			return 2 * 2;
		case ApothicDataType::fmat3:
			return 3 * 3;
		case ApothicDataType::fmat4:
			return 4 * 4;
		case ApothicDataType::fmat2x3:
			return 2 * 3;
		case ApothicDataType::fmat3x2:
			return 3 * 2;
		case ApothicDataType::fmat3x4:
			return 3 * 4;
		case ApothicDataType::fmat4x3:
			return 4 * 3;

		case ApothicDataType::dmat2:
			return 2 * 2;
		case ApothicDataType::dmat3:
			return 3 * 3;
		case ApothicDataType::dmat4:
			return 4 * 4;
		case ApothicDataType::dmat2x3:
			return 2 * 3;
		case ApothicDataType::dmat3x2:
			return 3 * 2;
		case ApothicDataType::dmat3x4:
			return 3 * 4;
		case ApothicDataType::dmat4x3:
			return 4 * 3;

		case ApothicDataType::imat2:
			return 2 * 2;
		case ApothicDataType::imat3:
			return 3 * 3;
		case ApothicDataType::imat4:
			return 4 * 4;
		case ApothicDataType::imat2x3:
			return 2 * 3;
		case ApothicDataType::imat3x2:
			return 3 * 2;
		case ApothicDataType::imat3x4:
			return 3 * 4;
		case ApothicDataType::imat4x3:
			return 4 * 3;

		case ApothicDataType::uimat2:
			return 2 * 2;
		case ApothicDataType::uimat3:
			return 3 * 3;
		case ApothicDataType::uimat4:
			return 4 * 4;
		case ApothicDataType::uimat2x3:
			return 2 * 3;
		case ApothicDataType::uimat3x2:
			return 3 * 2;
		case ApothicDataType::uimat3x4:
			return 3 * 4;
		case ApothicDataType::uimat4x3:
			return 4 * 3;
		}
		return 0;
	}

}