#ifndef GEOMETRY_2D_TRIANGLE_H
#define GEOMETRY_2D_TRIANGLE_H

#include "Constants.h"
#include "Geometry2D/Point.h"

namespace Geometry
{
	namespace Geometry2D
	{
		struct Triangle // 三角形类
		{
			Point a, b, c;
			Triangle();
			Triangle(const Point &, const Point &, const Point &);
			Real circumference() const; // 周长
			Real area() const;			// 面积
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_TRIANGLE_H
