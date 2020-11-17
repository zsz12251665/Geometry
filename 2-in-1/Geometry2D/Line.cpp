#ifndef GEOMETRY_2D_LINE_CPP
#define GEOMETRY_2D_LINE_CPP

#include "../Constants.cpp"
#include "Point.cpp"
#include <cassert>
#include <cmath>


namespace Geometry
{
	namespace Geometry2D
	{
		struct Line // 直线类
		{
			Point s, e;
			Line() {}
			Line(const Point &s, const Point &e) : s(s), e(e) {}
			bool includes(const Point &p) const { return !sign((p - s) / (p - e)); } // 是否包含指定点
			Vector direction() const { return e - s; } // 方向向量
			Real slope() const { return direction().slope(); } // 斜率
			Real radian() const { return direction().radian(); } // 倾斜角（弧度制）
			Real distanceTo(const Point &p) const { return std::abs((s - p) / (e - p)) / direction().length(); } // 求点到直线的距离
#ifdef REAL_AS_NUMBER
			Point projectPointOf(const Point &p) const { return s + direction() * ((p - s) * direction() / direction().norm()); } // 指定点到直线的投影（在垂直直线的方向上）
			Point symmetryPointOf(const Point &p) const { return projectPointOf(p) * 2 - p; } // 指定点关于直线的对称点
#endif // REAL_AS_NUMBER
			// 相交函数
			int operator&&(const Line &l) const { return l.includes(s) && l.includes(e) ? -1 : std::abs(sign(direction() / l.direction())); } // 判断两直线是否相交（重合返回-1，平行返回0，相交返回1）
#ifdef REAL_AS_NUMBER
			Point operator&(const Line &l) const // 求两直线之间的交点
			{
				assert((*this && l) == 1);
				Number sa = (l.e - l.s) / (s - l.s), sb = (l.e - l.s) / (e - l.s);
				return (s * sb - e * sa) / (sb - sa);
			}
#endif // REAL_AS_NUMBER
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_LINE_CPP
