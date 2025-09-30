#pragma once
#include <memory>
#include <iostream>

template<typename _T>
void deletep(_T* v)
{
	delete v;
}
template<typename _T>
void deletep(_T v)
{
}

namespace argon
{

	/* Custom Vector Class */
	template<typename _T, unsigned int _L>
	class ArgonVector
	{
	public:
		ArgonVector()
			: m_Values(new _T[_L]{})
		{} /* empty instantiations will allocate the desired amount of memory */
		ArgonVector(_T* vals) 
			: m_Values(vals)
		{} /* Casts a pointer of values to a vector */
		template<typename... _inits>
		ArgonVector(_inits... vals) 
			: m_Values(new _T[_L]{ (_T)vals... })
		{} /* initialize all of the values that are apart of the vector */

		~ArgonVector()
		{
			for (unsigned int i{}; i < _L; ++i)
				deletep<_T>(m_Values[i]);
			m_Values = nullptr;
		}

		/* Helper functions ----- */
		inline const unsigned int Length() const { return m_Length; }
		inline _T* Data() const { return m_Values; }
		inline const _T operator[](unsigned int index) const { return m_Values[index]; }
		inline _T& operator[](unsigned int index) { return m_Values[index]; }
		inline _T* operator()(unsigned int index) const { return &m_Values[index]; }
		/* ---- Helper functions */

	private:
		_T* m_Values;
		unsigned int m_Length = _L;
	};

	/* vector printing */
	template<typename _T, unsigned int _L>
	static std::ostream& operator<<(std::ostream& stream, const argon::ArgonVector<_T, _L>& vec)
	{
		stream << "| ";
		for (unsigned int i{}; i < _L; ++i)
		{
			stream << vec[i] << " ";
		}
		return stream << "|";
	}

	typedef ArgonVector<float, 2>           vec2;
	typedef ArgonVector<float, 3>           vec3;
	typedef ArgonVector<float, 4>           vec4;

	typedef ArgonVector<double, 2>          dvec2;
	typedef ArgonVector<double, 3>          dvec3;
	typedef ArgonVector<double, 4>          dvec4;

	typedef ArgonVector<int, 2>             ivec2;
	typedef ArgonVector<int, 3>             ivec3;
	typedef ArgonVector<int, 4>             ivec4;

	typedef ArgonVector<unsigned int, 2>    uivec2;
	typedef ArgonVector<unsigned int, 3>    uivec3;
	typedef ArgonVector<unsigned int, 4>    uivec4;
}