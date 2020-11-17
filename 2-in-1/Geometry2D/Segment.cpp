#ifndef GEOMETRY_2D_SEGMENT_CPP
#define GEOMETRY_2D_SEGMENT_CPP

#include "../Constants.cpp"
#include "Point.cpp"
#include "Line.cpp"
#include <algorithm>
#include <cassert>
#include <cmath>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Segment // 直线类
		{
			Point s, e;
			Segment() {}
			Segment(const Point &s, const Point &e) : s(s), e(e) {}
			operator Line() const { return Line(s, e); } // 所在直线
			bool includes(const Point &p) const { return !sign((p - s) / (p - e)) && sign((p - s) * (p - e)) <= 0; } // 是否包含指定点
			Vector direction() const { return e - s; } // 方向向量
			Real length() const { return direction().length(); } // 线段长度
			Real slope() const { return direction().slope(); } // 斜率
			Real radian() const { return direction().radian(); } // 倾斜角（弧度制）
			Real distanceTo(const Point &p) const // 求点到线段的距离
			{
				if (sign((p - s) * (e - s)) < 0 || sign((p - e) * (s - e)) < 0)
					return std::min((p - s).length(), (p - e).length());
				return std::abs((s - p) / (e - p)) / direction().length();
			}
			// 相交函数
			int operator&&(const Segment &l) const // 判断两线段是否相交（平行且相交返回-1，无交点返回0，相交返回1）
			{
				int d1 = sign((e - s) / (l.s - s)), d2 = sign((e - s) / (l.e - s));
				int d3 = sign((l.e - l.s) / (s - l.s)), d4 = sign((l.e - l.s) / (e - l.s));
				if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
					return 1;
				return -(d1 == 0 || sign((l.s - s) / (l.s - e)) <= 0);
			}
#ifdef REAL_AS_NUMBER
			Point operator&(const Segment &l) const // 求两线段之间的交点
			{
				assert((*this && l) == 1);
				return (Line)(*this) & (Line)l;
			}
#endif // REAL_AS_NUMBER
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEGMENT_CPP
