// Problem: https://www.luogu.com.cn/problem/P4196

#include <bits/stdc++.h>
#include "Geometry2D/Point.h"
#include "Geometry2D/Polygon.h"
#include "Geometry2D/Semiplane.h"
#include "Geometry2D/Semiplanes.h"

using namespace std;
using namespace Geometry;
using namespace Geometry2D;

int main()
{
	Polygon p;
	Semiplanes sps;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		int m;
		scanf("%d", &m);
		p.clear();
		for (int j = 0; j < m; ++j)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			p.push_back(Point(x, y));
		}
		for (int j = 0; j < m; ++j)
			sps.push_back(Semiplane(p.at(j), p.at(j + 1)));
	}
	printf("%.3lf", ((Polygon)sps.intersection()).area());
	return 0;
}
