#include "bits/stdc++.h"
using namespace std;

#define SIZE 2090

short arr[3][SIZE];

void fib(short a[], short b[], short ab[])
{
	int add = 0;

	for (int i = 0; i <= SIZE; i++)
	{
		ab[i] = a[i] + b[i] + add;
		if (add != 0) add = 0;

		if (ab[i] >= 10)
		{
			add = ab[i] / 10;
			ab[i] %= 10;
		}
	}
}

int main()
{
	int n, cnt = SIZE - 1;
	cin >> n;

	arr[1][0] = 1;

	for (int i = 2; i <= n; i++)
		fib(arr[(i - 2) % 3], arr[(i - 1) % 3], arr[i % 3]);

	while (cnt >= 0 && arr[n % 3][cnt] == 0)
	{
		cnt--;
	}

	if (cnt < 0) cnt = 0;

	for (int i = cnt; i >= 0; i--) cout << arr[n % 3][i];

	return 0;
}