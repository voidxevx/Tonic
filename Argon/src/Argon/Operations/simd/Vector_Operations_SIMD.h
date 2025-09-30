#ifndef ARGON_VECTOR_OPS_SIMD_ENABLED
#define ARGON_VECTOR_OPS_SIMD_ENABLED
#define ARGON_SIMD_ENABLED

#include "../../DataTypes/Vector.h"
#include "ArgonSIMD.h"


#define ARGON_EXPANDABLE_VECTOR()            template<unsigned int _L>
#define VECTOR_OPERATION_SETUP(type, steps)  unsigned int SpaceAllocated = (unsigned int)ceil((float)_L / (float)steps) * steps;\
											 type* data = (type*) malloc(SpaceAllocated * sizeof(type)); /* allocates the correct amount of memory */
#define VECTOR_OPERATION_CLEANUP(type)       type* out = (type*) std::realloc(data, _L * sizeof(type)); /* reallocates the output to the initial size freeing any extra data*/\
										     data = nullptr;

/* prevents trash values during horizontal sum */
#define VECTOR_HORIZONTAL_OPERATION_SETUP(type, steps) unsigned int MemoryAllocated = (unsigned int)ceil((float)_L / (float)steps) * steps; /* Calculates the amount of memory to allocate */\
													  type* A_cpy = (type*)calloc(MemoryAllocated, sizeof(type)); /* allocates the amount as 0 */\
													  type* B_cpy = (type*)calloc(MemoryAllocated, sizeof(type));\
													  memcpy(A_cpy, A.Data(), _L * sizeof(type)); /* copies the correct data leaving any overhang as 0 */\
													  memcpy(B_cpy, B.Data(), _L * sizeof(type));
#define VECTOR_HORIZONTAL_OPERATION_CLEANUP() free(A_cpy);\
											  A_cpy = nullptr;\
											  free(B_cpy);\
											  B_cpy = nullptr;

namespace argon
{


	/* --------- float operations ---------- */
	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<float, _L> ArgonVector_add_SIMD(const ArgonVector<float, _L>& A, const ArgonVector<float, _L>& B)
	{
		VECTOR_OPERATION_SETUP(float, FLOATSTEPS)

		__mXXX _A, _B, _res;

		for (unsigned int i{}; i < _L; i += FLOATSTEPS)
		{
			_A = _mmXXX_loadu_ps(A(i));
			_B = _mmXXX_loadu_ps(B(i));

			_res = _mmXXX_add_ps(_A, _B);

			_mmXXX_storeu_ps(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(float)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<float, _L> ArgonVector_mul_SIMD(const ArgonVector<float, _L>& A, const ArgonVector<float, _L>& B)
	{
		VECTOR_OPERATION_SETUP(float, FLOATSTEPS)

		__mXXX _A, _B, _res;

		for (unsigned int i{}; i < _L; i += FLOATSTEPS)
		{
			_A = _mmXXX_loadu_ps(A(i));
			_B = _mmXXX_loadu_ps(B(i));

			_res = _mmXXX_mul_ps(_A, _B);

			_mmXXX_storeu_ps(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(float)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<float, _L> ArgonVector_sub_SIMD(const ArgonVector<float, _L>& A, const ArgonVector<float, _L>& B)
	{
		VECTOR_OPERATION_SETUP(float, FLOATSTEPS)

		__mXXX _A, _B, _res;

		for (unsigned int i{}; i < _L; i += FLOATSTEPS)
		{
			_A = _mmXXX_loadu_ps(A(i));
			_B = _mmXXX_loadu_ps(B(i));

			_res = _mmXXX_sub_ps(_A, _B);

			_mmXXX_storeu_ps(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(float)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<float, _L> ArgonVector_div_SIMD(const ArgonVector<float, _L>& A, const ArgonVector<float, _L>& B)
	{
		VECTOR_OPERATION_SETUP(float, FLOATSTEPS)

		__mXXX _A, _B, _res;

		for (unsigned int i{}; i < _L; i += FLOATSTEPS)
		{
			_A = _mmXXX_loadu_ps(A(i));
			_B = _mmXXX_loadu_ps(B(i));

			_res = _mmXXX_div_ps(_A, _B);

			_mmXXX_storeu_ps(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(float)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	float ArgonVector_dot_SIMD(const ArgonVector<float, _L>& A, const ArgonVector<float, _L>& B)
	{
		float sum{};
		VECTOR_HORIZONTAL_OPERATION_SETUP(float, FLOATSTEPS)
		
		__mXXX _A, _B, _res;

		for (unsigned int i{}; i < _L; i += FLOATSTEPS)
		{
			_A = _mmXXX_loadu_ps(&A_cpy[i]);
			_B = _mmXXX_loadu_ps(&B_cpy[i]);

			_res = _mmXXX_mul_ps(_A, _B);

			sum += _mmXXX_horizontal_sum_ps(_res);
		}

		VECTOR_HORIZONTAL_OPERATION_CLEANUP()

		return sum;
	}



    ARGON_EXPANDABLE_VECTOR()
    float ArgonVector_Distance_SIMD(const ArgonVector<float, _L>& A, const ArgonVector<float, _L>& B)
    {
        float sum{};
        VECTOR_HORIZONTAL_OPERATION_SETUP(float, FLOATSTEPS)

        __mXXX _A, _B, _res;

        for (unsigned int i{}; i < _L; i += FLOATSTEPS)
        {
            _A = _mmXXX_loadu_ps(&A_cpy[i]);
            _B = _mmXXX_loadu_ps(&B_cpy[i]);

            _res = _mmXXX_sub_ps(_A, _B); //         (n1 - n2)
            _res = _mmXXX_mul_ps(_res, _res);//      (n1 - n2) ^ 2

            sum += _mmXXX_horizontal_sum_ps(_res);// (n1i - n2i)^2 + (n1i+1 - n2i+1)^2 ...
        }

        VECTOR_HORIZONTAL_OPERATION_CLEANUP()

        return sum;
    }



	/* --------- double operations ---------- */
	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<double, _L> ArgonVector_add_SIMD(const ArgonVector<double, _L>& A, const ArgonVector<double, _L>& B)
	{
		VECTOR_OPERATION_SETUP(double, DOUBLESTEPS)

		__mXXXd _A, _B, _res;

		for (unsigned int i{}; i < _L; i += DOUBLESTEPS)
		{
			_A = _mmXXX_loadu_pd(A(i));
			_B = _mmXXX_loadu_pd(B(i));

			_res = _mmXXX_add_pd(_A, _B);

			_mmXXX_storeu_pd(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(double)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<double, _L> ArgonVector_mul_SIMD(const ArgonVector<double, _L>& A, const ArgonVector<double, _L>& B)
	{
		VECTOR_OPERATION_SETUP(double, DOUBLESTEPS)

		__mXXXd _A, _B, _res;

		for (unsigned int i{}; i < _L; i += DOUBLESTEPS)
		{
			_A = _mmXXX_loadu_pd(A(i));
			_B = _mmXXX_loadu_pd(B(i));

			_res = _mmXXX_mul_pd(_A, _B);

			_mmXXX_storeu_pd(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(double)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<double, _L> ArgonVector_sub_SIMD(const ArgonVector<double, _L>& A, const ArgonVector<double, _L>& B)
	{
		VECTOR_OPERATION_SETUP(double, DOUBLESTEPS)

		__mXXXd _A, _B, _res;

		for (unsigned int i{}; i < _L; i += DOUBLESTEPS)
		{
			_A = _mmXXX_loadu_pd(A(i));
			_B = _mmXXX_loadu_pd(B(i));

			_res = _mmXXX_sub_pd(_A, _B);

			_mmXXX_storeu_pd(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(double)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<double, _L> ArgonVector_div_SIMD(const ArgonVector<double, _L>& A, const ArgonVector<double, _L>& B)
	{
		VECTOR_OPERATION_SETUP(double, DOUBLESTEPS)

		__mXXXd _A, _B, _res;

		for (unsigned int i{}; i < _L; i += DOUBLESTEPS)
		{
			_A = _mmXXX_loadu_pd(A(i));
			_B = _mmXXX_loadu_pd(B(i));

			_res = _mmXXX_div_pd(_A, _B);

			_mmXXX_storeu_pd(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(double)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	double ArgonVector_dot_SIMD(const ArgonVector<double, _L>& A, const ArgonVector<double, _L>& B)
	{
		double sum{};
		VECTOR_HORIZONTAL_OPERATION_SETUP(double, DOUBLESTEPS)

		__mXXXd _A, _B, _res;

		for (unsigned int i{}; i < _L; i += DOUBLESTEPS)
		{
			_A = _mmXXX_loadu_pd(&A_cpy[i]);
			_B = _mmXXX_loadu_pd(&B_cpy[i]);

			_res = _mmXXX_mul_pd(_A, _B);

			sum += _mmXXX_horizontal_sum_pd(_res);
		}

		VECTOR_HORIZONTAL_OPERATION_CLEANUP()

		return sum;
	}

    ARGON_EXPANDABLE_VECTOR()
    double ArgonVector_distance_SIMD(const ArgonVector<double, _L>& A, const ArgonVector<double, _L>& B)
    {
        double sum{};
        VECTOR_HORIZONTAL_OPERATION_SETUP(double, DOUBLESTEPS)

        __mXXXd _A, _B, _res;

        for (unsigned int i{}; i < _L; i += DOUBLESTEPS)
        {
            _A = _mmXXX_loadu_pd(&A_cpy[i]);
            _B = _mmXXX_loadu_pd(&B_cpy[i]);

            _res = _mmXXX_sub_pd(_A, _B);
            _res = _mmXXX_mul_pd(_res, _res);
            
            sum += _mmXXX_horizontal_sum_pd(_res);
        }

        VECTOR_HORIZONTAL_OPERATION_CLEANUP()

        return sqrt(sum);
    }



	/* --------- integer operations ---------- */
	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<int, _L> ArgonVector_add_SIMD(const ArgonVector<int, _L>& A, const ArgonVector<int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(int, INTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += INTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_add_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<int, _L> ArgonVector_mul_SIMD(const ArgonVector<int, _L>& A, const ArgonVector<int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(int, INTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += INTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_mul_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<int, _L> ArgonVector_sub_SIMD(const ArgonVector<int, _L>& A, const ArgonVector<int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(int, INTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += INTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_sub_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<int, _L> ArgonVector_div_SIMD(const ArgonVector<int, _L>& A, const ArgonVector<int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(int, INTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += INTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_div_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	int ArgonVector_dot_SIMD(const ArgonVector<int, _L>& A, const ArgonVector<int, _L>& B)
	{
		int sum = {};
		VECTOR_HORIZONTAL_OPERATION_SETUP(int, INTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += INTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(&A_cpy[i]);
			_B = _mmXXX_loadu_epi32(&B_cpy[i]);

			_res = _mmXXX_mul_epi32(_A, _B);

			sum += _mmXXX_horizontal_sum_epi32(_res);
		}

		VECTOR_HORIZONTAL_OPERATION_CLEANUP()

		return sum;
	}

    ARGON_EXPANDABLE_VECTOR()
    int ArgonVector_distance_SIMD(const ArgonVector<int, _L>& A, const ArgonVector<int, _L>& B)
    {
        int sum{};
        VECTOR_HORIZONTAL_OPERATION_SETUP(int, INTSTEPS)

        __mXXXi _A, _B, _res;

        for (unsigned int i{}; i < _L; ++i)
        {
            _A = _mmXXX_loadu_epi32(&A_cpy[i]);
            _B = _mmXXX_loadu_epi32(&B_cpy[i]);

            _res = _mmXXX_sub_epi32(_A, _B);
            _res = _mmXXX_mul_epi32(_res, _res);

            sum += _mmXXX_horizontal_sum_epi32(_res);
        }

        VECTOR_HORIZONTAL_OPERATION_CLEANUP()

        return sqrt(sum);
    }



	// unsigned int
	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<unsigned int, _L> ArgonVector_add_SIMD(const ArgonVector<unsigned int, _L>& A, const ArgonVector<unsigned int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(unsigned int, UINTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += UINTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_add_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(unsigned int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<unsigned int, _L> ArgonVector_mul_SIMD(const ArgonVector<unsigned int, _L>& A, const ArgonVector<unsigned int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(unsigned int, UINTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += UINTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_mul_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(unsigned int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<unsigned int, _L> ArgonVector_sub_SIMD(const ArgonVector<unsigned int, _L>& A, const ArgonVector<unsigned int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(unsigned int, UINTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += UINTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_sub_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(unsigned int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	ArgonVector<unsigned int, _L> ArgonVector_div_SIMD(const ArgonVector<unsigned int, _L>& A, const ArgonVector<unsigned int, _L>& B)
	{
		VECTOR_OPERATION_SETUP(unsigned int, UINTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += UINTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(A(i));
			_B = _mmXXX_loadu_epi32(B(i));

			_res = _mmXXX_div_epi32(_A, _B);

			_mmXXX_storeu_epi32(&data[i], _res);
		}

		VECTOR_OPERATION_CLEANUP(unsigned int)
		return out;
	}

	ARGON_EXPANDABLE_VECTOR()
	unsigned int ArgonVector_dot_SIMD(const ArgonVector<unsigned int, _L>& A, const ArgonVector<unsigned int, _L>& B)
	{
		unsigned int sum = {};
		VECTOR_HORIZONTAL_OPERATION_SETUP(unsigned int, UINTSTEPS)

		__mXXXi _A, _B, _res;

		for (unsigned int i{}; i < _L; i += UINTSTEPS)
		{
			_A = _mmXXX_loadu_epi32(&A_cpy[i]);
			_B = _mmXXX_loadu_epi32(&B_cpy[i]);

			_res = _mmXXX_mul_epi32(_A, _B);

			sum += _mmXXX_horizontal_sum_epi32(_res);
		}

		VECTOR_HORIZONTAL_OPERATION_CLEANUP()

		return sum;
	}


    ARGON_EXPANDABLE_VECTOR()
    unsigned int ARgonVector_distance_SIMD(const ArgonVector<unsigned int, _L>& A, const ArgonVector<unsigned int, _L>& B)
    {
        unsigned int sum{};
        VECTOR_HORIZONTAL_OPERATION_SETUP(unsigned int, UINTSTEPS)

        __mXXXi _A, _B, _res;

        for (unsigned int i{}; i < _L; i += UINTSTEPS)
        {
            _A = _mmXXX_loadu_epi32(&A_cpy[i]);
            _B = _mmXXX_loadu_epi32(&B_cpy[i]);

            _res = _mmXXX_sub_epi32(_A, _B);
            _res = _mmXXX_mul_epi32(_res, _res);

            sum += _mmXXX_horizontal_sum_epi32(_res);
        }

        VECTOR_HORIZONTAL_OPERATION_CLEANUP()

        return sqrt(sum);
    }

    

}

#endif