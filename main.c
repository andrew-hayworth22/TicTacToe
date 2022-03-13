///////////////////////////////////////////////////////////////////////
// Michael Hayworth
// 3/12/2022
///////////////////////////////////////////////////////////////////////
// main.c
// Handles the main logic flow of the TicTacToe game
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "board.h"

///////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////
#define PLAYER_1_CHAR   'X'
#define PLAYER_2_CHAR   'O'
#define QUIT_CHAR       'q'

///////////////////////////////////////////////////////////////////////
// Declarations
///////////////////////////////////////////////////////////////////////
void setUp();
void drawPrompt();
void makeMove(char);
void refreshScreen();
void victory();
void quit();

// Game variables
struct Board board;
int isP1Turn = 1;
char* prompt = "Player 1's Turn: ";

///////////////////////////////////////////////////////////////////////
// main() -> main logic flow of the game
///////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

    setUp();
    drawBoard(&board);

    int c;
    while((c = getchar()) != QUIT_CHAR) {
        makeMove(c);
        refreshScreen();
    }

    quit();
}

///////////////////////////////////////////////////////////////////////
// setUp() -> initialize the game
///////////////////////////////////////////////////////////////////////
void setUp() {
    // Initialize and clear curses screen
    initscr();
    clear();

    // Initialize the board
    initBoard(&board, PLAYER_1_CHAR, PLAYER_2_CHAR);

    // Set up alarm system
    signal(SIGABRT, quit);
}

///////////////////////////////////////////////////////////////////////
// makeMove() -> player attempts a move
///////////////////////////////////////////////////////////////////////
void makeMove(char in) {
    switch (in) {
            case '1':
                if(!takeTurn(&board, 0, 0, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '2':
                if(!takeTurn(&board, 0, 1, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '3':
                if(!takeTurn(&board, 0, 2, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '4':
                if(!takeTurn(&board, 1, 0, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '5':
                if(!takeTurn(&board, 1, 1, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '6':
                if(!takeTurn(&board, 1, 2, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '7':
                if(!takeTurn(&board, 2, 0, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '8':
                if(!takeTurn(&board, 2, 1, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            case '9':
                if(!takeTurn(&board, 2, 2, isP1Turn)) {
                    prompt = "Spot is taken: ";
                }
                else {
                    victory(board);
                }
                break;
            default:
                prompt = "Incorrect input: ";
                break;
        }
}

///////////////////////////////////////////////////////////////////////
// refreshScreen() -> refresh screen
///////////////////////////////////////////////////////////////////////
void refreshScreen() {

}

///////////////////////////////////////////////////////////////////////
// quit() -> gracefully quit the game
///////////////////////////////////////////////////////////////////////
void quit() {
    endwin();
    exit(0);
}