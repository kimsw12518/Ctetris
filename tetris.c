#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include <conio.h>



#define lineerase() bonus=0;for(i=0;i<22;i++){det=1;for(j=0;j<10;j++){if(map[i][j]==0){det=0;break;}}if(det==1){score=score+100+bonus;bonus+=50;for(k=i;0<k;k--){for(j=0;j<10;j++){map[k][j]=map[k-1][j];}}}}for(i=0;i<10;i++){map[0][i]=0;}temp=1;for(j=0;j<10;j++){if(map[21][j]==0){temp=0;}}if(temp==1){score+=1000;}


//JSIZTOL
const short int minodat[7][4][4] = {
{//J
{0,0,0,0},
{1,10,2,0},
{5,15,5,0},
{8,10,4,0}
},
{//S
{0,0,0,0},
{8,3,1,0},
{9,15,6,0},
{4,12,2,0}
},
{//I
{0,8,2,0},
{1,9,3,1},
{4,12,6,4},
{0,8,2,0}
},
{//Z 
{0,0,0,0},
{1,9,2,0},
{12,15,3,0},
{8,6,4,0}
},
{//T
{0,0,0,0},
{0,11,0,0},
{13,15,7,0},
{0,14,0,0}
},
{//O
{0,0,0,0},
{0,15,15,0},
{0,15,15,0},
{0,0,0,0}
},
{//L
{0,0,0,0},
{8,10,1,0},
{5,15,5,0},
{4,10,2,0}
}
};

const short int srs[2][4][5][2] = {
{//i제외 
{{0,0},	{0,0},	{0,0},	{0,0},	{0,0}},
{{0,0},	{1,0},	{1,1},	{0,-2},	{1,-2}},
{{0,0},	{0,0},	{0,0},	{0,0},	{0,0}},
{{0,0},	{-1,0},	{-1,1},	{0,-2},	{-1,-2}}
},
{//i
{{0,0},{-1,0},{2,0},{-1,0},{2,0}},
{{0,0},{1,0},{1,0},{1,-1},{1,2}},
{{0,0},{2,0},{-1,0},{2,1},{-1,1}},
{{0,0},{0,0},{0,0},{0,2},{0,-1}}
}
};

void CursorView();
void gotoxy(int x, int y);
void color(int colorNum, int bg);
void base(int bag[14], int score, int hold);
void display(int map[22][10], int x, int y, int type, int rot, int bag[14], int score, int hold);
void setmino(int x, int y, int type, int rot);
int move(int map[22][10], int act, int x, int y, int type, int rot);
int spin(int map[22][10], int act, int x, int y, int type, int rot);

int main()
{
	system("mode con cols=48 lines=26");
	color(0, 0);
	system("cls");
	CursorView();
	srand(time(NULL));
	int x = 3, y = -2, r = 0, mino = 1, a = 0, t = 0, b, k, l, c = 0, fc = 0, reset, p, q, det, i, j, score = 0, hold = -1, temp, holdc = 0,sp,spc=0,speed=0,bonus=0;
	int bag[14] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	for (reset = 0; reset < 7; reset++) {
		p = rand() % 7;
		if (bag[p] == -1) {
			bag[p] = reset;
		}
		else {
			reset--;
		}
	}
	mino = bag[0];
	if(mino==2)y++;
	int map[22][10] = { {0,}, };
	while (1) {
		Sleep(20);
		q = 1;
		for (reset = 7; reset < 14; reset++) {
			if (bag[reset] != -1) {
				q = 0;
				break;
			}
		}
		if (q == 1) {
			for (reset = 0; reset < 7; reset++) {
				p = rand() % 7;
				if (bag[p + 7] == -1) {
					bag[p + 7] = reset;
				}
				else {
					reset--;
				}
			}
		}
//		if (kbhit()) {
//			a = getch();
			if (GetAsyncKeyState(0x41) & 0x8001) {
				x = x + move(map, 1, x, y, mino, r);
			}
			if (GetAsyncKeyState(0x44) & 0x8001) {
				x = x + move(map, 2, x, y, mino, r);
			}
			if (GetAsyncKeyState(0x53) & 0x8001) {
				b = move(map, 3, x, y, mino, r);
				y = y + b;
				score = score + b;
				if (b == 0) {
					if (c == 1 && fc >= 7) {
						for (k = 0; k < 4; k++) {
							for (l = 0; l < 4; l++) {
								if ((minodat[mino][k][l] / (1 << r)) % 2 == 1) {
									map[y + k + 2][x + l] = mino + 1;
								}
							}
						}
						fc = 0;
						x = 3;
						y = -2;
						r = 0;
						for (reset = 0; reset < 13; reset++) {
							bag[reset] = bag[reset + 1];
						}
						bag[13] = -1;
						mino = bag[0];
						if(mino==2)y++;
						holdc = 0;
						if(map[2][3]!=0||map[2][4]!=0||map[2][5]!=0||map[2][6]!=0){
							return 0;
						}
						c=0;
					}
					else {
						c = 1;
					}
				}
				else {
					c = 0;
					fc = 0;
				}
			}
			if (GetAsyncKeyState(0x57) & 0x0001) {
				do {
					b = move(map, 3, x, y, mino, r);
					y = y + b;
					score = score + b + b;
				} while (b != 0);
				fc = 0;
				for (k = 0; k < 4; k++) {
					for (l = 0; l < 4; l++) {
						if ((minodat[mino][k][l] / (1 << r)) % 2 == 1) {
							map[y + k + 2][x + l] = mino + 1;
						}
					}
				}
				lineerase();
				x = 3;
				y = -2;
				r = 0;
				for (reset = 0; reset < 13; reset++) {
					bag[reset] = bag[reset + 1];
				}
				bag[13] = -1;
				mino = bag[0];
				if(mino==2)y++;
				holdc = 0;
				if(map[2][3]!=0||map[2][4]!=0||map[2][5]!=0||map[2][6]!=0){
					return 0;
				}
				c=0;
			}
			if (GetAsyncKeyState(0x20) & 0x0001) {
				if (holdc == 0) {
					fc = 0;
					if (hold == -1) {
						hold = mino;
						for (reset = 0; reset < 13; reset++) {
							bag[reset] = bag[reset + 1];
						}
						bag[13] = -1;
						mino = bag[0];
						x = 3;
						y = -2;
						r = 0;
						if(mino==2)y++;
					}
					else {
						temp = mino;
						mino = hold;
						hold = temp;
						x = 3;
						y = -2;
						r = 0;
						if(mino==2)y++;
					}
					holdc = 1;
				}
			}
		//	if (a == 224) {
		//		a = getch();
				if (mino == 2)sp = 1;
				else sp = 0;
				if (GetAsyncKeyState(0x25) & 0x0001) {
					temp = spin(map, 2, x, y, mino, r);
					if (temp != -1) {
						x += srs[sp][r][temp][0] - srs[sp][(r + 4 - 1) % 4][temp][0];
						y += srs[sp][r][temp][1] - srs[sp][(r + 4 - 1) % 4][temp][1];
						r = (r + 4 - 1) % 4;
					}
				}
				if (GetAsyncKeyState(0x27) & 0x0001) {
					temp = spin(map, 1, x, y, mino, r);
					if (temp != -1) {
						x += srs[sp][r][temp][0] - srs[sp][(r + 4 + 1) % 4][temp][0];
						y += srs[sp][r][temp][1] - srs[sp][(r + 4 + 1) % 4][temp][1];
						r = (r + 4 + 1) % 4;
					}
				
			
		}
		if (clock() - t > 50) {
			speed=score/5000;
			if(speed>17){
				speed=17;
			}
			t = clock();
			display(map, x, y, mino, r, bag, score, hold);
			fc++;
			spc++;
			if (fc == 18) {
				fc = 0;
				b = move(map, 3, x, y, mino, r);
				y = y + b;
				if (b == 0) {
					if (c == 1&&spc>14) {
						for (k = 0; k < 4; k++) {
							for (l = 0; l < 4; l++) {
								if ((minodat[mino][k][l] / (1 << r)) % 2 == 1) {
									map[y + k + 2][x + l] = mino + 1;
								}
							}
						}
						lineerase();
						x = 3;
						y = -2;
						r = 0;
						for (reset = 0; reset < 13; reset++) {
							bag[reset] = bag[reset + 1];
						}
						bag[13] = -1;
						mino = bag[0];
						if(mino==2)y++;
						holdc = 0;
						if(map[2][3]!=0||map[2][4]!=0||map[2][5]!=0||map[2][6]!=0){
							return 0;
						}
						c=0;
						spc=0;
					}
					else {
						c = 1;
					}
				}
				else {
					c = 0;
				}
			}
		}
	}
}
//next=12,2

void base(int bag[14], int score, int hold)
{
	gotoxy(-4, 2);
	int i = 0;
	color(7, 8);
	printf("■■■■■■■■■■■■■■■■■■■■■■");
	for (i = 0; i < 4; i++) {
		gotoxy(-4, 3 + i);
		color(7, 8);
		printf("■");
		color(8, 8);
		printf("■■■■");
		gotoxy(1, 3 + i);
		color(7, 8);
		printf("■");
		gotoxy(12, 3 + i);
		color(7, 8);
		printf("■");
		color(8, 8);
		printf("■■■■");
		color(7, 8);
		printf("■");
	}
	setmino(11, 0, bag[1], 0);
	setmino(-5, 0, hold, 0);
	gotoxy(-4, 7);
	color(7, 8);
	printf("■■■■■■");
	gotoxy(1, 7);
	color(7, 8);
	printf("■");
	gotoxy(12, 7);
	color(7, 8);
	printf("■■■■■■");
	for (i = 0; i < 4; i++) {
		gotoxy(1, 8 + (i * 3));
		color(7, 8);
		printf("■");
		gotoxy(12, 8 + (i * 3));
		color(7, 8);
		printf("■");
		color(bag[i + 2] + 9, bag[i + 2] + 9);
		printf("■■");
		color(7, 8);
		printf("■");
		gotoxy(1, 9 + (i * 3));
		color(7, 8);
		printf("■");
		gotoxy(12, 9 + (i * 3));
		color(7, 8);
		printf("■");
		color(bag[i + 2] + 9, bag[i + 2] + 9);
		printf("■■");
		color(7, 8);
		printf("■");
		gotoxy(1, 10 + (i * 3));
		color(7, 8);
		printf("■");
		gotoxy(12, 10 + (i * 3));
		color(7, 8);
		printf("■■■■");
	}
	for (i = 0; i < 3; i++) {
		gotoxy(1, 20 + i);
		color(7, 8);
		printf("■");
		gotoxy(12, 20 + i);
		color(7, 8);
		printf("■");
	}
	gotoxy(1, 23);
	printf("■■■■■■■■■■■■\n\n");
	gotoxy(13, 21);
	color(7, 0);
	printf("SCORE");
	gotoxy(13, 22);
	printf("%d", score);
}

void gotoxy(int x, int y)
{

	COORD pos = { 2 * x + 10,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void color(int colorNum, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum | (bg << 4));
	/*
	0	Black		1	Dark Blue
	2   Dark Green	3   Dark Sky Blue
	4   Dark Red	5   Dark Purple
	6   Dark Yellow	7   Gray
	8   Dark Gray	9   Blue
	10  Green		11  Sky Blue
	12  Red			13  Purple
	14  Yellow		15  White
	*/
}

void setmino(int x, int y, int type, int rot)
{
	x = x + 2;
	y = y + 3;
	gotoxy(x, y);
	int k, l;
	for (k = 0; k < 4; k++) {
		for (l = 0; l < 4; l++) {
			if ((minodat[type][k][l] / (1 << rot)) % 2 == 1) {
				gotoxy(x + l, y + k);
				color(type + 9, type + 1);
				printf("■");
			}
		}
	}
}

void display(int map[22][10], int x, int y, int type, int rot, int bag[14], int score, int hold)
{
	int i, j;
	int a;
	base(bag, score, hold);
	gotoxy(2, 3);
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			color(map[i + 2][j] + 8, map[i + 2][j]);
			printf("□");
		}
		if (i == y + 3) {
			setmino(x, y, type, rot);
		}
		gotoxy(2, 4 + i);
	}
	if (i <= y + 3) {
		setmino(x, y, type, rot);
	}
	gotoxy(2, 1);
	color(0, 0);
	printf("■■■■■■■■■■■■");
	gotoxy(2, 2);
	color(7, 8);
	printf("■■■■■■■■■■■■");
	gotoxy(0, 25);
}

int move(int map[22][10], int act, int x, int y, int type, int rot)
{
	int i, k, l, rt;
	for (k = 0; k < 4; k++) {
		for (l = 0; l < 4; l++) {
			if ((minodat[type][k][l] / (1 << rot)) % 2 == 1) {
				if (act == 1) {
					if (x + l == 0) {
						return 0;
					}
					if (map[y + k + 2][x + l - 1] != 0) {
						return 0;
					}
				}
				if (act == 2) {
					if (x + l == 9) {
						return 0;
					}
					if (map[y + k + 2][x + l + 1] != 0) {
						return 0;
					}
				}
				if (act == 3) {
					if (y + k == 19) {
						return 0;
					}
					if (map[y + k + 1 + 2][x + l] != 0) {
						return 0;
					}
				}
			}
		}
	}
	switch (act) {
	case 1:
		return -1;
	case 2:
		return 1;
	case 3:
		return 1;
	}
}

int spin(int map[22][10], int act, int x, int y, int type, int rot)
{
	int i, k, l, rt, ox, oy, ll = 0;
	int tar;
	int a[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	if (act == 1)tar = (rot + 1) % 4;
	if (act == 2)tar = (rot + 3) % 4;
	if (type == 2)ll = 1;
	if (act == 1 || act == 2) {
		for (i = 0; i < 5; i++) {

			ox = srs[ll][rot][i][0] - srs[ll][tar][i][0];
			oy = srs[ll][rot][i][1] - srs[ll][tar][i][1];
			rt = 1;
			for (k = 0; k < 4; k++) {
				for (l = 0; l < 4; l++) {
					if ((minodat[type][k][l] / (1 << tar)) % 2 == 1) {
						if (x + l + ox > 9 || x + l + ox < 0 || (map[y + k + 2 + oy][x + l + ox] != 0) || y + k + oy>19) { //문제가 많음 
							rt = 0;
							break;
						}
					}
				}
			}
//			display(map, (x + ox), (y + oy), type, tar, a, 0, 0);
			if (rt == 1) {
				return i;
			}
		}
		return -1;
	}
	return -1;
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
