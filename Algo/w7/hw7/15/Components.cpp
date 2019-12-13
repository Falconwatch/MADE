#include"Components.h"

Components::Components(int n) : n(n)
{
	parents = new int[n + 1];
	ranks = new int[n + 1];

	for (int i = 0; i <= n; i++)
	{
		ranks[i] = 0;
		parents[i] = i;
	}
}

int Components::Find(int u)
{
	//ищем родителя заданной вершины рекурсивно
	if (u != parents[u])
		parents[u] = Find(parents[u]);
	return parents[u];
}

void Components::Merge(int x, int y)
{
	x = Find(x), y = Find(y);
	//присоединяем маньшее дерево к большему
	if (ranks[x] > ranks[y])
		parents[y] = x;
	else
		parents[x] = y;

	if (ranks[x] == ranks[y])
		ranks[y]++;
}
