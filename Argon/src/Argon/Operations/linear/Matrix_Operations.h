#ifndef ARGON_MATRIX_OPS_SIMD_DISABLED
#define ARGON_MATRIX_OPS_SIMD_DISABLED
#define ARGON_SIMD_DISABLED

#include "../../DataTypes/Matrix.h"
#include "Vector_Operations.h"

namespace argon
{

	template<typename _T, unsigned int _rows, unsigned int _cols>
	ArgonMatrix<_T, _rows, _cols> ArgonMatrix_mul(const ArgonMatrix<_T, _rows, _cols>& A, const ArgonMatrix<_T, _cols, _rows>& B)
	{
		ArgonMatrix<_T, _rows, _cols> out{};
		for (unsigned int ix{}; ix < _rows; ++ix)
		{
			auto c_Row = A.GetRow(ix);
			for (unsigned int iy{}; iy < _cols; ++iy)
			{
				auto c_Col = B.GetCol(iy);
				out(ix, iy) = ArgonVector_dot(c_Row, c_Col);
			}
		}
		return out;
	}

	template<typename _T, unsigned int _rows, unsigned int _cols>
	ArgonVector<_T, _rows> ArgonMatrix_transform_ArgonVector(const ArgonMatrix<_T, _rows, _cols>& mat, const ArgonVector<_T, _cols>& vec)
	{
		ArgonVector<_T, _rows> out{};
		for (unsigned int i{}; i < _rows; ++i)
		{
			auto c_Row = mat.GetRow(i);
			out[i] = ArgonVector_dot(c_Row, vec);
		}
		return out;
	}

}

#endif