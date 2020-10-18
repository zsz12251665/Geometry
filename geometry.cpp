#include <bits/stdc++.h>

template <class T>
struct CircularContainer : public T // 可循环索引的容器模板
{
	using T::size;
	using T::T;
	typedef typename T::value_type value_type;
	typedef typename T::difference_type diff_type;
	value_type &at(const diff_type i) { diff_type n = size(); return T::at((i % n + n) % n); }
	const value_type &at(const diff_type i) const { diff_type n = size(); return T::at((i % n + n) % n); }
	value_type &operator[](const diff_type i) { return at(i); }
	const value_type &operator[](const diff_type i) const { return at(i); }
};

namespace Geometry2D
{
	// 类型及常量声明
	using namespace std;
	typedef double Real;
	typedef double Number;
	const Real EPS = 1e-8;
	const Real PI = acos(-1);
	inline int sign(Real a, Real b = 0) { return fabs(a - b) <= EPS ? 0 : a < b ? -1 : 1; } // 有误差判等（a < b 为-1，a ≈ b 为0，a > b 为1）

	// 类声明
	struct Vector // 向量类（同时也是点类）
	{
		Number x, y;
		Vector(const Number x = 0, const Number y = 0) : x(x), y(y) {}
		// 线性运算
		Vector operator+(const Vector &v) const { return Vector(x + v.x, y + v.y); }
		Vector operator-(const Vector &v) const { return Vector(x - v.x, y - v.y); }
		Vector operator*(const Number c) const { return Vector(x * c, y * c); }
		Vector operator/(const Number c) const { return Vector(x / c, y / c); }
		Vector operator-() const { return *this * -1; }
		// 其它运算
		Number operator*(const Vector &v) const { return x * v.x + y * v.y; } // 点积
		Number operator/(const Vector &v) const { return x * v.y - y * v.x; } // 叉积
		Number norm() const { return x * x + y * y; }						  // 范数（模长的平方）
		Vector perpanticularVector() const { return Vector(-y, x); }		  // 垂直向量（逆时针旋转90度）
		// 运算符比较（字典升序）
		bool operator<(const Vector &v) const { return !sign(x, v.x) ? sign(y, v.y) < 0 : sign(x, v.x) < 0; }
		bool operator>(const Vector &v) const { return !sign(x, v.x) ? sign(y, v.y) > 0 : sign(x, v.x) > 0; }
		bool operator==(const Vector &v) const { return !sign(x, v.x) && !sign(y, v.y); }
		bool operator>=(const Vector &v) const { return !(*this < v); }
		bool operator<=(const Vector &v) const { return !(*this > v); }
		bool operator!=(const Vector &v) const { return !(*this == v); }
		// 实数运算专用函数
		Real length() const { return sqrt(norm()); }														   // 模长
		Real slope() const { return Real(y) / Real(x); }													   // 斜率
		Real angle() const { return atan2(y, x); }															   // 倾斜角（弧度制）
		Vector unitVector() const { return *this / length(); }												   // 单位向量
		Vector rotate(const Real r) const { return Vector(x * cos(r) - y * sin(r), x * sin(r) + y * cos(r)); } // 旋转（弧度制）
	};

	typedef Vector Point; // 定义 Point 为 Vector 的别名

	// 常用函数
	Point polarToCartesian(const Real len, const Real rad) { return Point(len * cos(rad), len * sin(rad)); }   // 极坐标转直角坐标，直角坐标转极坐标可使用向量模板中的 length() 和 angle()
	Number triangleArea(const Point &a, const Point &b, const Point &c) { return abs((a - b) / (a - c) / 2); } // 求指定点构成的三角形的面积

	struct Line // 直线类
	{
		Point a, b;
		Line() {}
		Line(const Point &a, const Point &b) : a(a), b(b) {}
		Vector direction() const { return b - a; }																			  // 方向向量
		Point projectPointOf(const Point &p) const { return a + direction() * ((p - a) * direction() / direction().norm()); } // 指定点到直线的投影（在垂直直线的方向上）
		Point symmetryPointOf(const Point &p) const { return projectPointOf(p) * 2 - p; }									  // 指定点关于直线的对称点
		bool contains(const Point &p) const { return !sign((p - a) / (p - b)); }											  // 判断直线是否包含指定点
		// 实数运算专用函数
		Real slope() const { return direction().slope(); }												   // 斜率
		Real angle() const { return direction().angle(); }												   // 倾斜角（弧度制）
		Real distanceTo(const Point &p) const { return 2 * triangleArea(p, a, b) / direction().length(); } // 求点到直线的距离
		// 相交函数
		int intersectionExists(const Line &l) const // 判断两直线是否相交（重合返回-1，平行返回0，相交返回1）
		{
			return l.contains(a) && l.contains(b) ? -1 : abs(sign(direction() / l.direction()));
		}
		Point intersectionWith(const Line &l) const // 求两直线之间的交点
		{
			Number sa = triangleArea(l.a, a, b), sb = triangleArea(l.b, a, b);
			return l.a + l.direction() * sa / (sa + sb);
		}
	};

	struct Segment : public Line // 线段类
	{
		using Line::Line;
		bool contains(const Point &p) const { return Line::contains(p) && sign((p - a) * (p - b)) <= 0; } // 判断线段是否包含指定点
		// 实数运算专用函数
		Real length() const { return direction().length(); }																														 // 线段长度
		Real distanceTo(const Point &p) const { return sign((p - a) * (b - a)) < 0 || sign((p - b) * (a - b)) < 0 ? min((p - a).length(), (p - b).length()) : Line::distanceTo(p); } // 求点到线段的距离
	};

	struct Circle // 圆类
	{
		Number r;
		Point o;
		Circle(const Number r = 0, const Point &o = {}) : r(r), o(o) {}
		int contains(const Point &p) const { return !sign((p - o).norm(), r * r) ? -1 : sign((p - o).norm(), r * r) < 0 ? 1 : 0; } // 判断点是否在圆内（在圆上返回-1，在圆外返回0，在圆内部返回1）
		Real circumference() const { return 2 * PI * r; }																		   // 周长
		Real area() const { return PI * r * r; }																				   // 面积
		// 相交函数
		int intersectionExists(const Line &l) const // 判断圆和直线是否相交（相切返回-1，相离返回0，相交返回1）
		{
			Real d = l.distanceTo(o);
			return !sign(d, r) ? -1 : sign(d, r) < 0 ? 1 : 0;
		}
		Segment intersectionWith(const Line &l) const // 求圆和直线之间的交线段
		{
			Point p = l.projectPointOf(o);
			Vector v = l.direction().unitVector() * sqrt(r * r - (p - o).norm());
			return Segment(p - v, p + v);
		}
		int intersectionExists(const Circle &c) const // 判断圆和直线是否相交（内切返回-2，外切返回-1，相离返回0，相交返回1，内含返回2）
		{
			int cmp_sum = sign((o - c.o).norm(), (r + c.r) * (r + c.r));
			int cmp_diff = sign((o - c.o).norm(), (r - c.r) * (r - c.r));
			return !cmp_diff ? -2 : !cmp_sum ? -1 : cmp_sum > 0 ? 0 : cmp_diff < 0 ? 2 : 1;
		}
		// 切线函数
		pair<Line, Line> tangentLineTo(const Point &p) const // 求点到圆的切线
		{
			Real l = r * r / (o - p).length(), h = sqrt(r * r - l * l);
			Vector v1 = (p - o).unitVector() * l, v2 = (p - o).perpanticularVector().unitVector() * h;
			return make_pair(Line(p, o + v1 - v2), Line(p, o + v1 + v2));
		}
	};

	struct Polygon : public CircularContainer<vector<Point>> // 多边形类，点应按逆时针顺序排列（实际无严格限制）
	{
		using CircularContainer<vector<Point>>::CircularContainer;
		Real circumference() const // 周长
		{
			Real ans = 0;
			for (size_t i = 0; i < size(); ++i)
				ans += (at(i + 1) - at(i)).length();
			return ans;
		}
		Number area() const // 面积
		{
			Number sum = 0;
			for (size_t i = 0; i < size(); ++i)
				sum += at(i + 1) / at(i);
			return abs(sum) / 2;
		}
		Polygon convexHull(const bool strict = true) const // 求点逆时针排列的凸包。strict 表示是否去除边上的点
		{
			Polygon cpy(*this), ans;
			sort(cpy.begin(), cpy.end());
			for (size_t i = 0; i < cpy.size(); ++i) // 上凸壳
			{
				while (ans.size() > 1 && sign((ans.at(-1) - ans.at(-2)) / (cpy.at(i) - ans.at(-2))) < strict)
					ans.pop_back();
				ans.push_back(cpy.at(i));
			}
			for (size_t i = 2, pre = ans.size(); i <= cpy.size(); ++i) // 下凸壳
			{
				while (ans.size() > pre && sign((ans.at(-1) - ans.at(-2)) / (cpy.at(-i) - ans.at(-2))) < strict)
					ans.pop_back();
				ans.push_back(cpy.at(-i));
			}
			ans.pop_back();
			return ans;
		}
		// 下列函数均要求点逆时针排列
		int contains(const Point &p) const // 判断点是否在多边形内（在多边形边上返回-1，在多边形外返回0，在多边形内部返回1）
		{
			int cnt = 0;
			for (size_t i = 0; i < size(); ++i)
			{
				if (Segment(at(i), at(i + 1)).contains(p))
					return -1;
				if (sign((p - at(i + 1)) / (at(i) - at(i + 1))) > 0 && sign(at(i).y, p.y) < 0 && sign(p.y, at(i + 1).y) <= 0)
					++cnt;
				if (sign((p - at(i + 1)) / (at(i) - at(i + 1))) < 0 && sign(at(i + 1).y, p.y) < 0 && sign(p.y, at(i).y) <= 0)
					--cnt;
			}
			return cnt != 0;
		}
		bool isConvexHull() const // 判断多边形是否为凸包
		{
			for (size_t i = 0; i < size(); ++i)
				if (sign((at(i + 1) - at(i)) / (at(i + 2) - at(i))) < 0)
					return false;
			return true;
		}
		Number convexDiameterSquare() const // 旋转卡壳求凸包直径的平方（若多边形不是凸包则返回-1，常用于 convexHull() 后）
		{
			if (!isConvexHull())
				return -1;
			Number ans = 0;
			for (size_t i = 0, now = 1; i < size(); ++i)
			{
				while (sign(triangleArea(at(i), at(i + 1), at(now)), triangleArea(at(i), at(i + 1), at(now + 1))) < 0)
					now = (now + 1) % size();
				ans = max({ans, (at(i) - at(now)).norm(), (at(i + 1) - at(now + 1)).norm()});
			}
			return ans;
		}
	};

	struct Semiplane : public Line // 半平面类（半平面位于直线方向逆时针方向）
	{
		Semiplane() {}
		Semiplane(const Point &a, const Point &b) : Line(a, b) {}
		Semiplane(const Line &l) : Line(l) {}
		bool contains(const Point &p) const { return sign((b - a) / (p - a)) > 0; } // 判断点是否位于半平面内
		// 运算符比较（极角升序）
		bool operator<(const Semiplane &sp) const { return !sign(angle(), sp.angle()) ? sp.contains(a) : sign(angle(), sp.angle()) < 0; }
		bool operator>(const Semiplane &sp) const { return !sign(angle(), sp.angle()) ? contains(sp.a) : sign(angle(), sp.angle()) > 0; }
		bool operator==(const Semiplane &sp) const { return a == sp.a && b == sp.b; }
		bool operator>=(const Semiplane &sp) const { return !(*this < sp); }
		bool operator<=(const Semiplane &sp) const { return !(*this > sp); }
		bool operator!=(const Semiplane &sp) const { return !(*this == sp); }
	};

	struct SemiplaneIntersection : public CircularContainer<vector<Semiplane>> // 半平面交类
	{
		using CircularContainer<vector<Semiplane>>::CircularContainer;
		SemiplaneIntersection getIntersection() const // 构造半平面交（半平面逆时针排列）
		{
			SemiplaneIntersection tmp(*this);
			sort(tmp.begin(), tmp.end());
			CircularContainer<deque<Line>> ans;
			for (size_t i = 0; i < tmp.size(); ++i)
			{
				if (i && !sign(tmp.at(i).angle(), tmp.at(i - 1).angle()))
					continue;
				while (ans.size() > 1 && tmp.at(i).Line::contains(ans.at(-2).intersectionWith(ans.at(-1))))
					ans.pop_back();
				while (ans.size() > 1 && tmp.at(i).Line::contains(ans.at(0).intersectionWith(ans.at(1))))
					ans.pop_front();
				ans.push_back(tmp.at(i));
			}
			while (ans.size() > 2 && ans.at(0).Line::contains(ans.at(-2).intersectionWith(ans.at(-1))))
				ans.pop_back();
			while (ans.size() > 2 && ans.at(-1).Line::contains(ans.at(0).intersectionWith(ans.at(1))))
				ans.pop_front();
			tmp.clear();
			for (auto i : ans)
				tmp.push_back(i);
			return tmp;
		}
		Polygon toConvex() const // 将半平面交转化为多边形（凸包）
		{
			Polygon ans;
			for (size_t i = 0; i < size(); ++i)
				ans.push_back(at(i).intersectionWith(at(i + 1)));
			return ans;
		}
	};
}; // namespace Geometry2D

// using namespace Geometry2D;
