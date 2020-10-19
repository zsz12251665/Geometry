#include "Geometry2D/Point.h"
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Vector::Vector(const Number x = 0, const Number y = 0) : x(x), y(y)
{
	;
}

// 运算符比较（字典升序）

bool Vector::operator<(const Vector &v) const
{
	return !sign(x, v.x) ? sign(y, v.y) < 0 : sign(x, v.x) < 0;
}

bool Vector::operator>(const Vector &v) const
{
	return !sign(x, v.x) ? sign(y, v.y) > 0 : sign(x, v.x) > 0;
}

bool Vector::operator==(const Vector &v) const
{
	return !sign(x, v.x) && !sign(y, v.y);
}

bool Vector::operator>=(const Vector &v) const
{
	return !(*this < v);
}

bool Vector::operator<=(const Vector &v) const
{
	return !(*this > v);
}

bool Vector::operator!=(const Vector &v) const
{
	return !(*this == v);
}

// 线性运算

Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y);
}

Vector Vector::operator*(const Number c) const
{
	return Vector(x * c, y * c);
}

Vector Vector::operator/(const Number c) const
{
	return Vector(x / c, y / c);
}

Vector Vector::operator-() const
{
	return *this * -1;
}

// 其它运算

Number Vector::dot(const Vector &v) const // 点积（函数版本）
{
	return x * v.x + y * v.y;
}

Number Vector::cross(const Vector &v) const // 叉积（函数版本）
{
	return x * v.y - y * v.x;
}

Number Vector::operator*(const Vector &v) const // 点积（运算符版本）
{
	return dot(v);
}

Number Vector::operator/(const Vector &v) const // 叉积（运算符版本）
{
	return cross(v);
}

Number Vector::norm() const // 范数（模长的平方）
{
	return x * x + y * y;
}

Vector Vector::perpanticularVector() const // 垂直向量（逆时针旋转90度，顺时针旋转90度须在原向量基础上取反）
{
	return Vector(-y, x);
}

Real Vector::length() const // 模长
{
	return sqrt(norm());
}

Real Vector::slope() const // 斜率
{
	return Real(y) / Real(x);
}

Real Vector::radian() const // 倾斜角（弧度制）
{
	return atan2(y, x);
}

#ifdef REAL_AS_NUMBER

Vector Vector::unitVector() const // 单位向量
{
	return *this / length();
}

Vector Vector::rotate(const Real r) const // 旋转（弧度制）
{
	return Vector(x * cos(r) - y * sin(r), x * sin(r) + y * cos(r));
}

Point polarToCartesian(const Real len, const Real rad) // 极坐标转直角坐标，直角坐标转极坐标可使用点类中的 length() 和 radian()
{
	return Point(len * cos(rad), len * sin(rad));
}

#endif // REAL_AS_NUMBER
