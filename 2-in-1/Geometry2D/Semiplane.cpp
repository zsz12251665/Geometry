#ifndef GEOMETRY_2D_SEMIPLANE_CPP
#define GEOMETRY_2D_SEMIPLANE_CPP

#include "../Constants.cpp"
#include "Point.cpp"
#include "Line.cpp"

namespace Geometry
{
	namespace Geometry2D
	{
		struct Semiplane : public Line // 半平面类（半平面位于直线方向逆时针方向）
		{
			Semiplane() {}
			Semiplane(const Point &s, const Point &e) : Line(s, e) {}
			Semiplane(const Line &l) : Line(l) {}
			int includes(const Point &p) const { return Line::includes(p) ? -1 : sign((e - s) / (p - s)) > 0; } // 判断点是否位于半平面内（-1表示位于分界线上，0表示不在半平面内，1表示严格在半平面内）
			// 运算符比较（极角升序）
			bool operator<(const Semiplane &sp) const { return sign(radian(), sp.radian()) < 0; }
			bool operator>(const Semiplane &sp) const { return sign(radian(), sp.radian()) > 0; }
			bool operator==(const Semiplane &sp) const { return s == sp.s && e == sp.e; }
			bool operator>=(const Semiplane &sp) const { return !(*this < sp); }
			bool operator<=(const Semiplane &sp) const { return !(*this > sp); }
			bool operator!=(const Semiplane &sp) const { return !(*this == sp); }
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEMIPLANE_CPP
