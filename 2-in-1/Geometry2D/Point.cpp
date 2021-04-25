#ifndef GEOMETRY_2D_POINT_CPP
#define GEOMETRY_2D_POINT_CPP

#include "../Constants.cpp"
#include <cmath>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Vector // 向量类（同时也是点类）
		{
			Number x, y;
			Vector(const Number &x = 0, const Number &y = 0) : x(x), y(y) {}
			// 运算符比较（字典升序）
			bool operator<(const Vector &v) const { return !sign(x, v.x) ? sign(y, v.y) < 0 : sign(x, v.x) < 0; }
			bool operator>(const Vector &v) const { return !sign(x, v.x) ? sign(y, v.y) > 0 : sign(x, v.x) > 0; }
			bool operator==(const Vector &v) const { return !sign(x, v.x) && !sign(y, v.y); }
			bool operator>=(const Vector &v) const { return !(*this < v); }
			bool operator<=(const Vector &v) const { return !(*this > v); }
			bool operator!=(const Vector &v) const { return !(*this == v); }
			// 线性运算
			Vector operator+(const Vector &v) const { return Vector(x + v.x, y + v.y); }
			Vector operator-(const Vector &v) const { return Vector(x - v.x, y - v.y); }
			Vector operator*(const Number &c) const { return Vector(x * c, y * c); }
			Vector operator/(const Number &c) const { return Vector(x / c, y / c); }
			Vector operator-() const { return *this * -1; }
			// 其它运算
			Number dot(const Vector &v) const { return x * v.x + y * v.y; } // 点积（函数版本）
			Number cross(const Vector &v) const { return x * v.y - y * v.x; } // 叉积（函数版本）
			Number operator*(const Vector &v) const { return dot(v); } // 点积（运算符版本）
			Number operator/(const Vector &v) const { return cross(v); } // 叉积（运算符版本）
			Number norm() const { return x * x + y * y; } // 范数（模长的平方）
			Vector perpanticularVector() const { return Vector(-y, x); } // 垂直向量（逆时针旋转90度，顺时针旋转90度须在原向量基础上取反）
			Real length() const { return std::sqrt(norm()); } // 模长
			Real slope() const { return Real(y) / Real(x); } // 斜率
			Real radian() const { return std::atan2(y, x); } // 倾斜角（弧度制）
#ifdef REAL_AS_NUMBER
			Vector unitVector(const Number &len = 1) const { return *this / length() * len; } // 单位向量（参数控制向量长度）
			Vector rotate(const Real &r) const { return Vector(x * std::cos(r) - y * std::sin(r), x * std::sin(r) + y * std::cos(r)); } // 逆时针旋转（弧度制）
#endif // REAL_AS_NUMBER
		};
		typedef Vector Point;
#ifdef REAL_AS_NUMBER
		Point polarToCartesian(const Number &len, const Real &rad) { return Point(len * std::cos(rad), len * std::sin(rad)); } // 极坐标转直角坐标，直角坐标转极坐标可使用点类中的 length() 和 radian()
#endif // REAL_AS_NUMBER
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_POINT_CPP
