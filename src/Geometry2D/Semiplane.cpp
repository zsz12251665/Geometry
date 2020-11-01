#include "Geometry2D/Semiplane.h"
#include <cmath>

using namespace Geometry;
using namespace Geometry2D;
using namespace std;

Semiplane::Semiplane()
{
	;
}

Semiplane::Semiplane(const Point &a, const Point &b) : Line(a, b)
{
	;
}

Semiplane::Semiplane(const Line &l) : Line(l)
{
	;
}

int Semiplane::includes(const Point &p) const // 判断点是否位于半平面内（-1表示位于分界线上，0表示不在半平面内，1表示严格在半平面内）
{
	return Line::includes(p) ? -1 : sign((b - a) / (p - a)) > 0;
}

// 运算符比较（极角升序）

bool Semiplane::operator<(const Semiplane &sp) const
{
	return sign(radian(), sp.radian()) < 0;
}

bool Semiplane::operator>(const Semiplane &sp) const
{
	return sign(radian(), sp.radian()) > 0;
}

bool Semiplane::operator==(const Semiplane &sp) const
{
	return a == sp.a && b == sp.b;
}

bool Semiplane::operator>=(const Semiplane &sp) const
{
	return !(*this < sp);
}

bool Semiplane::operator<=(const Semiplane &sp) const
{
	return !(*this > sp);
}

bool Semiplane::operator!=(const Semiplane &sp) const
{
	return !(*this == sp);
}
