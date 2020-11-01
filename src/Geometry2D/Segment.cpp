#include "Geometry2D/Segment.h"
#include "Geometry2D/Triangle.h"
#include <algorithm>
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Segment::Segment()
{
	;
}

Segment::Segment(const Point &a, const Point &b) : a(a), b(b)
{
	;
}

bool Segment::includes(const Point &p) const // 是否包含指定点
{
	return !sign((p - a) / (p - b)) && sign((p - a) * (p - b)) <= 0;
}

Vector Segment::direction() const // 方向向量
{
	return b - a;
}

Line Segment::toLine() const // 所在直线
{
	return Line(a, b);
}

Real Segment::length() const // 线段长度
{
	return direction().length();
}

Real Segment::slope() const // 斜率
{
	return direction().slope();
}

Real Segment::radian() const // 倾斜角（弧度制）
{
	return direction().radian();
}

Real Segment::distanceTo(const Point &p) const // 求点到直线的距离
{
	if (sign((p - a) * (b - a)) < 0 || sign((p - b) * (a - b)) < 0)
		return min((p - a).length(), (p - b).length());
	return 2 * Triangle(p, a, b).area() / direction().length();
}

// 相交函数

int Segment::operator&&(const Segment &s) const // 判断两线段是否相交（平行且相交返回-1，无交点返回0，相交返回1）
{
	int d1 = sign((b - a) / (l.a - a)), d2 = sign((b - a) / (l.b - a));
	int d3 = sign((s.b - s.a) / (a - s.a)), d4 = sign((s.b - s.a) / (b - s.a));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
		return 1;
	return -(d1 == 0 || sign((s.a - a) / (s.a - b)) <= 0);
}

#ifdef REAL_AS_NUMBER

Point Segment::operator&(const Segment &s) const // 求两线段之间的交点
{
	return toLine() & s.toLine();
}

#endif // REAL_AS_NUMBER
