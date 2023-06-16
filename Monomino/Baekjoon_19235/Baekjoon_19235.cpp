#include <iostream>
using namespace std;

int n;
int blue[4][6] = { 0, };
int green[6][4] = { 0, };
int ans = 0;

void push_blue_block() {
	// 파란색 구역 블록이 파괴된 후 남아있는 블록이 아래로 내려옴
	bool changeBlue;
	do {
		changeBlue = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// 블록에 저장된 번호가 1 또는 2일 때
				if (blue[j][i] == 1 || blue[j][i] == 2) {
					if (blue[j][i + 1] == 0) {
						swap(blue[j][i], blue[j][i + 1]);
						changeBlue = true;
					}
				}
				// 블록에 저장된 번호가 3일 때
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
	// 초록색 구역 블록이 파괴된 후 남아있는 블록이 아래로 내려옴
	bool changeGreen;
	do {
		changeGreen = false;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				// 블록에 저장된 번호가 1 또는 3일 때
				if (green[i][j] == 1 || green[i][j] == 3) {
					if (green[i + 1][j] == 0) {
						swap(green[i][j], green[i + 1][j]);
						changeGreen = true;
					}
				}
				// 블록에 저장된 번호가 2일 때
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
	// 파란색 구역에서 한 줄이 완성된 것이 존재할 시 삭제
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;
		for (int j = 0; j < 4; j++) {
			check &= (blue[j][i] > 0);
		}

		// 한 줄 완성될 시 열 삭제
		if (check) {	
			blue[0][i] = blue[1][i] = blue[2][i] = blue[3][i] = 0;
			tetris = true;
			ans++;
		}
	}
	return tetris;
}

bool break_green() {
	// 초록색 구역에서 한 줄이 완성된 것이 존재할 시 삭제
	bool tetris = false;
	for (int i = 2; i < 6; i++) {
		bool check = true;
		for (int j = 0; j < 4; j++) {
			check &= (green[i][j] > 0);
		}
		// 한 줄 완성될 시 열 삭제
		if (check) {
			green[i][0] = green[i][1] = green[i][2] = green[i][3] = 0;
			tetris = true;
			ans++;
		}
	}
	return tetris;
}
// blue 의 연한 구역에 블록을 놓는 시작점
// 연한 구역에 블록이 없을 때까지만 움직이기 때문에 시작점은 연한 구역부터
void put_blue_block(int t, int x, int y) {
	// blue 블록 놓기
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

// green 의 연한 구역에 블록을 놓는 시작점
// 연한 구역에 블록이 없을 때까지만 움직이기 때문에 시작점은 연한 구역부터
void put_green_block(int t, int x, int y) {
	// green 블록 놓기
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
	// 첫 줄 n 값 입력 받기
	cin >> n;

	// n번 반복
	for (int i = 0; i < n; i++) {	
		int t, x, y;

		// t, x, y 입력 받음
		cin >> t >> x >> y;

		// 파란색, 초록색 구역에 블록 배치
		put_blue_block(t, x, y);
		put_green_block(t, x, y);

		// 테트리스 완성 시 그 줄 부수고, 위에 있는 블록 내리고 반복
		while (break_blue()) {
			push_blue_block();
		}
		while (break_green()) {
			push_green_block();
		}
	}

	// 파란색 출력
	cout << "파란색 타일 상황" << endl;
	int col = sizeof(blue[0]) / sizeof(int);
	int row = sizeof(blue) / sizeof(blue[0]);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << blue[i][j];
		}
		cout << endl;
	}

	// 초록색 출력
	cout << "초록색 타일 상황" << endl;
	int col_green = sizeof(green[0]) / sizeof(int);
	int row_green = sizeof(green) / sizeof(green[0]);

	for (int i = 0; i < row_green; i++) {
		for (int j = 0; j < col_green; j++) {
			cout << green[i][j];
		}
		cout << endl;
	}
}