////////////////////////////////////////////////////////////
// Michael Hayworth
// 3/12/2022
////////////////////////////////////////////////////////////
// board.c
// Implementation of the board methods
////////////////////////////////////////////////////////////

#include "board.h"
#include <stdio.h>
#include <curses.h>

////////////////////////////////////////////////////////////
// initBoard() -> initialize the board to have correct values
//     Inputs:
//         - board       -> board to initialize
//         - player1Char -> character to represent player 1
//         - player2Char -> character to represent player 2
////////////////////////////////////////////////////////////
void initBoard(struct Board* board, char player1Char, char player2Char) {
    // Initialize functions
    board->player1Char = player1Char;
    board->player2Char = player2Char;

    // Number all of the board spots for input later
    char count = '0';
    for(int i = 0; i < 3; ++i) {
        for(int k = 0; k < 3; ++k) {
            board->spaces[i][k] = ++count;
        }
    }
}

////////////////////////////////////////////////////////////
// initBoard() -> print board and its values
//     Input: board -> board to print
////////////////////////////////////////////////////////////
void drawBoard(struct Board* board) {
    // Draw first horizontal line
    int row = 5;
    int col = 10;
    while(col < 27) {
        move(row, col);
        addch('#');
        ++col;
    }

    // Draw second horizontal line
    row = 9;
    col = 10;
    while(col < 27) {
        move(row, col);
        addch('#');
        ++col;
    }

    // Draw first vertical line
    row = 2;
    col = 15;
    while(row < 13) {
        move(row, col);
        addch('#');
        ++row;
    }

    // Draw second vertical line
    row = 2;
    col = 21;
    while(row < 13) {
        move(row, col);
        addch('#');
        ++row;
    }

    // Draw the values of each of the 
    row = 3;
    col = 12;
    for(int i = 0; i < 3; ++i) {
        for(int k = 0; k < 3; ++k) {
            move(row, col);
            addch(board->spaces[i][k]);
            col += 6;
        }
        row += 4;
        col = 12;
    }

    refresh();
}

////////////////////////////////////////////////////////////
// takeTurn() -> takes a turn
//     Input:
//         - board -> board to check
//         - row   -> row of selection
//         - col   -> column of selection
//         - isP1  -> is it player 1?
//     Return: 1 if turn is taken and 0 if not
////////////////////////////////////////////////////////////
int takeTurn(struct Board* board, int row, int col, int isP1) {
    if(board->spaces[row][col] != board->player1Char && board->spaces[row][col] != board->player2Char)
        return 1;
    return 0;
}