#pragma once
#include <memory>
#include <iostream>

#include "Vector.h"

namespace argon
{

	template<typename _T, unsigned int _rows, unsigned int _cols>
	class ArgonMatrix
	{
	public:
		ArgonMatrix() 
			: m_Size(_rows* _cols)
			, m_Values((_T*)malloc(m_Size * sizeof(_T)))
		{}
		ArgonMatrix(_T* vals) 
			: m_Size(_rows* _cols)
			, m_Values(vals)
		{}
		template<typename... _inits>
		ArgonMatrix(_inits... vals) 
			: m_Size(_rows* _cols)
			, m_Values(new _T[m_Size]{ (_T)vals... })
		{}

		~ArgonMatrix()
		{
			for (unsigned int i{}; i < m_Size; ++i)
				deletep<_T>(m_Values[i]);
			m_Values = nullptr;
		}

		/* Helper functions ----- */
		inline const unsigned int Size() const { return m_Size; }
		inline const unsigned int Rows() const { return m_Rows; }
		inline const unsigned int Cols() const { return m_Cols; }
		inline _T* Data() const { return m_Values; }
		inline const _T operator()(unsigned int row, unsigned int col) const { return m_Values[(m_Cols * row) + col]; }
		inline _T& operator()(unsigned int row, unsigned int col) { return m_Values[(m_Cols * row) + col]; }
		inline _T* operator[](unsigned int row) const { return &m_Values[m_Cols * row]; }

		ArgonVector<_T, _cols> GetRow(unsigned int row) const
		{
			float* out = (float*)malloc(_cols * sizeof(_T)); /* memory is freed by vector class */
			for (unsigned int i{}; i < _cols; ++i)
				out[i] = m_Values[(m_Cols * row) + i];
			return out;
		}
		ArgonVector<_T, _rows> GetCol(unsigned int col) const
		{
			float* out = (float*)malloc(_rows * sizeof(_T));
			for (unsigned int i{}; i < _rows; ++i)
				out[i] = m_Values[(m_Cols * i) + col];
			return out;
		}
		/* ----- Helper functions */

	private:
		_T* m_Values;
		unsigned int m_Rows = _rows;
		unsigned int m_Cols = _cols;
		unsigned int m_Size;
	};

	/* matrix printing */
	template<typename _T, unsigned int _rows, unsigned int _cols>
	std::ostream& operator<<(std::ostream& stream, const ArgonMatrix<_T, _rows, _cols>& mat)
	{
		for (unsigned int ix{}; ix < _rows; ++ix)
		{
			stream << "| ";
			for (unsigned int iy{}; iy < _cols; ++iy)
			{
				stream << mat(ix, iy) << " ";
			}
			stream << "| ";
		}
		return stream;
	}
	

	typedef ArgonMatrix<float, 2, 2> mat2;
	typedef ArgonMatrix<float, 3, 3> mat3;
	typedef ArgonMatrix<float, 4, 4> mat4;
	typedef ArgonMatrix<float, 2, 3> mat2x3;
	typedef ArgonMatrix<float, 3, 2> mat3x2;
	typedef ArgonMatrix<float, 3, 4> mat3x4;
	typedef ArgonMatrix<float, 4, 3> mat4x3;

	typedef ArgonMatrix<double, 2, 2> dmat2;
	typedef ArgonMatrix<double, 3, 3> dmat3;
	typedef ArgonMatrix<double, 4, 4> dmat4;
	typedef ArgonMatrix<double, 2, 3> dmat2x3;
	typedef ArgonMatrix<double, 3, 2> dmat3x2;
	typedef ArgonMatrix<double, 3, 4> dmat3x4;
	typedef ArgonMatrix<double, 4, 3> dmat4x3;

	typedef ArgonMatrix<int, 2, 2> imat2;
	typedef ArgonMatrix<int, 3, 3> imat3;
	typedef ArgonMatrix<int, 4, 4> imat4;
	typedef ArgonMatrix<int, 2, 3> imat2x3;
	typedef ArgonMatrix<int, 3, 2> imat3x2;
	typedef ArgonMatrix<int, 3, 4> imat3x4;
	typedef ArgonMatrix<int, 4, 3> imat4x3;

	typedef ArgonMatrix<unsigned int, 2, 2> uimat2;
	typedef ArgonMatrix<unsigned int, 3, 3> uimat3;
	typedef ArgonMatrix<unsigned int, 4, 4> uimat4;
	typedef ArgonMatrix<unsigned int, 2, 3> uimat2x3;
	typedef ArgonMatrix<unsigned int, 3, 2> uimat3x2;
	typedef ArgonMatrix<unsigned int, 3, 4> uimat3x4;
	typedef ArgonMatrix<unsigned int, 4, 3> uimat4x3;

}