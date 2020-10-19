#include "Geometry2D/Line.h"
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Triangle::Triangle()
{
	;
}

Triangle::Triangle(const Point &a, const Point &b, const Point &c) : a(a), b(b), c(c)
{
	;
}

// 实数运算专用函数

Real Triangle::circumference() const // 周长
{
	return (b - a).length() + (c - b).length() + (a - c).length();
}

Real Triangle::area() const // 面积
{
	return abs((b - a) / (c - a)) / 2.0;
}
