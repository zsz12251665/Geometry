#include "Geometry2D/SemiplaneIntersection.h"
#include "CircularContainer.h"
#include "Geometry2D/Line.h"
#include <algorithm>
#include <cmath>
#include <deque>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

#ifdef REAL_AS_NUMBER

SemiplaneIntersection SemiplaneIntersection::intersection() const // 构造半平面交（半平面逆时针排列）
{
	SemiplaneIntersection tmp(*this);
	sort(tmp.begin(), tmp.end());
	CircularContainer<deque<Line>> ans;
	for (size_t i = 0; i < tmp.size(); ++i)
	{
		if (i && !sign(tmp.at(i).radian(), tmp.at(i - 1).radian()))
			continue;
		while (ans.size() > 1 && tmp.at(i).includes(ans.at(-2) & ans.at(-1)) == -1)
			ans.pop_back();
		while (ans.size() > 1 && tmp.at(i).includes(ans.at(0) & ans.at(1)) == -1)
			ans.pop_front();
		ans.push_back(tmp.at(i));
	}
	while (ans.size() > 2 && ans.at(0).includes(ans.at(-2) & ans.at(-1)) == -1)
		ans.pop_back();
	while (ans.size() > 2 && ans.at(-1).includes(ans.at(0) & ans.at(1)) == -1)
		ans.pop_front();
	tmp.clear();
	for (auto i : ans)
		tmp.push_back(i);
	return tmp;
}

Polygon SemiplaneIntersection::toPolygon() const // 将半平面交转化为多边形（凸包）
{
	Polygon ans;
	for (size_t i = 0; i < size(); ++i)
		ans.push_back(Line(at(i)) & Line(at(i + 1)));
	return ans;
}

#endif // REAL_AS_NUMBER
