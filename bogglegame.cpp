<<<<<<< HEAD
/*
#include <iostream>
#include <string>
using namespace std;

char board[5][5];
int cache[5][5][10];
string word;

int canFindWord(int y, int x, int wordIndex) {
	if ((x > 4) || (x < 0) || (y > 4) || (y < 0)) {
		return 0;
	}
	int &ret = cache[y][x][wordIndex];
	if (ret != -1) {
		return ret;
	}
	if (word.at(wordIndex) != board[y][x]) {
		return ret = 0;
	}
	wordIndex++;
	if (wordIndex >= word.size()) {
		return ret = 1;
	}
	return ret = (
		canFindWord(y - 1, x - 1, wordIndex) || canFindWord(y - 1, x, wordIndex) || canFindWord(y - 1, x + 1, wordIndex)
		|| canFindWord(y, x - 1, wordIndex) || canFindWord(y, x + 1, wordIndex)
		|| canFindWord(y + 1, x - 1, wordIndex) || canFindWord(y + 1, x, wordIndex) || canFindWord(y + 1, x + 1, wordIndex)
		);
}

int main() {
	int C;
	scanf_s("%d\n", &C);
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < 5; j++) {
			scanf_s("%c%c%c%c%c\n", &board[j][0], &board[j][1], &board[j][2], &board[j][3], &board[j][4]);
		}
		int N;
		scanf_s("%d\n", &N);
		for (int j = 0; j < N; j++) {
			memset(cache, -1, sizeof(cache));
			word.clear();
			getline(cin, word);
			bool isFound = false;
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					if (canFindWord(k, l, 0) == 1) {
						isFound = true;
						break;
					}
				}
				if (isFound) {
					break;
				}
			}
			if (isFound) {
				cout << word << " YES" << endl;
			}
			else {
				cout << word << " NO" << endl;
			}
		}
	}
	return 0;
}
*/
#include <iostream>
#include <string>
#include <string.h>
#pragma warning(disable:4996)

using namespace std;

char board[5][5];    // �Է¹��� ������
int cache[5][5][10];    // ��������� �����Ѵ�. memset���� -1�� �ʱ�ȭ �� ���. 1:����, 0:����
string word;    // ã�ƾ��� �ܾ�

				/*
				�ٽ� ��� �Լ�.
				(y,x) ����Ʈ���� word Index�� �ش��ϴ� �ܾ ã�´�.
				������ 1 ����, ���н� 0 ����.
				���� ������ ĳ�ÿ��� �����Ѵ�.
				*/
int canFindWord(int y, int x, int wordIndex) {
	/* ������ ��� ��� */
	if ((x > 4) || (x < 0) || (y > 4) || (y < 0)) {
		return 0;
	}

	int& ret = cache[y][x][wordIndex];    // �� �ڵ带 ���� ret == cache[y][x][wordIndex] �� �ȴ�.

										  /* ĳ�ÿ� �̹� ����� ���Ǿ� ������, �߰��� ������� �ʰ� �� ���� �״�� ����(Ȱ��)�Ѵ�. */
	if (ret != -1) {
		return ret;
	}

	/* ������� �� �Լ� �������� ���� �ٽ� ���� */

	/*
	word Index�� �ش��ϴ� �ܾ, ���� �����ǿ��� (y,x)�� �ִ� �ܾ�� �ٸ� ���. �̹� ���ۺ��� �۷����� ���. (ù���ں��� Ʋ�ȴ�)
	: 0�� �����ϸ� �� ���� ĳ�ÿ� �����Ѵ�.
	*/
	if (word.at(wordIndex) != board[y][x]) {
		return ret = 0;
	}

	/*
	������� �Դٴ� ����, �����ǿ��� ���� ��ġ (y,x)�� ���� ã������ �ܾ��� ù���ڰ� �ִٴ� ���̴�.
	(��μ� ������ �� �ִ�)
	*/

	wordIndex++;    // ���� ����(character)�� ã�� ����, index++

					/*
					index �� ������ ��� ��� (��� �� index�� �ش��ϴ� ���ڰ� ������ ���ڿ��� ���̴�)
					�׷��ٸ� ���ϴ� ���ڸ� �� ã�� ���̹Ƿ�
					: 1�� �����ϸ� �� ���� ĳ�ÿ� �����Ѵ�.
					*/
	if (wordIndex >= word.size()) {
		return ret = 1;
	}

	/*
	o o o
	o ��o
	o o o
	��(������ġ y,x)�� �������� ������ ��ǥ 8�� ��θ� ��ͷ� Ž���Ѵ�.
	�� �߿� �ϳ��� ã�� �ȴٸ� ������ ���̹Ƿ� OR ������ ��Ų��.
	: ��������� 0�̳� 1�� ���ϵǸ� �� ���� ĳ�ÿ� �����Ѵ�.
	*/
	return ret = (
		canFindWord(y - 1, x - 1, wordIndex) || canFindWord(y - 1, x, wordIndex) || canFindWord(y - 1, x + 1, wordIndex)
		|| canFindWord(y, x - 1, wordIndex) || canFindWord(y, x + 1, wordIndex)
		|| canFindWord(y + 1, x - 1, wordIndex) || canFindWord(y + 1, x, wordIndex) || canFindWord(y + 1, x + 1, wordIndex)
		);
}

int main() {
	/* �׽�Ʈ ���̽��� �� C */
	int C;
	scanf_s("%d\n", &C);

	for (int i = 0; i < C; i++) {
		/* ������ (board[5][5]) ���� */
		for (int j = 0; j < 5; j++) {
			scanf_s("%c%c%c%c%c\n", &board[j][0], &board[j][1], &board[j][2], &board[j][3], &board[j][4]);
		}

		/* ã�� �ܾ��� �� N */
		int N;
		scanf_s("%d\n", &N);

		for (int j = 0; j < N; j++) {
			memset(cache, -1, sizeof(cache));    // �ܾ ã�� ������ �� ������ ĳ�ø� -1�� �ʱ�ȭ���ش�.

												 /* ã�� �ܾ� word */
			word.clear();
			getline(cin, word);

			bool isFound = false;

			/*
			5X5 ���� ��� ���� ������� Ž���Ѵ�.
			�߽߰� isFound = true �ϸ�, ���� break�� ������ Ż��
			*/
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					if (canFindWord(k, l, 0) == 1) {
						isFound = true;
						break;
					}
				}
				if (isFound) {
					break;
				}
			}

			/* ����� ���� ��� */
			if (isFound) {
				cout << word << " YES" << endl;
			}
			else {
				cout << word << " NO" << endl;
			}
		}
	}

	return 0;
=======
/*
#include <iostream>
#include <string>
using namespace std;

char board[5][5];
int cache[5][5][10];
string word;

int canFindWord(int y, int x, int wordIndex) {
	if ((x > 4) || (x < 0) || (y > 4) || (y < 0)) {
		return 0;
	}
	int &ret = cache[y][x][wordIndex];
	if (ret != -1) {
		return ret;
	}
	if (word.at(wordIndex) != board[y][x]) {
		return ret = 0;
	}
	wordIndex++;
	if (wordIndex >= word.size()) {
		return ret = 1;
	}
	return ret = (
		canFindWord(y - 1, x - 1, wordIndex) || canFindWord(y - 1, x, wordIndex) || canFindWord(y - 1, x + 1, wordIndex)
		|| canFindWord(y, x - 1, wordIndex) || canFindWord(y, x + 1, wordIndex)
		|| canFindWord(y + 1, x - 1, wordIndex) || canFindWord(y + 1, x, wordIndex) || canFindWord(y + 1, x + 1, wordIndex)
		);
}

int main() {
	int C;
	scanf_s("%d\n", &C);
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < 5; j++) {
			scanf_s("%c%c%c%c%c\n", &board[j][0], &board[j][1], &board[j][2], &board[j][3], &board[j][4]);
		}
		int N;
		scanf_s("%d\n", &N);
		for (int j = 0; j < N; j++) {
			memset(cache, -1, sizeof(cache));
			word.clear();
			getline(cin, word);
			bool isFound = false;
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					if (canFindWord(k, l, 0) == 1) {
						isFound = true;
						break;
					}
				}
				if (isFound) {
					break;
				}
			}
			if (isFound) {
				cout << word << " YES" << endl;
			}
			else {
				cout << word << " NO" << endl;
			}
		}
	}
	return 0;
}
*/
#include <iostream>
#include <string>
#include <string.h>
#pragma warning(disable:4996)

using namespace std;

char board[5][5];    // �Է¹��� ������
int cache[5][5][10];    // ��������� �����Ѵ�. memset���� -1�� �ʱ�ȭ �� ���. 1:����, 0:����
string word;    // ã�ƾ��� �ܾ�

				/*
				�ٽ� ��� �Լ�.
				(y,x) ����Ʈ���� word Index�� �ش��ϴ� �ܾ ã�´�.
				������ 1 ����, ���н� 0 ����.
				���� ������ ĳ�ÿ��� �����Ѵ�.
				*/
int canFindWord(int y, int x, int wordIndex) {
	/* ������ ��� ��� */
	if ((x > 4) || (x < 0) || (y > 4) || (y < 0)) {
		return 0;
	}

	int& ret = cache[y][x][wordIndex];    // �� �ڵ带 ���� ret == cache[y][x][wordIndex] �� �ȴ�.

										  /* ĳ�ÿ� �̹� ����� ���Ǿ� ������, �߰��� ������� �ʰ� �� ���� �״�� ����(Ȱ��)�Ѵ�. */
	if (ret != -1) {
		return ret;
	}

	/* ������� �� �Լ� �������� ���� �ٽ� ���� */

	/*
	word Index�� �ش��ϴ� �ܾ, ���� �����ǿ��� (y,x)�� �ִ� �ܾ�� �ٸ� ���. �̹� ���ۺ��� �۷����� ���. (ù���ں��� Ʋ�ȴ�)
	: 0�� �����ϸ� �� ���� ĳ�ÿ� �����Ѵ�.
	*/
	if (word.at(wordIndex) != board[y][x]) {
		return ret = 0;
	}

	/*
	������� �Դٴ� ����, �����ǿ��� ���� ��ġ (y,x)�� ���� ã������ �ܾ��� ù���ڰ� �ִٴ� ���̴�.
	(��μ� ������ �� �ִ�)
	*/

	wordIndex++;    // ���� ����(character)�� ã�� ����, index++

					/*
					index �� ������ ��� ��� (��� �� index�� �ش��ϴ� ���ڰ� ������ ���ڿ��� ���̴�)
					�׷��ٸ� ���ϴ� ���ڸ� �� ã�� ���̹Ƿ�
					: 1�� �����ϸ� �� ���� ĳ�ÿ� �����Ѵ�.
					*/
	if (wordIndex >= word.size()) {
		return ret = 1;
	}

	/*
	o o o
	o ��o
	o o o
	��(������ġ y,x)�� �������� ������ ��ǥ 8�� ��θ� ��ͷ� Ž���Ѵ�.
	�� �߿� �ϳ��� ã�� �ȴٸ� ������ ���̹Ƿ� OR ������ ��Ų��.
	: ��������� 0�̳� 1�� ���ϵǸ� �� ���� ĳ�ÿ� �����Ѵ�.
	*/
	return ret = (
		canFindWord(y - 1, x - 1, wordIndex) || canFindWord(y - 1, x, wordIndex) || canFindWord(y - 1, x + 1, wordIndex)
		|| canFindWord(y, x - 1, wordIndex) || canFindWord(y, x + 1, wordIndex)
		|| canFindWord(y + 1, x - 1, wordIndex) || canFindWord(y + 1, x, wordIndex) || canFindWord(y + 1, x + 1, wordIndex)
		);
}

int main() {
	/* �׽�Ʈ ���̽��� �� C */
	int C;
	scanf_s("%d\n", &C);

	for (int i = 0; i < C; i++) {
		/* ������ (board[5][5]) ���� */
		for (int j = 0; j < 5; j++) {
			scanf_s("%c%c%c%c%c\n", &board[j][0], &board[j][1], &board[j][2], &board[j][3], &board[j][4]);
		}

		/* ã�� �ܾ��� �� N */
		int N;
		scanf_s("%d\n", &N);

		for (int j = 0; j < N; j++) {
			memset(cache, -1, sizeof(cache));    // �ܾ ã�� ������ �� ������ ĳ�ø� -1�� �ʱ�ȭ���ش�.

												 /* ã�� �ܾ� word */
			word.clear();
			getline(cin, word);

			bool isFound = false;

			/*
			5X5 ���� ��� ���� ������� Ž���Ѵ�.
			�߽߰� isFound = true �ϸ�, ���� break�� ������ Ż��
			*/
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					if (canFindWord(k, l, 0) == 1) {
						isFound = true;
						break;
					}
				}
				if (isFound) {
					break;
				}
			}

			/* ����� ���� ��� */
			if (isFound) {
				cout << word << " YES" << endl;
			}
			else {
				cout << word << " NO" << endl;
			}
		}
	}

	return 0;
>>>>>>> c163b3a9c7fbfa6c637a042e8c9a9274dc6f4f4f
}