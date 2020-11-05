#ifndef GEOMETRY_2D_SEGMENT_H
#define GEOMETRY_2D_SEGMENT_H

#include "Constants.h"
#include "Geometry2D/Point.h"
#include "Geometry2D/Line.h"

namespace Geometry
{
	namespace Geometry2D
	{
		struct Segment // 直线类
		{
			Point s, e;
			Segment();
			Segment(const Point &, const Point &);
			operator Line() const;				  // 所在直线
			bool includes(const Point &) const;	  // 是否包含指定点
			Vector direction() const;			  // 方向向量
			Real length() const;				  // 线段长度
			Real slope() const;					  // 斜率
			Real radian() const;				  // 倾斜角（弧度制）
			Real distanceTo(const Point &) const; // 求点到线段的距离
			// 相交函数
			int operator&&(const Segment &) const; // 判断两线段是否相交（平行且相交返回-1，无交点返回0，相交返回1）
#ifdef REAL_AS_NUMBER
			Point operator&(const Segment &) const; // 求两线段之间的交点
#endif // REAL_AS_NUMBER
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEGMENT_H
