#include <iostream>
using namespace std;

int n;
int blue[4][6] = { 0, };
int green[6][4] = { 0, };
int ans = 0;

void push_blue_block() {
	// �Ķ��� ���� ����� �ı��� �� �����ִ� ����� �Ʒ��� ������
	bool changeBlue;
	do {
		changeBlue = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// ��Ͽ� ����� ��ȣ�� 1 �Ǵ� 2�� ��
				if (blue[j][i] == 1 || blue[j][i] == 2) {
					if (blue[j][i + 1] == 0) {
						swap(blue[j][i], blue[j][i + 1]);
						changeBlue = true;
					}
				}
				// ��Ͽ� ����� ��ȣ�� 3�� ��
				else if (blue[j][i] == 3) {
					if (blue[j][i + 1] == 0 && blue[j + 1][i + 1] == 0) {
						swap(blue[j][i], blue[j][i + 1]);
						swap(blue[j + 1][i], blue[j + 1][i + 1]);
						changeBlue = true;
					}
					j++;
				}
			}
		}
	} while (changeBlue);
}

void push_green_block() {
	// �ʷϻ� ���� ����� �ı��� �� �����ִ� ����� �Ʒ��� ������
	bool changeGreen;
	do {
		changeGreen = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// ��Ͽ� ����� ��ȣ�� 1 �Ǵ� 3�� ��
				if (green[i][j] == 1 || green[i][j] == 3) {
					if (green[i + 1][j] == 0) {
						swap(green[i][j], green[i + 1][j]);
						changeGreen = true;
					}
				}
				// ��Ͽ� ����� ��ȣ�� 2�� ��
				else if (green[i][j] == 2) {
					if (green[i + 1][j] == 0 && green[i + 1][j + 1] == 0) {
						swap(green[i][j], green[i + 1][j]);
						swap(green[i][j + 1], green[i + 1][j + 1]);
						changeGreen = true;
					}
					j++;
				}
			}
		}
	} while (changeGreen);
}

bool break_blue() {
	// �Ķ��� �������� �� ���� �ϼ��� ���� ������ �� ����
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;
		for (int j = 0; j < 4; j++) {
			check &= (blue[j][i] > 0);
		}

		// �� �� �ϼ��� �� �� ����
		if (check) {	
			blue[0][i] = blue[1][i] = blue[2][i] = blue[3][i] = 0;
			tetris = true;
			ans++;
		}
	}
	return tetris;
}

bool break_green() {
	// �ʷϻ� �������� �� ���� �ϼ��� ���� ������ �� ����
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;
		for (int j = 0; j < 4; j++) {
			check &= (green[i][j] > 0);
		}
		// �� �� �ϼ��� �� �� ����
		if (check) {
			green[i][0] = green[i][1] = green[i][2] = green[i][3] = 0;
			tetris = true;
			ans++;
		}
	}
	return tetris;
}
// blue �� ���� ������ ����� ���� ������
// ���� ������ ����� ���� �������� �����̱� ������ �������� ���� ��������
void put_blue_block(int t, int x, int y) {
	// blue ��� ����
	if (t == 1) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) blue[x][i] = 1;
			else if (blue[x][i + 1] > 0) {
				blue[x][i] = 1;
				break;
			}
		}
	}
	else if (t == 2) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) blue[x][i] = blue[x][i - 1] = 2;
			else if (blue[x][i + 1] > 0) {
				blue[x][i] = blue[x][i - 1] = 2;
				break;
			}
		}
	}
	else if (t == 3) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) blue[x][i] = blue[x + 1][i] = 3;
			else if (blue[x][i + 1] > 0 || blue[x + 1][i + 1] > 0) {
				blue[x][i] = blue[x + 1][i] = 3;
				break;
			}
		}
	}
}

// green �� ���� ������ ����� ���� ������
// ���� ������ ����� ���� �������� �����̱� ������ �������� ���� ��������
void put_green_block(int t, int x, int y) {
	// green ��� ����
	if (t == 1) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) green[i][y] = 1;
			else if (green[i + 1][y] > 0) {
				green[i][y] = 1;
				break;
			}
		}
	}
	else if (t == 2) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) green[i][y] = green[i][y + 1] = 2;
			else if (green[i + 1][y] > 0 || green[i + 1][y + 1] > 0) {
				green[i][y] = green[i][y + 1] = 2;
				break;
			}
		}
	}
	else if (t == 3) {
		for (int i = 1; i < 6; i++) {
			if (i == 5) green[i][y] = green[i - 1][y] = 3;
			else if (green[i + 1][y] > 0) {
				green[i][y] = green[i - 1][y] = 3;
				break;
			}
		}
	}
}

int main(void) {
	// ù �� n �� �Է� �ޱ�
	cin >> n;

	// n�� �ݺ�
	for (int i = 0; i < n; i++) {	
		int t, x, y;

		// t, x, y �Է� ����
		cin >> t >> x >> y;

		// �Ķ���, �ʷϻ� ������ ��� ��ġ
		put_blue_block(t, x, y);
		put_green_block(t, x, y);

		// ��Ʈ���� �ϼ� �� �� �� �μ���, ���� �ִ� ��� ������ �ݺ�
		while (break_blue()) {
			push_blue_block();
		}
		while (break_green()) {
			push_green_block();
		}
	}

	// �Ķ��� ���
	cout << "�Ķ��� Ÿ�� ��Ȳ" << endl;
	int col = sizeof(blue[0]) / sizeof(int);
	int row = sizeof(blue) / sizeof(blue[0]);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << blue[i][j];
		}
		cout << endl;
	}

	// �ʷϻ� ���
	cout << "�ʷϻ� Ÿ�� ��Ȳ" << endl;
	int col_green = sizeof(green[0]) / sizeof(int);
	int row_green = sizeof(green) / sizeof(green[0]);

	for (int i = 0; i < row_green; i++) {
		for (int j = 0; j < col_green; j++) {
			cout << green[i][j];
		}
		cout << endl;
	}
}