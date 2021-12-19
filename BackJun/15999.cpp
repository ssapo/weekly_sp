#include "bits/stdc++.h"
using namespace std;

bool IsIsolated(vector<int>& InArr, int currI, int currJ, int N, int M)
{
	int Vectors[4][2]{ {1,0}, {-1,0}, {0,1}, {0,-1} };
	int IsolatedCount = 0;
	for (int I = 0; I < 4; ++I)
	{
		int NY = currI + Vectors[I][0];
		int NX = currJ + Vectors[I][1];

		if (NY >= 0 && NY < N && NX >= 0 && NX < M)
		{
			int NewIndex = NY * M + NX;
			int CurIndex = currI * M + currJ;
			if (InArr[NewIndex] == InArr[CurIndex])
				++IsolatedCount;
			else
				return false;
		}
		else
			++IsolatedCount;
	}

	return IsolatedCount == 4;
}

int Pow(int X, int Y)
{
	int Sum = 1;
	for (int I = 0; I < Y; ++I)
	{
		Sum = (Sum * 2) % 1000000007;
	}
	return Sum;
}

int main()
{
	int N = 0;
	int M = 0;
	cin >> N >> M;

	vector<int> Temp;
	for (int I = 0; I < N; ++I)
	{
		char Ms[2001] = { 0, };
		cin >> Ms;

		for (int J = 0; J < M; ++J)
		{
			if (Ms[J] == 'W')
				Temp.emplace_back(1);
			else
				Temp.emplace_back(0);
		}
	}

	int Count = 0;
	for (int I = 0; I < N; ++I)
		for (int J = 0; J < M; ++J)
			if (IsIsolated(Temp, I, J, N, M))
				Count++;

	cout << Pow(2, Count) << endl;

	return 0;
}