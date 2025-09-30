/*
	Argon Math util Library --- Rex Bradbury - 8/29/2025

	HOW TO IMPLEMENT -> include <Argon.h> alongside select parameters.
	Parameters:
		* ARGON_SIMD_ENABLED     -> Sets SIMD Operations as enabled
		* ARGON_SIMD_DISABLED    -> Uses linear operations instead of SIMD (Only use if hardware is incompatable with the current version of Argon.)
		* ARGON_SIMD_USE_SSE     -> Switches to using SSE's 128-bit wide registers for SIMD operations.
		* ARGON_SIMD_USE_AVX     -> Switches to using AVX's 256-bit wide registers for SIMD operations.
	Example:
		#define ARGON_SIMD_ENABLED
		#define ARGON_SIMD_USE_AVX
		#include <Argon.h>

	=< TODO >============================================================================================================================================================
		* vector dot product -> sigma0->d(Ad * Bd)                                                                 | Added: < 08/29/2025 > | complete: < 08/30/2025 > |  
		* Matrices -> use float* or float**? new or malloc?	-> float*                  		                       | Added: < 08/29/2025 > | complete: < 08/30/2025 > |
		* Matrix operations -> multiplication												                       | Added: < 08/29/2025 > | complete: < 08/31/2025 > |
		* Transform matrices -> translation, scalar, rotation, orthographic, perspective	                       | Added: < 08/29/2025 > | complete: < xx/xx/xxxx > | <- c
		* Fix int multiplication for SIMD skipping values -> likely wrong function                                 | Added: < 08/29/2025 > | complete: < xx/xx/xxxx > |
		* Add wrappers for SIMD intrinisc to automaticaly use the correct datatype                                 | Added: < 08/29/2025 > | complete: < xx/xx/xxxx > |
	=< V0.0 >============================================================================================================================================================
		Added<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
		* Vectors                                                                                                  | Implemented: < 08/29/2025 >					  |
		* SIMD Toggle													                                           | Implemented: < 08/29/2025 >					  |
		* Basic SIMD/non-SIMD operators for vectors	+*-/dot                                                        | Implemented: < 08/29/2025 >					  |
		* support for SSE and AVX           							                                           | Implemented: < 08/29/2025 >					  |
		* generic vectors for float, double, int, uint vector type and their respected degrees                     | Implemented: < 08/29/2025 >					  |
		Notes<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>														                           
		* I was given coffee.                                                                                      | Writen: < 08/29/2025 >                           |
	=====================================================================================================================================================================
*/

#ifndef ARGON_IMPLEMENTATION
#define ARGON_IMPLEMENTATION

/* Data Types ----- */
#include "Argon/DataTypes/Vector.h"
#include "Argon/DataTypes/Matrix.h"
#include "Argon/util/types.h"

/* Custom Types ----- */
#include "Argon/Transforms/MatrixTransforms.cpp"

/* Operator overloads ----- */
#include "Argon/Operations/Overloads.h"

#endif