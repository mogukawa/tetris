#include <iostream>
#include <windows.h>
#include <conio.h>

typedef struct {
	int mino1[5][5][5];
}MINO;

static int data[20][10];
int angle = 0;
int random;
int y = 1;
int x = 0;
int startx = 3;
int starty = 0;
int ch;
int score = 0;
int minodata[5][5];
bool gameover = false;
bool isground = false;
bool add = false;

MINO mino = { { { {0,0,0,0,0}, {0,0,0,0,0}, {1,1,1,1,1}, {0,0,0,0,0}, {0,0,0,0,0} },
{ {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,0,0}, {0,0,1,1,0}, {0,0,0,0,0} },
{ {0,0,0,0,0}, {0,0,1,0,0}, {0,1,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0} },
{ {0,0,0,0,0}, {0,1,1,0,0}, {0,0,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0} },
{ {0,0,0,0,0}, {0,0,1,1,0}, {0,0,1,1,0}, {0,0,0,0,0}, {0,0,0,0,0} }} };


int reset(int blocktype) {
	for (int h = 0;h < 20;h++) {
		for (int w = 0; w < 20; w++)
		{
			if (data[h][w] == blocktype) {
				data[h][w] = 0;
			}
		}
	}
	return 0;
}


void rotate() {
	if (y + 3 < 16) {
		if (angle == 0) {
			for (int h = 0;h < 5;h++) {
				for (int w = 0;w < 5;w++) {
					minodata[h][w] = mino.mino1[random][h][w];
				}
			}
		}
		else if (angle == 1) {
			for (int h = 0;h < 5;h++) {
				for (int w = 0;w < 5;w++) {
					minodata[4 - w][h] = mino.mino1[random][h][w];
				}
			}
		}
		else if (angle == 2) {
			for (int h = 0;h < 5;h++) {
				for (int w = 0;w < 5;w++) {
					minodata[h][4 - w] = mino.mino1[random][h][w];
				}
			}
		}
		else {
			for (int h = 0;h < 5;h++) {
				for (int w = 0;w < 5;w++) {
					minodata[w][h] = mino.mino1[random][h][w];
				}
			}
		}
	}
}

//新しいミノを追加
void newmino() {
	y = starty;
	x = startx;
	angle = 0;
	int temp;
	random  = 0;
	for (int h = 0;h < 5;h++) {
		for (int w = 0; w < 5; w++)
		{
			temp = mino.mino1[random][h][w];
			minodata[h][w] = temp;
			data[h + y][w + x] = temp;
			
			
		}
	}
}
//画面を配列として保存
void save() {
	for (int h = 0;h < 5;h++) {
		for (int w = 0; w < 5; w++)
		{
			if(isground)
			{
				if (minodata[h][w] == 1) {
					data[h + y][w + x] = 2;
				}
			}else if (h + y + 1 < 20 && w + x < 11 && -1 < w + x) {

				if (data[h + y + 1][w + x] == 2) {
					if (minodata[h][w] == 1) {
						data[h + y][w + x] = 2;
						isground = true;
					}
				}
				else if (minodata[h][w] == 1) {
					data[h + y][w + x] = minodata[h][w];
				}
			}
			else {
				if(minodata[h][w] == 1) {
					data[h + y][w + x] = 2;
					isground = true;
				}
			}

		}
	}
}

//出力
void output() {
	system("cls");
	for (int h = 0;h < 20;h++) {
		for (int w = 0; w < 10; w++)
		{
			//printf("%d", data[h][w]);
			if (w == 9) {
				if (data[h][w] == 0) {
					printf(" \n");
				}
				else {
					printf("■\n");
				}
			}
			else {
				if (data[h][w] == 0) {
					printf(" ");
				}
				else {
					printf("■");
				}
			}
		}
	}
}

void addscore() {
	int i = 0;
	int j = 0;
	for (int h = 0;h < 20;h++) {
		for (int w = 0; w < 10;w++) {			
			if (!(add) && data[h][w] == 2) {
				i++;
			}
		}
		if (i == 10) {
			j++;
			score = 50 *j;
			for (int a = 0;a < 10;a++) {
				data[h][a] = 0;
			}
		}
		int i = 0;
	}
}

void key() {
	if (_kbhit()) {
		ch = _getch();
	}
	else {
		ch = 0;
	}
	if (ch == 'd'&& x < 5) {
		x++;
	}
	if (ch == 'a' && x > 0) {
		x--;
	}
	if (ch == 'w') {
		angle += 1;
	}
	if (ch == 's') {
		angle -= 1;
	}
	if (angle == 4) {
		angle = 0;
	}
	else if (angle == -1) {
		angle = 4;
	}
	
	
}


//メイン関数
int main() {
	newmino();
	while (!(gameover)) {
		if (isground) {
			
			save();
			newmino();
			isground = false;
		}

		rotate();
		save();
		output();
		reset(1);
		key();
		if (!(isground)) {
			y++;
			addscore();
		}
		printf("%d", y);
		Sleep(500);
	}
	printf("game over");
	return 0;
}