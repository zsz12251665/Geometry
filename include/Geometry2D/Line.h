#ifndef GEOMETRY_2D_LINE_H
#define GEOMETRY_2D_LINE_H

#include "Constants.h"
#include "Geometry2D/Point.h"
#include "Geometry2D/Triangle.h"

namespace Geometry
{

	namespace Geometry2D
	{
		struct Line // 直线类
		{
			Point a, b;
			Line();
			Line(const Point &, const Point &);
			Vector direction() const;					// 方向向量
			Point projectPointOf(const Point &) const;	// 指定点到直线的投影（在垂直直线的方向上）
			Point symmetryPointOf(const Point &) const; // 指定点关于直线的对称点
			bool contains(const Point &) const;			// 判断直线是否包含指定点
			// 实数运算专用函数
			Real slope() const;					  // 斜率
			Real radian() const;				  // 倾斜角（弧度制）
			Real distanceTo(const Point &) const; // 求点到直线的距离
			// 相交函数
			int operator&&(const Line &) const;	 // 判断两直线是否相交（重合返回-1，平行返回0，相交返回1）
			Point operator&(const Line &) const; // 求两直线之间的交点
		};

	}; // namespace Geometry2D

}; // namespace Geometry

#endif // GEOMETRY_2D_LINE_H
