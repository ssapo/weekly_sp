#include "bits/stdc++.h"
using namespace std;

//https://www.acmicpc.net/problem/1260

//문제
//그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오.
//단, 방문할 수 있는 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고, 
//더 이상 방문할 수 있는 점이 없는 경우 종료한다.정점 번호는 1번부터 N번까지이다.

//입력
//첫째 줄에 정점의 개수 N(1 ≤ N ≤ 1, 000), 
//간선의 개수 M(1 ≤ M ≤ 10, 000), 탐색을 시작할 정점의 번호 V가 주어진다.
//다음 M개의 줄에는 간선이 연결하는 두 정점의 번호가 주어진다.
//어떤 두 정점 사이에 여러 개의 간선이 있을 수 있다.입력으로 주어지는 간선은 양방향이다.

#define MAX_VALUE 1001            //'N이 1~1000 이므로 1000번째 인덱스에 접근 -> 크기 1001까지 선언
int N, M, V;                    //노드 개수, 간선 개수, 시작할 노드 번호
int mat[MAX_VALUE][MAX_VALUE];    //인접행렬 배열 선언
int visit[MAX_VALUE];            //visit 배열 default 는 0으로. . . 

void dfs(int v) {

	cout << v << ' ';
	visit[v] = 1;            //방문한 노드를 visit 0에서 1로 변경
	for (int i = 1; i <= N; i++) {
		if (visit[i] == 1 || mat[v][i] == 0)
			continue;
		dfs(i);                //dfs에서 재귀를 사용
	}
}

void bfs(int v) {
	queue<int> q;            //bfs에서는 q를사용
	q.push(v);
	visit[v] = 0;            //방문한 노드를 visit 1에서 0으로 변경
	while (!q.empty()) {
		v = q.front();
		cout << q.front() << ' ';
		q.pop();
		for (int i = 1; i <= N; i++) {
			if (visit[i] == 0 || mat[v][i] == 0)
				continue;
			q.push(i);
			visit[i] = 0;
		}
	}
}

int main() {
	int x, y;
	cin >> N >> M >> V;            //N은 노드개수, M은 간선의개수, V는 처음 위치의 기준이 되는 노드
	for (int i = 0; i < M; i++) {    //간선의 개수만큼 서로 이어줄 x와 y노드를 입력받습니다.
		cin >> x >> y;
		mat[x][y] = mat[y][x] = 1;    //인접행렬 표시
	}
	dfs(V);
	cout << '\n';
	bfs(V);
	return 0;
}
