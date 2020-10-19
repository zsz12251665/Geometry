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
			Point a, b;
			Segment();
			Segment(const Point &, const Point &);
			bool includes(const Point &) const; // 是否包含指定点
			Vector direction() const;			// 方向向量
			Line toLine() const;				// 所在直线
			Real length() const;				  // 线段长度
			Real slope() const;					  // 斜率
			Real radian() const;				  // 倾斜角（弧度制）
			Real distanceTo(const Point &) const; // 求点到线段的距离
		};

	}; // namespace Geometry2D

}; // namespace Geometry

#endif // GEOMETRY_2D_SEGMENT_H
