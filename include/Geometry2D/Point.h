#ifndef GEOMETRY_2D_POINT_H
#define GEOMETRY_2D_POINT_H

#include "Constants.h"

namespace Geometry
{
	namespace Geometry2D
	{
		struct Vector // 向量类（同时也是点类）
		{
			Number x, y;
			Vector(const Number & = 0, const Number & = 0);
			// 运算符比较（字典升序）
			bool operator<(const Vector &) const;
			bool operator>(const Vector &) const;
			bool operator==(const Vector &) const;
			bool operator>=(const Vector &) const;
			bool operator<=(const Vector &) const;
			bool operator!=(const Vector &) const;
			// 线性运算
			Vector operator+(const Vector &) const;
			Vector operator-(const Vector &) const;
			Vector operator*(const Number &) const;
			Vector operator/(const Number &) const;
			Vector operator-() const;
			// 其它运算
			Number dot(const Vector &) const;	    // 点积（函数版本）
			Number cross(const Vector &) const;	    // 叉积（函数版本）
			Number operator*(const Vector &) const; // 点积（运算符版本）
			Number operator/(const Vector &) const; // 叉积（运算符版本）
			Number norm() const;				    // 范数（模长的平方）
			Vector perpanticularVector() const;	    // 垂直向量（逆时针旋转90度，顺时针旋转90度须在原向量基础上取反）
			Real length() const;				    // 模长
			Real slope() const;					    // 斜率
			Real radian() const;				    // 倾斜角（弧度制）
#ifdef REAL_AS_NUMBER
			Vector unitVector(const Number & = 1) const; // 单位向量（参数控制向量长度）
			Vector rotate(const Real &) const;			 // 逆时针旋转（弧度制）
#endif // REAL_AS_NUMBER
		};
		typedef Vector Point;
#ifdef REAL_AS_NUMBER
		Point polarToCartesian(const Number &, const Real &); // 极坐标转直角坐标，直角坐标转极坐标可使用点类中的 length() 和 radian()
#endif // REAL_AS_NUMBER
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_POINT_H
