#include "Constants.h"
#include <cmath>

using namespace std;

const Geometry::Real Geometry::EPS = 1e-8; // 浮点数精度（默认1e-8）

const Geometry::Real Geometry::PI = acos(-1); // 圆周率（用于弧度制角度衡量）

int sign(const Geometry::Real a, const Geometry::Real b = 0) // 有误差判等（a < b 为-1，a ≈ b 为0，a > b 为1）
{
	return fabs(a - b) <= Geometry::EPS ? 0 : a < b ? -1 : 1;
}
