#ifndef ARGON_VECTOR_OPS_SIMD_DISABLED
#define ARGON_VECTOR_OPS_SIMD_DISABLED
#define ARGON_SIMD_DISABLED

#include "../../DataTypes/Vector.h"

// Vector macros -> for readablility
#define ARGON_CUSTOM_VECTOR() template<typename _T, unsigned int _L>
#define ARGON_VECTOR ArgonVector<_T, _L>
#define ARGON_VECTOR_IN(name) const ArgonVector<_T, _L>& ##name

namespace argon
{

	ARGON_CUSTOM_VECTOR()
	ARGON_VECTOR ArgonVector_add(ARGON_VECTOR_IN(A), ARGON_VECTOR_IN(B))
	{
		ARGON_VECTOR out{};
		for (unsigned int i{}; i < _L; ++i)
		{
			out[i] = A[i] + B[i];
		}
		return out;
	}

	ARGON_CUSTOM_VECTOR()
	ARGON_VECTOR ArgonVector_mul(ARGON_VECTOR_IN(A), ARGON_VECTOR_IN(B))
	{
		ARGON_VECTOR out {};
		for (unsigned int i{}; i < _L; ++i)
		{
			out[i] = A[i] * B[i];
		}
		return out;
	}

	ARGON_CUSTOM_VECTOR()
	ARGON_VECTOR ArgonVector_sub(ARGON_VECTOR_IN(A), ARGON_VECTOR_IN(B))
	{
		ARGON_VECTOR out {};
		for (unsigned int i{}; i < _L; ++i)
		{
			out[i] = A[i] - B[i];
		}
		return out;
	}

	ARGON_CUSTOM_VECTOR()
	ARGON_VECTOR ArgonVector_div(ARGON_VECTOR_IN(A), ARGON_VECTOR_IN(B))
	{
		ARGON_VECTOR out {};
		for (unsigned int i{}; i < _L; ++i)
		{
			out[i] = A[i] / B[i];
		}
		return out;
	}

	ARGON_CUSTOM_VECTOR()
	_T ArgonVector_dot(ARGON_VECTOR_IN(A), ARGON_VECTOR_IN(B))
	{
		_T sum = {};
		for (unsigned int i{}; i < _L; ++i)
		{
			sum += A[i] * B[i];
		}
		return sum;
	}

    ARGON_CUSTOM_VECTOR()
    _T ArgonVector_distance(ARGON_VECTOR_IN(A), ARGON_VECTOR_IN(B))
    {
        _T sum = {};
        for (unsigned int i{}; i < _L; ++i)
            sum += pow(((float)A[i] - (float)B[i]), 2)
        return sqrt(sum);
    }

}

#endif