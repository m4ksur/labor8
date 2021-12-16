#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cmath>
#include <stack>
#include <queue>


using namespace std;

int max_size = 7, i, j, start, num, mass_ex[30], D = 0, R = 1000, perif, center, elem = 0;
int* DIST = (int*)malloc(max_size * sizeof(int));
queue<int> ex;

void BSFD(int st, int** b, int num_of_elem, int* vis) {
	queue<int> Q;
	int t;
	Q.push(st);
	vis[st] = 0;

	while (!Q.empty())
	{
		t = Q.front();
		Q.pop();
		for (int i = 0; i < num_of_elem; i++)
		{
			if (b[t][i] > 0 && vis[i] == 1000)
			{
				vis[i] = vis[t] + b[t][i];
				Q.push(i);
			}
		}
	}
}

void max_elem(int* mass) {
	int max = 0, n;
	for (n = 0; n < max_size; n++) {
		if (mass[n] > max and mass[n] != 1000)
			max = mass[n];
	}
	ex.push(max);
}

int main() {

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	int** a = new int* [max_size];
	for (i = 0; i < max_size; i++)
	{
		a[i] = new int[max_size];
	}

	for (i = 0; i < max_size; i++)
	{
		for (j = i + 1; j < max_size; j++)
		{
			num = rand() % 8;
			if (num <= 4)
			{
				a[i][j] = 0;
				a[j][i] = a[i][j];
			}
			else
			{
				a[i][j] = (rand() % 6) + 1;
				a[j][i] = a[i][j];
			}
		}
	}
	printf("\nНеориентированный граф:\n");
	for (i = 0; i < max_size; i++)
	{
		DIST[i] = 1000;
		for (j = 0; j < max_size; j++)
		{
			if (i == j)
				a[i][j] = 0;
			printf("%2d", a[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < max_size; i++) {
		BSFD(i, a, max_size, DIST);
		max_elem(DIST);
		printf("\nРасстояния из %d-й вершины: ", i + 1);
		for (j = 0; j < max_size; j++) {
			printf("%4d ", DIST[j]);
			DIST[j] = 1000;
		}
	}

	printf("\n\nЭксицентритеты вершин:\n");
	for (i = 0; i < max_size; i++) {
		if (!ex.empty()) {
			mass_ex[i] = ex.front();
			printf("%d-й = %d\n", i + 1, mass_ex[i]);
			ex.pop();
		}
	}

	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] > D)
			D = mass_ex[i];
		if (mass_ex[i] < R)
			R = mass_ex[i];
	}
	printf("Диаметр графа = %d\nРадиус графа = %d", D, R);

	printf("\nПерифирийные вершины: ");
	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] == D)
			printf("%d ", i + 1);
	}
	printf("\nЦентральные вершины: ");
	for (i = 0; i < max_size; i++) {
		if (mass_ex[i] == R)
			printf("%d ", i + 1);
	}

	//изолированные, концевые и доминирующие вершины
	printf("\n\nКонцевые вершины:");
	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < max_size; j++)
		{
			if (a[i][j] > 0)
				elem++;
		}
		if (elem == 1)
			printf("%d ", i + 1);
		elem = 0;
	}

	printf("\nИзолированные вершины:");
	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < max_size; j++)
		{
			if (a[i][j] > 0)
				elem++;
		}
		if (elem == 0)
			printf("%d ", i + 1);
		elem = 0;
	}

	printf("\nДоминирующие вершины:");
	for (i = 0; i < max_size; i++)
	{
		for (j = 0; j < max_size; j++)
		{
			if (a[i][j] > 0)
				elem++;
		}
		if (elem == max_size - 1)
			printf("%d ", i + 1);
		elem = 0;
	}
}
