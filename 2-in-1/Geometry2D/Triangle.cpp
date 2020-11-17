#ifndef GEOMETRY_2D_TRIANGLE_CPP
#define GEOMETRY_2D_TRIANGLE_CPP

#include "../Constants.cpp"
#include "Point.cpp"
#include <cmath>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Triangle // 三角形类
		{
			Point a, b, c;
			Triangle() {}
			Triangle(const Point &a, const Point &b, const Point &c) : a(a), b(b), c(c) {}
			Real circumference() const { return (b - a).length() + (c - b).length() + (a - c).length(); } // 周长
			Real area() const { return std::abs((b - a) / (c - a)) / 2.0; } // 面积
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_TRIANGLE_CPP
