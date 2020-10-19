#include "Geometry2D/Segment.h"
#include "Geometry2D/Triangle.h"
#include <algorithm>
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Segment::Segment()
{
	;
}

Segment::Segment(const Point &a, const Point &b) : a(a), b(b)
{
	;
}

bool Segment::includes(const Point &p) const // 是否包含指定点
{
	return !sign((p - a) / (p - b)) && sign((p - a) * (p - b)) <= 0;
}

Vector Segment::direction() const // 方向向量
{
	return b - a;
}

Line Segment::toLine() const // 所在直线
{
	return Line(a, b);
}

Real Segment::length() const // 线段长度
{
	return direction().length();
}

Real Segment::slope() const // 斜率
{
	return direction().slope();
}

Real Segment::radian() const // 倾斜角（弧度制）
{
	return direction().radian();
}

Real Segment::distanceTo(const Point &p) const // 求点到直线的距离
{
	if (sign((p - a) * (b - a)) < 0 || sign((p - b) * (a - b)) < 0)
		return min((p - a).length(), (p - b).length());
	return 2 * Triangle(p, a, b).area() / direction().length();
}
