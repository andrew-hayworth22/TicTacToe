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
    clear();
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
//         - board      -> board to check
//         - spotNum    -> spot number to fill
//         - isP1       -> is it player 1's turn?
//     Return: 1 if turn is taken and 0 if not
////////////////////////////////////////////////////////////
int takeTurn(struct Board* board, int spotNum, int isP1) {
    // Determine the row and column of the selection
    int row;
    int col;
    switch(spotNum) {
        case 1 : 
            row = 0;
            col = 0;
            break;
        case 2 : 
            row = 0;
            col = 1;
            break;
        case 3 : 
            row = 0;
            col = 2;
            break;
        case 4 : 
            row = 1;
            col = 0;
            break;
        case 5 : 
            row = 1;
            col = 1;
            break;
        case 6 : 
            row = 1;
            col = 2;
            break;
        case 7 : 
            row = 2;
            col = 0;
            break;
        case 8 : 
            row = 2;
            col = 1;
            break;
        case 9 : 
            row = 2;
            col = 2;
            break;
    }

    // Check if that spot is not taken
    if(board->spaces[row][col] != board->player1Char && board->spaces[row][col] != board->player2Char) {
        // If not, fill spot with correct player character
        board->spaces[row][col] = (isP1 == 1) ? board->player1Char : board->player2Char;
        return 1;
    }

    return 0;
}

////////////////////////////////////////////////////////////
// checkVictory() -> checks if the player has won or tie
//     Input:
//         - board  -> board to check
//         - isP1   -> is it player 1's turn?
//     Return: 1 if player won, 0 if not, and -1 if tie
////////////////////////////////////////////////////////////
int checkVictory(struct Board* board, int isP1) {
    char playerChar = (isP1) ? board->player1Char : board->player2Char;

    // Check win conditions
    // Horizontal lines
    if((board->spaces[0][0] == playerChar) && (board->spaces[0][1] == playerChar) && (board->spaces[0][2] == playerChar))
        return 1;
    if((board->spaces[1][0] == playerChar) && (board->spaces[1][1] == playerChar) && (board->spaces[1][2] == playerChar))
        return 1;
    if((board->spaces[2][0] == playerChar) && (board->spaces[2][1] == playerChar) && (board->spaces[2][2] == playerChar))
        return 1;
    // Vertical lines
    if((board->spaces[0][0] == playerChar) && (board->spaces[1][0] == playerChar) && (board->spaces[2][0] == playerChar))
        return 1;
    if((board->spaces[0][1] == playerChar) && (board->spaces[1][1] == playerChar) && (board->spaces[2][1] == playerChar))
        return 1;
    if((board->spaces[0][2] == playerChar) && (board->spaces[1][2] == playerChar) && (board->spaces[2][2] == playerChar))
        return 1;
    // Diagonal lines
    if((board->spaces[0][0] == playerChar) && (board->spaces[1][1] == playerChar) && (board->spaces[2][2] == playerChar))
        return 1;
    if((board->spaces[0][2] == playerChar) && (board->spaces[1][1] == playerChar) && (board->spaces[2][0] == playerChar))
        return 1;
    
    // Check if any spaces left
    for(int i = 0; i < 3; ++i) {
        for(int k = 0; k < 3; ++k) {
            if(board->spaces[i][k] - '0' > 0 && board->spaces[i][k] - '0' < 10)
                return 0;
        }
    }

    // If not, we have a tie
    return -1;
}