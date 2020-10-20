#ifndef GEOMETRY_2D_SEMIPLANEINTERSECTION_H
#define GEOMETRY_2D_SEMIPLANEINTERSECTION_H

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
	struct SemiplaneIntersection : public CircularContainer<vector<Semiplane>> // 半平面交类
	{
		using CircularContainer<vector<Semiplane>>::CircularContainer;
#ifdef REAL_AS_NUMBER
		SemiplaneIntersection intersection() const; // 构造半平面交（半平面逆时针排列）
		Polygon toPolygon() const; 				    // 将半平面交转化为多边形（凸包）
#endif // REAL_AS_NUMBER
	};
	}; // namespace Geometry2D
}; // namespace Geometry

#endif // GEOMETRY_2D_SEMIPLANEINTERSECTION_H
