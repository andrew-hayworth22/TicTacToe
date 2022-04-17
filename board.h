////////////////////////////////////////////////////////////
// Michael Hayworth
// 3/12/2022
////////////////////////////////////////////////////////////
// board.h
// Design of the board structure and its associated methods
////////////////////////////////////////////////////////////

#ifndef BOARD_H
#define BOARD_H

struct Board {
    int boxSize;
    char player1Char;
    char player2Char;
    char spaces[3][3];
};

void initBoard(struct Board*, char, char);
void drawBoard(struct Board*);
int takeTurn(struct Board*, int, int);
int checkVictory(struct Board*, int);

#endif