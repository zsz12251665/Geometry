#include "Geometry2D/Circle.h"
#include <cassert>
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Circle::Circle(const Number &r, const Point &o) : r(r), o(o)
{
	;
}

int Circle::includes(const Point &p) const // 判断点是否在圆内（在圆上返回-1，在圆外返回0，在圆内部返回1）
{
	return !sign((p - o).norm(), r * r) ? -1 : sign((p - o).norm(), r * r) < 0 ? 1 : 0;
}

Real Circle::circumference() const // 周长
{
	return 2 * PI * r;
}

Real Circle::area() const // 面积
{
	return PI * r * r;
}

#ifdef REAL_AS_NUMBER

pair<Point, Point> Circle::tangentPointsTo(const Point &p) const // 求点到圆的切点
{
	assert(!includes(p));
	Real rad = acos(r / (p - o).length());
	Vector v = (p - o).unitVector() * r;
	return make_pair(o + v.rotate(-rad),  o + v.rotate(rad));
}

pair<Line, Line> Circle::tangentLinesTo(const Point &p) const // 求点到圆的切线
{
	assert(!includes(p));
	auto tangentPoints = tangentPointsTo(p);
	return make_pair(Line(p, tangentPoints.first), Line(p, tangentPoints.second));
}

#endif // REAL_AS_NUMBER

// 相交函数

int Circle::operator&&(const Line &l) const // 判断圆和直线是否相交（相切返回-1，相离返回0，相交返回1）
{
	Real d = l.distanceTo(o);
	return !sign(d, r) ? -1 : sign(d, r) < 0 ? 1 : 0;
}

int Circle::operator&&(const Circle &c) const // 判断圆和圆是否相交（内切返回-2，外切返回-1，相离返回0，相交返回1，内含返回2）
{
	int cmp_sum = sign((o - c.o).norm(), (r + c.r) * (r + c.r));
	int cmp_diff = sign((o - c.o).norm(), (r - c.r) * (r - c.r));
	return !cmp_diff ? -2 : !cmp_sum ? -1 : cmp_sum > 0 ? 0 : cmp_diff < 0 ? 2 : 1;
}

#ifdef REAL_AS_NUMBER

#ifdef GEOMETRY_2D_SEGMENT_H

Segment Circle::operator&(const Line &l) const // 求圆和直线之间的交线段
{
	assert(!(*this && l));
	Point p = l.projectPointOf(o);
	Vector v = l.direction().unitVector() * sqrt(r * r - (p - o).norm());
	return Segment(p - v, p + v);
}

#endif // GEOMETRY_2D_SEGMENT_H

#endif // REAL_AS_NUMBER
