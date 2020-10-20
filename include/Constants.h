#ifndef GEOMETRY_CONSTANTS_H
#define GEOMETRY_CONSTANTS_H

namespace Geometry
{
	// 类型及常量声明
#ifndef SELF_DEFINED_REAL
	typedef double Real; // 实数（以浮点数近似表示）
#endif
#ifndef SELF_DEFINED_NUM
	typedef Real Number; // 普通数字（不进行开方及非整除运算，可用整数类型代替）
	#define REAL_AS_NUMBER // 该定义使得 Real 可以被安全地赋值给 Number
#endif
#ifndef SELF_DEFINED_EPS
	extern const Real EPS; // 浮点数精度（默认 1e-8）
#endif
	extern const Real PI; // 圆周率（用于弧度制角度衡量）
	int sign(const Real, const Real = 0); // 有误差判等（a < b 为-1，a ≈ b 为0，a > b 为1）
}; // namespace Geometry

#endif // GEOMETRY_CONSTANTS_H
