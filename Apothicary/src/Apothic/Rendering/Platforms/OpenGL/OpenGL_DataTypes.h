#pragma once

#include "../../DataTypes.h"

#include <glad/glad.h>

namespace apothic
{

	static GLenum ToGLType(ApothicDataType type)
	{
		switch (type)
		{
			// primatives
		case ApothicDataType::Nil:
			return 0;
		case ApothicDataType::Float:
			return GL_FLOAT;
		case ApothicDataType::Double:
			return GL_DOUBLE;
		case ApothicDataType::Int:
			return GL_INT;
		case ApothicDataType::Uint:
			return GL_UNSIGNED_INT;
			// vectors
		case ApothicDataType::fvec2:
			return GL_FLOAT;
		case ApothicDataType::fvec3:
			return GL_FLOAT;
		case ApothicDataType::fvec4:
			return GL_FLOAT;

		case ApothicDataType::dvec2:
			return GL_DOUBLE;
		case ApothicDataType::dvec3:
			return GL_DOUBLE;
		case ApothicDataType::dvec4:
			return GL_DOUBLE;

		case ApothicDataType::ivec2:
			return GL_INT;
		case ApothicDataType::ivec3:
			return GL_INT;
		case ApothicDataType::ivec4:
			return GL_INT;

		case ApothicDataType::uivec2:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uivec3:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uivec4:
			return GL_UNSIGNED_INT;
			// matrices
		case ApothicDataType::fmat2:
			return GL_FLOAT;
		case ApothicDataType::fmat3:
			return GL_FLOAT;
		case ApothicDataType::fmat4:
			return GL_FLOAT;
		case ApothicDataType::fmat2x3:
			return GL_FLOAT;
		case ApothicDataType::fmat3x2:
			return GL_FLOAT;
		case ApothicDataType::fmat3x4:
			return GL_FLOAT;
		case ApothicDataType::fmat4x3:
			return GL_FLOAT;

		case ApothicDataType::dmat2:
			return GL_DOUBLE;
		case ApothicDataType::dmat3:
			return GL_DOUBLE;
		case ApothicDataType::dmat4:
			return GL_DOUBLE;
		case ApothicDataType::dmat2x3:
			return GL_DOUBLE;
		case ApothicDataType::dmat3x2:
			return GL_DOUBLE;
		case ApothicDataType::dmat3x4:
			return GL_DOUBLE;
		case ApothicDataType::dmat4x3:
			return GL_DOUBLE;

		case ApothicDataType::imat2:
			return GL_INT;
		case ApothicDataType::imat3:
			return GL_INT;
		case ApothicDataType::imat4:
			return GL_INT;
		case ApothicDataType::imat2x3:
			return GL_INT;
		case ApothicDataType::imat3x2:
			return GL_INT;
		case ApothicDataType::imat3x4:
			return GL_INT;
		case ApothicDataType::imat4x3:
			return GL_INT;

		case ApothicDataType::uimat2:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uimat3:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uimat4:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uimat2x3:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uimat3x2:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uimat3x4:
			return GL_UNSIGNED_INT;
		case ApothicDataType::uimat4x3:
			return GL_UNSIGNED_INT;
		}
		return 0;
	}

	static ApothicDataType GetApothicDataType(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return ApothicDataType::Float;
		case GL_DOUBLE:
			return ApothicDataType::Double;
		case GL_INT:
			return ApothicDataType::Int;
		case GL_UNSIGNED_INT:
			return ApothicDataType::Uint;

		case GL_FLOAT_VEC2:
			return ApothicDataType::fvec2;
		case GL_FLOAT_VEC3:
			return ApothicDataType::fvec3;
		case GL_FLOAT_VEC4:
			return ApothicDataType::fvec4;

		case GL_DOUBLE_VEC2:
			return ApothicDataType::dvec2;
		case GL_DOUBLE_VEC3:
			return ApothicDataType::dvec3;
		case GL_DOUBLE_VEC4:
			return ApothicDataType::dvec4;

		case GL_INT_VEC2:
			return ApothicDataType::ivec2;
		case GL_INT_VEC3:
			return ApothicDataType::ivec3;
		case GL_INT_VEC4:
			return ApothicDataType::ivec4;

		case GL_UNSIGNED_INT_VEC2:
			return ApothicDataType::uivec2;
		case GL_UNSIGNED_INT_VEC3:
			return ApothicDataType::uivec3;
		case GL_UNSIGNED_INT_VEC4:
			return ApothicDataType::uivec4;

		case GL_FLOAT_MAT2:
			return ApothicDataType::fmat2;
		case GL_FLOAT_MAT3:
			return ApothicDataType::fmat3;
		case GL_FLOAT_MAT4:
			return ApothicDataType::fmat4;
		case GL_FLOAT_MAT2x3:
			return ApothicDataType::fmat2x3;
		case GL_FLOAT_MAT3x2:
			return ApothicDataType::fmat3x2;
		case GL_FLOAT_MAT3x4:
			return ApothicDataType::fmat3x4;
		case GL_FLOAT_MAT4x3:
			return ApothicDataType::fmat4x3;

		case GL_DOUBLE_MAT2:
			return ApothicDataType::dmat2;
		case GL_DOUBLE_MAT3:
			return ApothicDataType::dmat3;
		case GL_DOUBLE_MAT4:
			return ApothicDataType::dmat4;
		case GL_DOUBLE_MAT2x3:
			return ApothicDataType::dmat2x3;
		case GL_DOUBLE_MAT3x2:
			return ApothicDataType::dmat3x2;
		case GL_DOUBLE_MAT3x4:
			return ApothicDataType::dmat3x4;
		case GL_DOUBLE_MAT4x3:
			return ApothicDataType::dmat4x3;

		default:
			return ApothicDataType::Nil;
		}

		return ApothicDataType::Nil;
	}

}