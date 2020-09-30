#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct pos {
	int y;
	int x;
	int dist;
	pos(int Y, int X, int Dist) : y(Y), x(X), dist(Dist) {};
};

int N, M, shark_size = 2, eaten_fish = 0, cur_y = 0, cur_x = 0, total_time = 0;
int map[21][21] = { 0, };
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<pos>fishes;

void eating(int ey, int ex, int y, int x, int dist) {
	map[ey][ex] = 0;
	map[y][x] = 9;
	cur_y = y, cur_x = x;
	total_time += dist;
	eaten_fish++;
	fishes.clear();
	if (eaten_fish == shark_size) {
		shark_size++;
		eaten_fish = 0;
	}
}

int BFS(int target_y, int target_x, int y, int x) {
	queue<pair<pair<int, int>, int>> q;
	int visited[21][21] = { 0, };
	q.push(make_pair(make_pair(y, x), 0));
	visited[y][x] = 1;
	while (!q.empty()) {
		int ey = q.front().first.first, ex = q.front().first.second, distance = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_y = ey + dir[i][0], next_x = ex + dir[i][1];
			if (next_y < 0 || next_y >= N || next_x < 0 || next_x >= N) continue;
			if (next_y == target_y && next_x == target_x) return distance + 1;
			if (map[next_y][next_x] <= shark_size && !visited[next_y][next_x]) {
				q.push(make_pair(make_pair(next_y, next_x), distance + 1));
				visited[next_y][next_x] = 1;
			}
		}
	}
	return 0;
}

void canMove(int target_y, int target_x, int y, int x) {
	int dist = BFS(target_y, target_x, y, x);
	if (dist) fishes.push_back(pos(target_y, target_x, dist));
}

void eatFish(int y, int x) {
	//���� 1�̸� �ٷ� �Դ´�.
	if (fishes.size() == 1) eating(y, x, fishes[0].y, fishes[0].x, fishes[0].dist);
	//������ ���� ���� ���
	else {
		vector<pos>topFishes;
		int topMost = 20, leftMost = 20, minDist = fishes[0].dist, totalCnt = fishes.size(), cnt = 0, topCnt = 0;
		for (int i = 0; i < totalCnt; i++) {
			if (fishes[i].dist != minDist) break;
			if (topMost > fishes[i].y) topMost = fishes[i].y; // �ֻ�� y ��ǥ ����
			cnt++;
		}

		for (int i = 0; i < cnt; i++) //�ֻ�� ��ǥ�� �ִ� ����� �߰�
			if (fishes[i].y == topMost) {
				topCnt++;
				topFishes.push_back(fishes[i]);
				if (leftMost > fishes[i].x) leftMost = fishes[i].x;// ���´� x ��ǥ ����
			}
		if (topFishes.size() == 1) // �ֻ�� ��ǥ�� 1������ ���� ��� �ٷ� �Ա�
			eating(y, x, topFishes[0].y, topFishes[0].x, topFishes[0].dist);
		else { // �ֻ�� ��ǥ�� ���� ������ ��� ���´� ����� �Ա�
			for (int i = 0; i < topCnt; i++) {
				if (leftMost == topFishes[i].x) {
					eating(y, x, topFishes[i].y, topFishes[i].x, topFishes[i].dist);
					break;
				}
			}
		}
	}
	return;
}

bool compare(pos a, pos b) {
	return a.dist < b.dist;
}

int checkFishes(int y, int x) {
	int distance = 1;
	while (1) {
		if (distance > 2 * N) break;
		for (int i = 0; i <= distance; i++) {
			int j = distance - i;
			int a = y - i, b = y + i;
			if (a >= 0) {
				if (x - j >= 0 && map[a][x - j] < shark_size && map[a][x - j]) canMove(a, x - j, y, x);
				if (x + j < N && map[a][x + j] < shark_size && map[a][x + j]) canMove(a, x + j, y, x);
			}
			if (b < N) {
				if (x - j >= 0 && map[b][x - j] < shark_size && map[b][x - j]) canMove(b, x - j, y, x);
				if (x + j < N && map[b][x + j] < shark_size && map[b][x + j]) canMove(b, x + j, y, x);
			}
		}
		distance++;
	}
	if (fishes.size() != 0) {
		sort(fishes.begin(), fishes.end(), compare);
		eatFish(y, x);
		return 1;
	}
	return 0;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				cur_y = i, cur_x = j;
			}
		}
	}

	while(checkFishes(cur_y, cur_x));
	cout << total_time;
	return 0;
}