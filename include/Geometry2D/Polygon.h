#ifndef GEOMETRY_2D_POLYGON_H
#define GEOMETRY_2D_POLYGON_H

#include "Constants.h"
#include "CircularContainer.h"
#include "Geometry2D/Point.h"
#include <vector>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Polygon : public CircularContainer<vector<Point>> // 多边形类，点应按逆时针顺序排列（实际无严格限制）
		{
			using CircularContainer<vector<Point>>::CircularContainer;
			typedef typename vector<Point>::size_type size_type;
			Real circumference() const;					 // 周长
			Real area() const;							 // 面积
			Polygon convexHull(const bool = true) const; // 求点逆时针排列的凸包。参数表示是否去除边上的点
			// 下列函数均要求点逆时针排列
			int includes(const Point &) const;	 // 判断点是否在多边形内（在多边形边上返回-1，在多边形外返回0，在多边形内部返回1）
			bool isConvexHull() const;			 // 判断多边形是否为凸包
			Number convexDiameterSquare() const; // 旋转卡壳求凸包直径的平方（若多边形不是凸包则返回-1，常用于 convexHull() 后）
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_POLYGON_H
