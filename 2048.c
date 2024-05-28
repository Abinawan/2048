#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int i, j, k, arrowInput, won = 1, hasMoved, board[4][4], tempBoard[4][4];
char scoreText[100], tileText[100];
int score = 0, highscore = 0;
int moveUp();
int moveDown();
int moveLeft();
int moveRight();
void createBoard();
void generate();
int boardMovement();
void gameOver();
int canMove();
void checkWin();
int main() {
	int gmode = DETECT, gdrive;
	srand(time(NULL));	
	initgraph( & gmode, & gdrive, "C:\\TURBOC3\\BGI");
	FILE * fp = fopen("highscore.txt", "r");
	if (fp != NULL) {
		fscanf(fp, "%d", & highscore);
		fclose(fp);
	} 
	generate(); // generate 2 random number,
	generate();	// to keep in the board;
	createBoard(); // create the board;
	while(1) {
		int moved = 0;
		if (canMove() == 0) {
			gameOver();
			if (score >= highscore) {
				FILE * fp = fopen("highscore.txt", "w");
				fprintf(fp, "%d", score);
				fclose(fp);
			}
			do{
				arrowInput = getch();
				if(arrowInput == 27) exit(0);
			} while(arrowInput != 27);		
		}
		if(won) checkWin();
		arrowInput = getch();
		switch (arrowInput) {
			case 119:
			case 72: //up
				moved = moveUp();
				break;
			case 115: 
			case 80://down
				moved = moveDown();
				break;
			case 97:
			case 75: //left
				moved = moveLeft();
				break;
			case 100:
			case 77: //right
				moved = moveRight();
				break;
			default:
				moved = 0;
				break;
		}
		if (moved == 1) {
			createBoard();
			delay(100);
			generate();
			createBoard();
		}
	} 
	getch();
	closegraph();
	return 0;
}
void checkWin(){
	for(i=0; i<4; i++){
		for(j=0;j<4; j++){
			if(board[i][j] == 2048){
				settextstyle(3, 0, 5);
				setcolor(WHITE);
				setfillstyle(SOLID_FILL, BLACK);
				bar(200, 250, 440, 320);
				outtextxy(230, 250, "YOU WON");
				setcolor(DARKGRAY);
				settextstyle(2, 0, 5);
				outtextxy(225, 295, "Press any key to continue...");
				won--;
			}
		}
	}
}
void gameOver() {
    delay(1000);
	settextstyle(3, 0, 5);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, BLACK);
	bar(200, 250, 440, 320);
	outtextxy(210, 250, "GAME OVER");
	setcolor(DARKGRAY);
	settextstyle(3, 0, 1);
	outtextxy(250, 295, "Press ESC to exit.");

}
void rotateBoard() {
	for (i = 0; i < 2; i++) {
		for (j = i; j < 3 - i; j++) {
			int temp = board[i][j];
			board[i][j] = board[3 - j][i];
			board[3 - j][i] = board[3 - i][3 - j];
			board[3 - i][3 - j] = board[j][3 - i];
			board[j][3 - i] = temp;
		}
	}
}
int canMove() {
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				return 1;
			}
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == board[i + 1][j] && i  <  3) {
				return 1;
			}
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == board[i][j + 1] && j  <  3) {
				return 1;
			}
		}
	}
	return 0;
}
int moveUp() {
	hasMoved = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}
	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			if (board[i][j] != 0) {
				if ((board[i][j] == board[i + 1][j]) && i  <  3) {
					board[i][j] += board[i + 1][j];
					score += board[i][j];
					board[i + 1][j] = 0;
				} else if ((board[i][j] == board[i + 2][j]) && i  <  2 && board[i + 1][j] == 0) {
					board[i][j] += board[i + 2][j];
					score += board[i][j];
					board[i + 2][j] = 0;
				} else if ((board[i][j] == board[i + 3][j]) && (i  <  1) && (board[i + 2][j] == 0)) {
					board[i][j] += board[i + 3][j];
					score += board[i][j];
					board[i + 3][j] = 0;
				}
			}
		}
	}
	for (j = 0; j < 4; j++) {
		k = 0;
		for (i = 0; i < 4; i++) {
			if (board[i][j] != 0) {
				if (i != k) {
					board[k][j] = board[i][j];
					board[i][j] = 0;
				}
				k++;
			}
		}
	}
	hasMoved = boardMovement();
	return hasMoved;
}
int boardMovement() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] != tempBoard[i][j]) {
				return 1;
			}
		}
	}
	return 0;
}
int moveDown() {
	rotateBoard();
	rotateBoard();
	hasMoved = moveUp();
	rotateBoard();
	rotateBoard();
	return hasMoved;
}
int moveLeft() {
	rotateBoard();
	hasMoved = moveUp();
	rotateBoard();
	rotateBoard();
	rotateBoard();
	return hasMoved;
}
int moveRight() {
	rotateBoard();
	rotateBoard();
	rotateBoard();
	hasMoved = moveUp();
	rotateBoard();
	return hasMoved;
}
void createBoard() {
	cleardevice();
	char numberText[10], scoreUpdate[15], highscoreText[15];
	int count, num;
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, 0, getmaxx(), getmaxy());
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(170, 140, 250 + 3 * 70, 220 + 3 * 70);
	settextstyle(3, 0, 6);
	setcolor(WHITE);
	outtextxy(181, 50, "2048");
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	if (score > highscore) {
		highscore = score;
	}
	num = highscore;
	count = 1;
	while (num != 0) {
		num /= 10;
		++count;
	}
	bar(340, 70, 400 + count * 10, 110);
	setcolor(BLACK);
	sprintf(scoreUpdate, "SCORE: %d", score);
	sprintf(highscoreText, "HIGHS: %d", highscore);
	settextstyle(0, 0, 1);
	outtextxy(350, 80, scoreUpdate);
	outtextxy(350, 95, highscoreText);
	setcolor(BLACK);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			num = board[i][j];
			count = 0;
			while (num != 0) {
				num /= 10;
				++count;
			}
			if (board[i][j] != 0) {
				if (count == 4) {
					setfillstyle(SOLID_FILL, YELLOW);
				} else if (count == 3) {
					setfillstyle(SOLID_FILL, BROWN);
				} else if (count == 2) {
					setfillstyle(SOLID_FILL, LIGHTBLUE);
				} else if (count == 1) {
					setfillstyle(SOLID_FILL, CYAN);
				} else {
					setfillstyle(SOLID_FILL, MAGENTA);
				}
			} else setfillstyle(SOLID_FILL, DARKGRAY);
			bar(180 + j * 70, 150 + i * 70, 240 + j * 70, 210 + i * 70);
			sprintf(numberText, "%d", board[i][j]);
			if (board[i][j] == 0) outtextxy(200 + j * 70, 155 + i * 70, " ");
			else {
				if (count == 4) {
					settextstyle(1, 0, 3);
					outtextxy(181 + j * 70, 160 + i * 70, numberText);
				} else if (count == 3) {
					settextstyle(1, 0, 4);
					outtextxy(181 + j * 70, 160 + i * 70, numberText);
				} else if (count == 2) {
					settextstyle(1, 0, 5);
					outtextxy(187 + j * 70, 155 + i * 70, numberText);
				} else if (count == 1) {
					settextstyle(1, 0, 5);
					outtextxy(200 + j * 70, 155 + i * 70, numberText);
				} else {
					settextstyle(1, 0, 1);
					outtextxy(180 + j * 70, 164 + i * 70, numberText);
				}
			}
		}
	}
	settextstyle(2, 0, 4);
	setcolor(WHITE);
	outtextxy(170, 438, "HOW TO PLAY: Move and merge tiles with same number");
	outtextxy(170, 450, "using arrow keys and add them to reach 2048! GLHF!!");
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(170, 461, 460, 475);
	outtextxy(170, 462, "PROJECT BY: Abinawan Bhattarai & Binisha Maharjan.");
}
void generate() {
	int addedNumber = 0;
	do {
		i = rand() % 4;
		j = rand() % 4;
		int l = rand() % 10;
		if (board[i][j] == 0) {
			if (l < 9) {
				board[i][j] = 2;
			} else board[i][j] = 4;
			addedNumber++;
		}
	} while (!addedNumber);
}
