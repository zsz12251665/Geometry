#include "Geometry2D/Semiplanes.h"
#include "CircularContainer.h"
#include "Geometry2D/Line.h"
#include <algorithm>
#include <cmath>
#include <deque>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

#ifdef REAL_AS_NUMBER

Semiplanes Semiplanes::intersection() const // 构造半平面交（半平面逆时针排列）
{
	Semiplanes tmp(*this);
	sort(tmp.begin(), tmp.end());
	size_type n = 1;
	for (size_type i = 1; i < tmp.size(); ++i) // 去重
		if (sign(tmp.at(i).radian(), tmp.at(i - 1).radian()))
			tmp.at(n++) = tmp.at(i);
		else
			if (sign((tmp.at(n - 1).b - tmp.at(n - 1).a) / (tmp.at(i).a - tmp.at(n - 1).a)) > 0)
				tmp.at(n - 1) = tmp.at(i);
	tmp.resize(n);
	CircularContainer<deque<Semiplane>> ans;
	for (size_type i = 0; i < tmp.size(); ++i)
	{
		while (ans.size() > 1 && !tmp.at(i).includes(ans.at(-2) & ans.at(-1)))
			ans.pop_back();
		while (ans.size() > 1 && !tmp.at(i).includes(ans.at(0) & ans.at(1)))
			ans.pop_front();
		ans.push_back(tmp.at(i));
	}
	while (ans.size() > 1 && !ans.at(0).includes(ans.at(-2) & ans.at(-1)))
		ans.pop_back();
	while (ans.size() > 1 && !ans.at(-1).includes(ans.at(0) & ans.at(1)))
		ans.pop_front();
	return Semiplanes(ans.begin(), ans.end());
}

Polygon Semiplanes::toPolygon() const // 将半平面交转化为多边形（凸包）
{
	if (size() < 2)
		return Polygon();
	Polygon ans;
	for (size_type i = 0; i < size(); ++i)
		ans.push_back(Line(at(i)) & Line(at(i + 1)));
	return ans;
}

#endif // REAL_AS_NUMBER
