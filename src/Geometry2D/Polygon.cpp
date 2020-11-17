#include "Geometry2D/Polygon.h"
#include "Geometry2D/Segment.h"
#include "Geometry2D/Triangle.h"
#include <algorithm>
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Real Polygon::circumference() const // 周长
{
	Real ans = 0;
	for (size_type i = 0; i < size(); ++i)
		ans += (at(i + 1) - at(i)).length();
	return ans;
}

Real Polygon::area() const // 面积
{
	Number sum = 0;
	for (size_type i = 0; i < size(); ++i)
		sum += at(i + 1) / at(i);
	return abs(sum) / 2.0;
}

Polygon Polygon::convexHull(const bool &strict) const // 求点逆时针排列的凸包。参数表示是否去除边上的点
{
	Polygon cpy(*this), ans;
	sort(cpy.begin(), cpy.end());
	for (size_type i = 0; i < cpy.size(); ++i) // 上凸壳
	{
		while (ans.size() > 1 && sign((ans.at(-1) - ans.at(-2)) / (cpy.at(i) - ans.at(-2))) < strict)
			ans.pop_back();
		ans.push_back(cpy.at(i));
	}
	for (size_type i = 2, pre = ans.size(); i <= cpy.size(); ++i) // 下凸壳
	{
		while (ans.size() > pre && sign((ans.at(-1) - ans.at(-2)) / (cpy.at(-i) - ans.at(-2))) < strict)
			ans.pop_back();
		ans.push_back(cpy.at(-i));
	}
	ans.pop_back();
	return ans;
}

// 下列函数均要求点逆时针排列

int Polygon::includes(const Point &p) const // 判断点是否在多边形内（在多边形边上返回-1，在多边形外返回0，在多边形内部返回1）
{
	int cnt = 0;
	for (size_type i = 0; i < size(); ++i)
	{
		if (Segment(at(i), at(i + 1)).includes(p))
			return -1;
		if (sign((p - at(i + 1)) / (at(i) - at(i + 1))) > 0 && sign(at(i).y, p.y) < 0 && sign(p.y, at(i + 1).y) <= 0)
			++cnt;
		if (sign((p - at(i + 1)) / (at(i) - at(i + 1))) < 0 && sign(at(i + 1).y, p.y) < 0 && sign(p.y, at(i).y) <= 0)
			--cnt;
	}
	return cnt != 0;
}

bool Polygon::isConvexHull() const // 判断多边形是否为凸包
{
	for (size_type i = 0; i < size(); ++i)
		if (sign((at(i + 1) - at(i)) / (at(i + 2) - at(i))) < 0)
			return false;
	return true;
}

Number Polygon::convexDiameterSquare() const // 旋转卡壳求凸包直径的平方（若多边形不是凸包则返回-1，常用于 convexHull() 后）
{
	if (!isConvexHull())
		return -1;
	Number ans = 0;
	for (size_type i = 0, now = 1; i < size(); ++i)
	{
		while (sign(Triangle(at(i), at(i + 1), at(now)).area(), Triangle(at(i), at(i + 1), at(now + 1)).area()) < 0)
			now = (now + 1) % size();
		ans = max({ans, (at(i) - at(now)).norm(), (at(i + 1) - at(now + 1)).norm()});
	}
	return ans;
}
