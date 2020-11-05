#include "Geometry2D/Segment.h"
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Segment::Segment()
{
	;
}

Segment::Segment(const Point &s, const Point &e) : s(s), e(e)
{
	;
}

Segment::operator Line() const // 所在直线
{
	return Line(s, e);
}

bool Segment::includes(const Point &p) const // 是否包含指定点
{
	return !sign((p - s) / (p - e)) && sign((p - s) * (p - e)) <= 0;
}

Vector Segment::direction() const // 方向向量
{
	return e - s;
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
	if (sign((p - s) * (e - s)) < 0 || sign((p - e) * (s - e)) < 0)
		return min((p - s).length(), (p - e).length());
	return abs((s - p) / (e - p)) / direction().length();
}

// 相交函数

int Segment::operator&&(const Segment &l) const // 判断两线段是否相交（平行且相交返回-1，无交点返回0，相交返回1）
{
	int d1 = sign((e - s) / (l.s - s)), d2 = sign((e - s) / (l.e - s));
	int d3 = sign((l.e - l.s) / (s - l.s)), d4 = sign((l.e - l.s) / (e - l.s));
	if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
		return 1;
	return -(d1 == 0 || sign((l.s - s) / (l.s - e)) <= 0);
}

#ifdef REAL_AS_NUMBER

Point Segment::operator&(const Segment &l) const // 求两线段之间的交点
{
	assert((*this && l) == 1);
	return (Line)(*this) & (Line)l;
}

#endif // REAL_AS_NUMBER
