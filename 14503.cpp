#include <iostream>

using namespace std;

int N, M, d, r, c, arr[51][51] = { 0, }, isClean[51][51] = { 0, };
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int ans = 0, flag = 1;

int rotate(int cnt) {
	int n = d;
	while (cnt--) {
		--n;
		if (n < 0) n = 3;
	}
	return n;
}

void clean() {
	int cnt = 0;
	while(flag) {
		isClean[r][c] = 1, ans++, cnt = 0; // 1��
		while (1) { // 2��
			int x = r + dir[rotate(1)][0], y = c + dir[rotate(1)][1];
			int range = x >= 0 && x < N && y >= 0 && y < M;
			if (!isClean[x][y] && !arr[x][y] && range) { // 2.a
				d = rotate(1); // �������� ȸ��
				r = x, c = y; // 1ĭ ����
				break; // 1������ ����
			}
			else if ((isClean[x][y] || arr[x][y]) && range) { // 2.b
				if (cnt == 4) { // 2.c , 2.d
					if (!arr[r - dir[d][0]][c - dir[d][1]]) { // 2.c
						r = r - dir[d][0], c = c - dir[d][1]; // ����
						cnt = 0;
						continue; // 2������
					}
					else { // 2.d
						flag = 0;
						break;
					}
				}
				d = rotate(1); // �������� ȸ��
				cnt++;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
			isClean[i][j] = arr[i][j];
		}
	}
	clean();
	cout << ans;
	return 0;
}