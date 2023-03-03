#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ROW 3
#define COL 3
#define ROWS ROW+1
#define COLS COL+1
#define MINE_COUNT 5

int welcome() {
    printf("****************************************\n");
    printf("**********     1、开始游戏     *********\n");
    printf("**********     2、退出游戏     *********\n");
    printf("****************************************\n");
    printf("请输入你的选择：");
    int input;
    scanf("%d", &input);
    return input;
}

void init_show(char matrix[][COLS],int row,int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = ' ';
        }
    }
    return;
}

void display(char matrix[][COLS],int row,int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i == 0) {
                printf(" %d |", j);
                continue;
            }
            if (j == 0) {
                printf(" %d |", i);
            } else {
                printf(" %c |", matrix[i][j]);
            }
        }
        printf("\n---|---|---|---|\n");
    }
    return;
}

void set_mine(int *x,int *y) {
    printf("请输入要排雷的位置<x,y>：");
    scanf("%d,%d", x, y);
}

void init_mine(char matrix[][COLS],int row,int col,int x,int y,int count) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = 0;
        }
    }
    while (count > 0) {
        int mx = (rand() % ROW) + 1;
        int my = (rand() % COL) + 1;
        if (mx == x && my == y) {
            continue;
        }
        if (matrix[mx][my] == 1) {
            continue;
        }
        matrix[mx][my] = 1;
        --count;
    }
}

int judge_fail(char matrix[][COLS],int x,int y) {
    if (matrix[x][y] == 1) {
        return 1;
    }
    return 0;
}

int judge_win(char matrix[][COLS],int row,int col) {
    int count = 0;
    for (int i = 1; i < row; ++i) {
        for (int j = 1; j < col; ++j) {
            if (matrix[i][j] == ' ') {
                ++count;
            }
        }
    }
    if ((count - 1) == MINE_COUNT) {
        return 1;
    }
    return 0;
}

int count_mine(char matrix[][COLS],int row,int col,int x,int y) {
    int count = 0;
    if (x - 1 >= 1 && y - 1 >= 1) {
        count += matrix[x - 1][y - 1];
    }
    if (x > 1 >= 1) {
        count += matrix[x - 1][y];
    }
    if (x - 1 >= 1 && y + 1 < col) {
        count += matrix[x - 1][y + 1];
    }
    if (y - 1 >= 1) {
        count += matrix[x][y - 1];
    }
    if (y + 1 < col) {
        count += matrix[x][y + 1];
    }
    if (x + 1 < row && y - 1 >= 1) {
        count += matrix[x + 1][y - 1];
    }
    if (x + 1 < row) {
        count += matrix[x + 1][y];
    }
    if (x + 1 < row && y + 1 < col) {
        count += matrix[x + 1][y + 1];
    }
    return count;
}

void set_show(char matrix[][COLS],int x,int y,int count) {
    matrix[x][y] = count + '0';
}

void game() {
    char mine[ROWS][COLS];
    char show[ROWS][COLS];
    init_show(show, ROWS, COLS);
    int flag = 0;
    while (1) {
        system("cls");
        display(show, ROWS, COLS);
        int x, y;
        set_mine(&x, &y);
        if (flag == 0) {
            init_mine(mine, ROWS, COLS, x, y, MINE_COUNT);
            flag = 1;
        }
        if (judge_fail(mine, x, y)) {
            printf("踩雷了~\n");
            return;
        }
        if (judge_win(show, ROWS, COLS)) {
            printf("成功！\n");
            return;
        }
        set_show(show, x, y, count_mine(mine, ROWS, COLS, x, y));
    }
}

int main() {
    srand(time(NULL));
    while (1) {
        switch (welcome()) {
            case 1:
                game();
                break;
            case 2:
                return 0;
            default:
                printf("请输入正确选项：");
                break;
        }

    }
}