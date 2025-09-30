#pragma once
#include <immintrin.h>

/* AVX support */
#ifdef ARGON_SIMD_USE_AVX
#define FLOATSTEPS (unsigned int)(256 / (8 * sizeof(float)))
#define DOUBLESTEPS (unsigned int)(256 / (8 * sizeof(double)))
#define INTSTEPS (unsigned int)(256 / (8 * sizeof(int)))
#define UINTSTEPS (unsigned int)(256 / (8 * sizeof(unsigned int)))

// floats 
typedef __m256 __mXXX;

#define _mmXXX_loadu_ps _mm256_loadu_ps
#define _mmXXX_storeu_ps _mm256_storeu_ps

#define _mmXXX_add_ps _mm256_add_ps
#define _mmXXX_mul_ps _mm256_mul_ps
#define _mmXXX_sub_ps _mm256_sub_ps
#define _mmXXX_div_ps _mm256_div_ps

// doubles 
typedef __m256d __mXXXd;

#define _mmXXX_loadu_pd _mm256_loadu_pd
#define _mmXXX_storeu_pd _mm256_storeu_pd

#define _mmXXX_add_pd _mm256_add_pd
#define _mmXXX_mul_pd _mm256_mul_pd
#define _mmXXX_sub_pd _mm256_sub_pd
#define _mmXXX_div_pd _mm256_div_pd

// integers 
typedef __m256i __mXXXi;

#define _mmXXX_loadu_epi32 _mm256_loadu_epi32
#define _mmXXX_storeu_epi32 _mm256_storeu_epi32

#define _mmXXX_add_epi32 _mm256_add_epi32
#define _mmXXX_mul_epi32 _mm256_mul_epi32
#define _mmXXX_sub_epi32 _mm256_sub_epi32
#define _mmXXX_div_epi32 _mm256_div_epi32

// custom operators
static float _mmXXX_horizontal_sum_ps(const __m256& _A)
{
	__m128 _l = _mm256_extractf128_ps(_A, 0);
	__m128 _h = _mm256_extractf128_ps(_A, 1);
	__m128 _s = _mm_add_ps(_l, _h);
	_s = _mm_hadd_ps(_s, _s);
	_s = _mm_hadd_ps(_s, _s);
	return _mm_cvtss_f32(_s);
}

static double _mmXXX_horizontal_sum_pd(const __m256d& _A)
{
	__m128d _l = _mm256_extractf128_pd(_A, 0);
	__m128d _h = _mm256_extractf128_pd(_A, 1);
	__m128d _s = _mm_add_pd(_l, _h);
	_s = _mm_hadd_pd(_s, _s); /* only does one add because doubles are 2x the size of floats and ints */
	return _mm_cvtsd_f64(_s);
}

static int _mmXXX_horizontal_sum_epi32(const __m256i& _A)
{
	__m128i _l = _mm256_extracti128_si256(_A, 0);
	__m128i _h = _mm256_extracti128_si256(_A, 1);
	__m128i _s = _mm_add_epi32(_l, _h);
	_s = _mm_hadd_epi32(_s, _s);
	_s = _mm_hadd_epi32(_s, _s);
	return _mm_cvtsi128_si32(_s);
}

/* SSE support */
#elif defined ARGON_SIMD_USE_SSE
#define FLOATSTEPS (unsigned int)(128 / (8 * sizeof(float)))
#define DOUBLESTEPS (unsigned int)(128 / (8 * sizeof(double)))
#define INTSTEPS (unsigned int)(128 / (8 * sizeof(int)))
#define UINTSTEPS (unsigned int)(128 / (8 * sizeof(unsigned int)))

// floats
typedef __m128 __mXXX;

#define _mmXXX_loadu_ps _mm_loadu_ps
#define _mmXXX_storeu_ps _mm_storeu_ps

#define _mmXXX_add_ps _mm_add_ps
#define _mmXXX_mul_ps _mm_mul_ps
#define _mmXXX_sub_ps _mm_sub_ps
#define _mmXXX_div_ps _mm_div_ps

// doubles 
typedef __m128d __mXXXd;

#define _mmXXX_loadu_pd _mm_loadu_pd
#define _mmXXX_storeu_pd _mm_storeu_pd

#define _mmXXX_add_pd _mm_add_pd
#define _mmXXX_mul_pd _mm_mul_pd
#define _mmXXX_sub_pd _mm_sub_pd
#define _mmXXX_div_pd _mm_div_pd

// integers 
typedef __m128i __mXXXi;

#define _mmXXX_loadu_epi32 _mm_loadu_epi32
#define _mmXXX_storeu_epi32 _mm_storeu_epi32

#define _mmXXX_add_epi32 _mm_add_epi32
#define _mmXXX_mul_epi32 _mm_mul_epi32
#define _mmXXX_sub_epi32 _mm_sub_epi32
#define _mmXXX_div_epi32 _mm_div_epi32

// custom operators
static float _mmXXX_horizontal_sum_ps(const __m128& _A)
{
	__m128 _s = _mm_hadd_ps(_A, _A);
	_s = _mm_hadd_ps(_s, _s);
	return _mm_cvtss_f32(_s);
}

static double _mmXXX_horizontal_sum_pd(const __m128d& _A)
{
	__m128d _s = _mm_hadd_pd(_A, _A); /* only does one add because doubles are 2x the size of floats and ints */
	return _mm_cvtsd_f64(_s);
}

static int _mmXXX_horizontal_sum_epi32(const __m128i& _A)
{
	__m128i _s = _mm_hadd_epi32(_A, _A);
	_s = _mm_hadd_epi32(_s, _s);
	return _mm_cvtsi128_si32(_s);
}

#endif