#ifndef GEOMETRY_2D_SEMIPLANES_H
#define GEOMETRY_2D_SEMIPLANES_H

#include "Constants.h"
#include "CircularContainer.h"
#include "Geometry2D/Point.h"
#include "Geometry2D/Semiplane.h"
#include "Geometry2D/Polygon.h"
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
			Semiplanes intersection() const; // 构造半平面交（半平面逆时针排列）
			Polygon toPolygon() const;		 // 将半平面交转化为多边形（凸包）
#endif // REAL_AS_NUMBER
		};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEMIPLANES_H
