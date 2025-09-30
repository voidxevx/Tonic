#pragma once
#include "../DataTypes/Matrix.h"
#include "../DataTypes/Vector.h"
#include "../util/types.h"

namespace argon
{

	template<typename _T>
	static ArgonMatrix<_T, 2, 2> scalar_mat2(_T base)
	{
		return new _T[4]{
			base, 0,
			0, base,
		};
	}

	template<typename _T>
	static ArgonMatrix<_T, 2, 2> scalar_mat2(const ArgonVector<_T, 2>& base)
	{
		return new _T[4]{
			base[0], 0,
			0, base[1],
		};
	}

	template<typename _T>
	static ArgonMatrix<_T, 3, 3> scalar_mat3(_T base)
	{
		return new _T[9]{
			base, 0, 0,
			0, base, 0,
			0, 0, base,
		};
	}

	template<typename _T>
	static ArgonMatrix<_T, 3, 3> scalar_mat3(const ArgonVector<_T, 3>& base)
	{
		return new _T[9]{
			base[0], 0, 0,
			0, base[1], 0,
			0, 0, base[2],
		};
	}

	template<typename _T>
	static ArgonMatrix<_T, 4, 4> scalar_mat4(_T base)
	{
		return new _T[16]{
			base, 0, 0, 0,
			0, base, 0, 0,
			0, 0, base, 0,
			0, 0, 0, base,
		};
	}

	template<typename _T>
	static ArgonMatrix<_T, 4, 4> scalar_mat4(const ArgonVector<_T, 4>& base)
	{
		return new _T[16]{
			base[0], 0, 0, 0,
			0, base[1], 0, 0,
			0, 0, base[2], 0,
			0, 0, 0, base[3],
		};
	}

	template<typename _T> 
	static ArgonMatrix<_T, 3, 3> translation_mat3(const ArgonVector<_T, 2>& base)
	{
		return new _T[9]{
			1, 0, base[0],
			0, 1, base[1],
			0, 0, 1,
		};
	}

	template<typename _T>
	static ArgonMatrix<_T, 4, 4>* translation_mat4(const ArgonVector<_T, 3>& base)
	{
		return new ArgonMatrix<_T, 4, 4>{
				new _T[16]{
				1, 0, 0, base[0],
				0, 1, 0, base[1],
				0, 0, 1, base[2],
				0, 0, 0, 1,
			}
		};
	}

	// rotations 
	static ArgonMatrix<float, 2, 2> rotation_mat2(int deg)
	{
		return new float[4] {
			cosf(Radians<float>(deg)), -sinf(Radians<float>(deg)),
			sinf(Radians<float>(deg)), cosf(Radians<float>(deg)),
		};
	}

	static ArgonMatrix<double, 2, 2> rotation_dmat2(int deg)
	{
		return new double[4] {
			cos(Radians<double>(deg)), -sin(Radians<double>(deg)),
			sin(Radians<double>(deg)), cos(Radians<double>(deg)),
		};
	}

	static ArgonMatrix<float, 3, 3> rotation2D_mat3(int deg)
	{
		return new float[9] {
			cosf(Radians<float>(deg)), -sinf(Radians<float>(deg)), 0,
			sinf(Radians<float>(deg)), cosf(Radians<float>(deg)), 0,
			0, 0, 1,
		};
	}

	static ArgonMatrix<double, 3, 3> rotation2D_dmat3(int deg)
	{
		return new double[9] {
			cos(Radians<double>(deg)), -sin(Radians<double>(deg)), 0,
			sin(Radians<double>(deg)), cos(Radians<double>(deg)), 0,
			0, 0, 1,
		};
	}


	static ArgonMatrix<float, 3, 3> rotation3D_x_mat3(int deg)
	{
		return new float[9] {
			1, 0, 0,
			0, cosf(Radians<float>(deg)), -sinf(Radians<float>(deg)),
			0, sinf(Radians<float>(deg)), cosf(Radians<float>(deg)),
		};
	}

	static ArgonMatrix<float, 3, 3> rotation3D_y_mat3(int deg)
	{
		return new float[9] {
			cosf(Radians<float>(deg)), 0, sinf(Radians<float>(deg)),
			0, 1, 0,
			-sinf(Radians<float>(deg)), 0, cosf(Radians<float>(deg)),
		};
	}

	static ArgonMatrix<float, 3, 3> rotation3D_z_mat3(int deg)
	{
		return new float[9] {
			cosf(Radians<float>(deg)), -sinf(Radians<float>(deg)), 0,
			sinf(Radians<float>(deg)), cosf(Radians<float>(deg)), 0,
			0, 0, 1,
		};
	}



	static ArgonMatrix<double, 3, 3> rotation3D_x_dmat3(int deg)
	{
		return new double[9] {
			1, 0, 0,
			0, cos(Radians<double>(deg)), -sin(Radians<double>(deg)),
			0, sin(Radians<double>(deg)), cos(Radians<double>(deg)),
		};
	}

	static ArgonMatrix<double, 3, 3> rotation3D_y_dmat3(int deg)
	{
		return new double[9] {
			cos(Radians<double>(deg)), 0, sin(Radians<double>(deg)),
			0, 1, 0,
			-sin(Radians<double>(deg)), 0, cos(Radians<double>(deg)),
		};
	}

	static ArgonMatrix<double, 3, 3> rotation3D_z_dmat3(int deg)
	{
		return new double[9] {
			cos(Radians<double>(deg)), -sin(Radians<double>(deg)), 0,
			sin(Radians<double>(deg)), cos(Radians<double>(deg)), 0,
			0, 0, 1,
		};
	}



	static ArgonMatrix<float, 4, 4> rotation3D_x_mat4(int deg)
	{
		return new float[16] {
			1, 0, 0, 0,
			0, cosf(Radians<float>(deg)), -sinf(Radians<float>(deg)), 0,
			0, sinf(Radians<float>(deg)), cosf(Radians<float>(deg)), 0,
			0, 0, 0, 1,
		};
	}

	static ArgonMatrix<float, 4, 4> rotation3D_y_mat4(int deg)
	{
		return new float[16] {
			cosf(Radians<float>(deg)), 0, sinf(Radians<float>(deg)), 0,
			0, 1, 0, 0,
			-sinf(Radians<float>(deg)), 0, cosf(Radians<float>(deg)), 0,
			0, 0, 0, 1,
		};
	}

	static ArgonMatrix<float, 4, 4> rotation3D_z_mat4(int deg)
	{
		return new float[16] {
			cosf(Radians<float>(deg)), -sinf(Radians<float>(deg)), 0, 0,
			sinf(Radians<float>(deg)), cosf(Radians<float>(deg)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
	}



	static ArgonMatrix<double, 4, 4> rotation3D_x_dmat4(int deg)
	{
		return new double[16] {
			1, 0, 0, 0,
			0, cos(Radians<double>(deg)), -sin(Radians<double>(deg)), 0,
			0, sin(Radians<double>(deg)), cos(Radians<double>(deg)), 0,
			0, 0, 0, 1,
		};
	}

	static ArgonMatrix<double, 4, 4> rotation3D_y_dmat4(int deg)
	{
		return new double[16] {
			cos(Radians<double>(deg)), 0, sin(Radians<double>(deg)), 0,
			0, 1, 0, 0,
			-sin(Radians<double>(deg)), 0, cos(Radians<double>(deg)), 0,
			0, 0, 0, 1,
		};
	}

	static ArgonMatrix<double, 4, 4> rotation3D_z_dmat4(int deg)
	{
		return new double[16] {
			cos(Radians<double>(deg)), -sin(Radians<double>(deg)), 0, 0,
			sin(Radians<double>(deg)), cos(Radians<double>(deg)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
	}

    static ArgonMatrix<float, 4, 4>* orthographicViewMatrix(float left, float right, float bottom, float top, float far, float near)
    {
		return new mat4{
			new float[16]{
				2 / (right - left), 0, 0, 0,
				0, 2 / (top - bottom), 0, 0,
				0, 0, -2 / (far - near), 0,
				(left + right) / (left - right), (top + bottom) / (bottom - top), (near + far) / (near - far), 1
			}
		};
    }
    /* i think n is the distance between the camera and the vertex */
    static ArgonMatrix<float, 4, 4> perspectiveProjectionMatrix(float left, float right, float top, float bottom, float near, float far, float distance)
    {
        return new float[16]{
            (2 * distance) / (right - left), 0, (right + left) / (right - left), 0,
            0, (2 * distance) / (top - bottom), (top + bottom) / (top - bottom), 0,
            0, 0, -(far + near) / (far - near), (-2 * far * distance) / (far - near), 
            0, 0, -1, 0,

        };
    }
}