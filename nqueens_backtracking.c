#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int BSize, int col);
int isSafe(int** board, int BSize, int row, int col);
void printSolution(int** board, int BSize);
void printBoard(int** board, int BSize);

int main() {
    int **board;
    int BSize;

    printf("Enter the size of chessBoard (N x N):\n");
    scanf("%d", &BSize);

    board = (int **)malloc(BSize * sizeof(int *));
    for (int i = 0; i < BSize; i++)
        board[i] = (int *)malloc(BSize * sizeof(int));

    for (int i = 0; i < BSize; i++)
        for (int j = 0; j < BSize; j++)
            board[i][j] = 0;

    nQueens(board, BSize, 0);

    for (int i = 0; i < BSize; i++)
        free(board[i]);
    free(board);

    return 0;
}

int nQueens(int** board, int BSize, int col) {
    if (col == BSize) {
        printSolution(board, BSize);
        return 1;
    }

    int solutions = 0;
    for (int i = 0; i < BSize; i++) {
        if (isSafe(board, BSize, i, col)) {
            board[i][col] = 1;
            solutions += nQueens(board, BSize, col + 1);
            board[i][col] = 0;
        }
    }

    return solutions;
}

int isSafe(int** board, int BSize, int row, int col) {
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    for (i = row, j = col; i < BSize && j >= 0; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int** board, int BSize) {
    printf("\nSolution:\n");
    printBoard(board, BSize);
}

void printBoard(int** board, int BSize) {
    const char COLOR_BGW[] = "\x1b[47m";
    const char COLOR_BGB[] = "\x1b[100m";
    const char COLOR_BLK[] = "\x1b[30m";
    const char COLOR_RESET[] = "\x1b[0m";

    for (int i = 0; i < BSize; i++) {
        for (int j = 0; j < BSize; j++) {
            if ((i + j) % 2 == 0)
                printf("%s", COLOR_BGW);
            else
                printf("%s", COLOR_BGB);

            if (board[i][j] == 1)
                printf("%s Q %s", COLOR_BLK, COLOR_RESET);
            else
                printf("   ");
        }
        printf("\n");
    }
    printf("\n");
}
