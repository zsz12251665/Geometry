// Problem: https://www.luogu.com.cn/problem/P2742

#include <bits/stdc++.h>
#include "Geometry2D/Point.h"
#include "Geometry2D/Polygon.h"

using namespace std;
using namespace Geometry;
using namespace Geometry2D;

int main()
{
	Polygon p;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		p.push_back(Point(x, y));
	}
	printf("%.2lf", p.convexHull().circumference());
	return 0;
}
