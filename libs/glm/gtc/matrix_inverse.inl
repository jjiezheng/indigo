///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2005-12-21
// Updated : 2010-12-13
// Licence : This source is under MIT License
// File    : glm/gtc/matrix_inverse.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtc{
namespace matrix_inverse
{
	template <typename T> 
	inline detail::tmat3x3<T> affineInverse
	(
		detail::tmat3x3<T> const & m
	)
	{
		detail::tmat3x3<T> Result(m);
		Result[2] = detail::tvec3<T>(0, 0, 1);
		Result = transpose(Result);
		detail::tvec3<T> Translation = Result * detail::tvec3<T>(-detail::tvec2<T>(m[2]), m[2][2]);
		Result[2] = Translation;
		return Result;
	}

	template <typename T> 
	inline detail::tmat4x4<T> affineInverse
	(
		detail::tmat4x4<T> const & m
	)
	{
		detail::tmat4x4<T> Result(m);
		Result[3] = detail::tvec4<T>(0, 0, 0, 1);
		Result = transpose(Result);
		detail::tvec4<T> Translation = Result * detail::tvec4<T>(-detail::tvec3<T>(m[3]), m[3][3]);
		Result[3] = Translation;
		return Result;
	}

	template <typename valType> 
	inline detail::tmat2x2<valType> inverseTranspose(
		detail::tmat2x2<valType> const & m)
	{
		valType Determinant = m[0][0] * m[1][1] - m[1][0] * m[0][1];

		detail::tmat2x2<valType> Inverse(
			+ m[1][1] / Determinant,
			- m[0][1] / Determinant,
			- m[1][0] / Determinant, 
			+ m[0][0] / Determinant);

		return Inverse;
	}

	template <typename valType> 
	inline detail::tmat3x3<valType> inverseTranspose(
		detail::tmat3x3<valType> const & m)
	{
		valType Determinant = 
			+ m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
			- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
			+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

		detail::tmat3x3<valType> Inverse;
		Inverse[0][0] = + (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
		Inverse[0][1] = - (m[1][0] * m[2][2] - m[2][0] * m[1][2]);
		Inverse[0][2] = + (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
		Inverse[1][0] = - (m[0][1] * m[2][2] - m[2][1] * m[0][2]);
		Inverse[1][1] = + (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
		Inverse[1][2] = - (m[0][0] * m[2][1] - m[2][0] * m[0][1]);
		Inverse[2][0] = + (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		Inverse[2][1] = - (m[0][0] * m[1][2] - m[1][0] * m[0][2]);
		Inverse[2][2] = + (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
		Inverse /= Determinant;

		return Inverse;
	}

	template <typename valType> 
	inline detail::tmat4x4<valType> inverseTranspose(
		detail::tmat4x4<valType> const & m)
	{
		valType SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		valType SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		valType SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		valType SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		valType SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		valType SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		valType SubFactor06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		valType SubFactor07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		valType SubFactor08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		valType SubFactor09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		valType SubFactor10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		valType SubFactor11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		valType SubFactor12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		valType SubFactor13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		valType SubFactor14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		valType SubFactor15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		valType SubFactor16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
		valType SubFactor17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
		valType SubFactor18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		detail::tmat4x4<valType> Inverse;
		Inverse[0][0] = + (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02);
		Inverse[0][1] = - (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04);
		Inverse[0][2] = + (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05);
		Inverse[0][3] = - (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05);

		Inverse[1][0] = - (m[0][1] * SubFactor00 - m[0][2] * SubFactor01 + m[0][3] * SubFactor02);
		Inverse[1][1] = + (m[0][0] * SubFactor00 - m[0][2] * SubFactor03 + m[0][3] * SubFactor04);
		Inverse[1][2] = - (m[0][0] * SubFactor01 - m[0][1] * SubFactor03 + m[0][3] * SubFactor05);
		Inverse[1][3] = + (m[0][0] * SubFactor02 - m[0][1] * SubFactor04 + m[0][2] * SubFactor05);

		Inverse[2][0] = + (m[0][1] * SubFactor06 - m[0][2] * SubFactor07 + m[0][3] * SubFactor08);
		Inverse[2][1] = - (m[0][0] * SubFactor06 - m[0][2] * SubFactor09 + m[0][3] * SubFactor10);
		Inverse[2][2] = + (m[0][0] * SubFactor11 - m[0][1] * SubFactor09 + m[0][3] * SubFactor12);
		Inverse[2][3] = - (m[0][0] * SubFactor08 - m[0][1] * SubFactor10 + m[0][2] * SubFactor12);

		Inverse[3][0] = - (m[0][1] * SubFactor13 - m[0][2] * SubFactor14 + m[0][3] * SubFactor15);
		Inverse[3][1] = + (m[0][0] * SubFactor13 - m[0][2] * SubFactor16 + m[0][3] * SubFactor17);
		Inverse[3][2] = - (m[0][0] * SubFactor14 - m[0][1] * SubFactor16 + m[0][3] * SubFactor18);
		Inverse[3][3] = + (m[0][0] * SubFactor15 - m[0][1] * SubFactor17 + m[0][2] * SubFactor18);

		valType Determinant = 
			+ m[0][0] * Inverse[0][0] 
			+ m[0][1] * Inverse[0][1] 
			+ m[0][2] * Inverse[0][2] 
			+ m[0][3] * Inverse[0][3];

		Inverse /= Determinant;
    
		return Inverse;
	}

}//namespace matrix_inverse
}//namespace gtc
}//namespace glm
