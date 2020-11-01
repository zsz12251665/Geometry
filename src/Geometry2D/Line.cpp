#include "Geometry2D/Line.h"
#include "Geometry2D/Triangle.h"
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Line::Line()
{
	;
}

Line::Line(const Point &a, const Point &b) : a(a), b(b)
{
	;
}

bool Line::includes(const Point &p) const // 是否包含指定点
{
	return !sign((p - a) / (p - b));
}

Vector Line::direction() const // 方向向量
{
	return b - a;
}

Real Line::slope() const // 斜率
{
	return direction().slope();
}

Real Line::radian() const // 倾斜角（弧度制）
{
	return direction().radian();
}

Real Line::distanceTo(const Point &p) const // 求点到直线的距离
{
	return 2 * Triangle(p, a, b).area() / direction().length();
}

#ifdef REAL_AS_NUMBER

Point Line::projectPointOf(const Point &p) const // 指定点到直线的投影（在垂直直线的方向上）
{
	return a + direction() * ((p - a) * direction() / direction().norm());
}

Point Line::symmetryPointOf(const Point &p) const // 指定点关于直线的对称点
{
	return projectPointOf(p) * 2 - p;
}

#endif // REAL_AS_NUMBER

// 相交函数

int Line::operator&&(const Line &l) const // 判断两直线是否相交（重合返回-1，平行返回0，相交返回1）
{
	return l.includes(a) && l.includes(b) ? -1 : abs(sign(direction() / l.direction()));
}

#ifdef REAL_AS_NUMBER

Point Line::operator&(const Line &l) const // 求两直线之间的交点
{
	Number sa = (l.b - l.a) / (a - l.a), sb = (l.b - l.a) / (b - l.a);
	return (a * sb - b * sa) / (sb - sa);
}

#endif // REAL_AS_NUMBER
