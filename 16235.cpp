#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
int food[11][11] = { 5, };
int addFood[11][11] = { 0, };
int dir[8][2] = {
	{-1, -1},
	{-1 , 0},
	{-1, 1},
	{0, -1},
	{0, 1},
	{1, -1},
	{1, 0},
	{1, 1}
};
vector<int> treeList[11][11];

/*
��: � �������� �ڽ��� ���̸�ŭ ����� �԰� ���� 1 ����. ����� ������ ���̸�ŭ ���� �� ���ٸ� ����
����: ���� ������ ������� ����. ���̸� 2�� ���� ���� ������� �߰���
����: ���� ����. �����Ϸ��� ���̰� 5�� ������� �ϸ� ������ 8���� ĭ�� ���̰� 1�� ���� ����
�ܿ� : �κ��� ���ƴٴϸ� ���� ��� �߰�. �� ĭ�� �߰� �Ǵ� ��� ���� A[r][c]
*/
void breed(int y, int x) {
	for (int i = 0; i < 8; i++) {
		int ny = y + dir[i][0], nx = x + dir[i][1];
		if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
		treeList[ny][nx].push_back(1);
	}
}

void springAndSummer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//spring
			if (treeList[i][j].empty()) continue;
			vector<int> livingTree;
			int deadTreeFood = 0;
			sort(treeList[i][j].begin(), treeList[i][j].end());
			for (int k = 0; k < treeList[i][j].size(); k++) {
				if (treeList[i][j][k] <= food[i][j]) {
					food[i][j] -= treeList[i][j][k];
					treeList[i][j][k]++;
					livingTree.push_back(treeList[i][j][k]);
				}
				else deadTreeFood += treeList[i][j][k] / 2;
			}
			treeList[i][j].clear();
			for (int k = 0; k < livingTree.size(); k++) {
				treeList[i][j].push_back(livingTree[k]);
			}
			//summer
			food[i][j] += deadTreeFood;
		}
	}
}

void autumn() {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 0; k < treeList[i][j].size(); k++)
				if (treeList[i][j][k] % 5 == 0) breed(i, j);
}

void winter() {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			food[i][j] += addFood[i][j];
}

int main() {
	cin >> N >> M >> K;
	int r, c, z;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			cin >> addFood[i][j];
			food[i][j] = 5;
		}

	for (int i = 0; i < M; i++) {
		cin >> r >> c >> z;
		treeList[r][c].push_back(z);
	}

	while (K--) {
		springAndSummer();
		autumn();
		winter();
	}

	int sum = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			sum += treeList[i][j].size();

	cout << sum;
	return 0;
}