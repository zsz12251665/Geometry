#ifndef GEOMETRY_2D_SEMIPLANES_CPP
#define GEOMETRY_2D_SEMIPLANES_CPP

#include "../Constants.cpp"
#include "../CircularContainer.cpp"
#include "Point.cpp"
#include "Line.cpp"
#include "Semiplane.cpp"
#include "Polygon.cpp"
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>

namespace Geometry
{
	namespace Geometry2D
	{
		struct Semiplanes : public CircularContainer<std::vector<Semiplane>> // 半平面交类
		{
			using CircularContainer<std::vector<Semiplane>>::CircularContainer;
			typedef typename std::vector<Semiplane>::size_type size_type;
#ifdef REAL_AS_NUMBER
			Semiplanes intersection() const // 构造半平面交（半平面逆时针排列）
			{
				Semiplanes tmp(*this);
				std::sort(tmp.begin(), tmp.end());
				size_type n = 1;
				for (size_type i = 1; i < tmp.size(); ++i) // 去重
					if (sign(tmp.at(i).radian(), tmp.at(i - 1).radian()))
						tmp.at(n++) = tmp.at(i);
					else
						if (sign((tmp.at(n - 1).e - tmp.at(n - 1).s) / (tmp.at(i).s - tmp.at(n - 1).s)) > 0)
							tmp.at(n - 1) = tmp.at(i);
				tmp.resize(n);
				CircularContainer<std::deque<Semiplane>> ans;
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
			operator Polygon() const // 将半平面交转化为多边形（凸包）
			{
				if (size() < 2)
					return Polygon();
				Polygon ans;
				for (size_type i = 0; i < size(); ++i)
					ans.push_back(Line(at(i)) & Line(at(i + 1)));
				return ans;
			}
#endif // REAL_AS_NUMBER
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEMIPLANES_CPP
