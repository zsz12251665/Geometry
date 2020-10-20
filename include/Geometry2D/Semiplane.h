#ifndef GEOMETRY_2D_SEMIPLANE_H
#define GEOMETRY_2D_SEMIPLANE_H

#include "Constants.h"
#include "Geometry2D/Point.h"
#include "Geometry2D/Line.h"

namespace Geometry
{
	namespace Geometry2D
	{
		struct Semiplane : public Line // 半平面类（半平面位于直线方向逆时针方向）
		{
			Semiplane();
			Semiplane(const Point &, const Point &);
			Semiplane(const Line &);
			int includes(const Point &) const; // 判断点是否位于半平面内（-1表示位于分界线上，0表示不在半平面内，1表示严格在半平面内）
			// 运算符比较（极角升序）
			bool operator<(const Semiplane &sp) const;
			bool operator>(const Semiplane &sp) const;
			bool operator==(const Semiplane &sp) const;
			bool operator>=(const Semiplane &sp) const;
			bool operator<=(const Semiplane &sp) const;
			bool operator!=(const Semiplane &sp) const;
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEMIPLANE_H
