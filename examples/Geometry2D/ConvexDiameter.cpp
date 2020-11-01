// Problem: https://www.luogu.com.cn/problem/P1452

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
		int x, y;
		scanf("%d%d", &x, &y);
		p.push_back(Point(x, y));
	}
	printf("%lld", (long long)p.convexHull().convexDiameterSquare());
	return 0;
}
