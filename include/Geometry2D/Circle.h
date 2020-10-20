#ifndef GEOMETRY_2D_CIRCLE_H
#define GEOMETRY_2D_CIRCLE_H

#include "Constants.h"
#include "Geometry2D/Point.h"
#include "Geometry2D/Line.h"
#include "Geometry2D/Segment.h"
#include <utility>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Circle // 圆类
		{
			Number r;
			Point o;
			Circle(const Number = 0, const Point & = {});
			int includes(const Point &) const; // 判断点是否在圆内（在圆上返回-1，在圆外返回0，在圆内部返回1）
			Real circumference() const;		   // 周长
			Real area() const;				   // 面积
#ifdef REAL_AS_NUMBER
			std::pair<Line, Line> tangentLineTo(const Point &) const; // 求点到圆的切线
#endif // REAL_AS_NUMBER
			// 相交函数
			int operator&&(const Line &) const;	   // 判断圆和直线是否相交（相切返回-1，相离返回0，相交返回1）
			Segment operator&(const Line &) const; // 求圆和直线之间的交线段
			int operator&&(const Circle &) const;  // 判断圆和直线是否相交（内切返回-2，外切返回-1，相离返回0，相交返回1，内含返回2）
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_CIRCLE_H
