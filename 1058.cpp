#include <iostream>

using namespace std;

int N, friendNum[51] = { 0, };
string person[51];

void calFriendNum() {
	for (int i = 0; i < N; i++) {
		int friendArr[51] = { 0, }, n = 0;
		for (int j = 0; j < N; j++) { // ���� B��� �� ��
			if (j == i) continue;
			if (person[i][j] == 'Y') { //i = B, j = other
				friendNum[i]++;
				friendArr[n++] = j; // B�� ģ�� ���
			}
		}

		for (int j = 0; j < N; j++) // ���� B��� �� ��
			if (person[i][j] == 'N') { //�������� ģ���� �ƴ����� �ٸ� ģ���� ģ���� ���
				if (j == i)continue;
				for (int k = 0; k < n; k++) if (person[j][friendArr[k]] == 'Y') {
					friendNum[i]++;
					break;
				}
			}
	}
}

int main() {
	int max = 0, num;
	cin >> N;
	for (int i = 0; i < N; i++) cin >> person[i];
	calFriendNum();
	for (int i = 0; i < N; i++) if (max < friendNum[i]) max = friendNum[i];
	cout << max << endl;
	return 0;
}