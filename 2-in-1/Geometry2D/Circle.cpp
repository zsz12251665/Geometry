#ifndef GEOMETRY_2D_CIRCLE_CPP
#define GEOMETRY_2D_CIRCLE_CPP

#include "../Constants.cpp"
#include "Point.cpp"
#include "Line.cpp"
#include "Segment.cpp"
#include <cassert>
#include <cmath>
#include <utility>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Circle // 圆类
		{
			Number r;
			Point o;
			Circle(const Number &r = 0, const Point &o = {}) : r(r), o(o) {}
			int includes(const Point &p) const { return !sign((p - o).norm(), r * r) ? -1 : sign((p - o).norm(), r * r) < 0 ? 1 : 0; } // 判断点是否在圆内（在圆上返回-1，在圆外返回0，在圆内部返回1）
			Real circumference() const { return 2 * PI * r; } // 周长
			Real area() const { return PI * r * r; } // 面积
#ifdef REAL_AS_NUMBER
			std::pair<Point, Point> tangentPointsTo(const Point &p) const // 求点到圆的切点
			{
				Real rad = acos(r / (p - o).length());
				Vector v = (p - o).unitVector() * r;
				return std::make_pair(o + v.rotate(-rad),  o + v.rotate(rad));
			}
			std::pair<Line, Line> tangentLinesTo(const Point &p) const // 求点到圆的切线
			{
				auto tangentPoints = tangentPointsTo(p);
				return std::make_pair(Line(p, tangentPoints.first), Line(p, tangentPoints.second));
			}
#endif // REAL_AS_NUMBER
			// 相交函数
			int operator&&(const Line &l) const // 判断圆和直线是否相交（相切返回-1，相离返回0，相交返回1）
			{
				Real d = l.distanceTo(o);
				return !sign(d, r) ? -1 : sign(d, r) < 0 ? 1 : 0;
			}
			int operator&&(const Circle &c) const // 判断圆和圆是否相交（内切返回-2，外切返回-1，相离返回0，相交返回1，内含返回2）
			{
				int cmp_sum = sign((o - c.o).norm(), (r + c.r) * (r + c.r));
				int cmp_diff = sign((o - c.o).norm(), (r - c.r) * (r - c.r));
				return !cmp_diff ? -2 : !cmp_sum ? -1 : cmp_sum > 0 ? 0 : cmp_diff < 0 ? 2 : 1;
			}
#ifdef REAL_AS_NUMBER
#ifdef GEOMETRY_2D_SEGMENT_CPP
			Segment operator&(const Line &l) const // 求圆和直线之间的交线段
			{
				assert(!(*this && l));
				Point p = l.projectPointOf(o);
				Vector v = l.direction().unitVector() * sqrt(r * r - (p - o).norm());
				return Segment(p - v, p + v);
			}
#endif // GEOMETRY_2D_SEGMENT_CPP
#endif // REAL_AS_NUMBER
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_CIRCLE_CPP
