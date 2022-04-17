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
void drawPrompt();
void refreshScreen();
void gameOver();
void quit();

// Game variables
struct Board board;
int isP1Turn = 1;
char* prompt = "Player 1's Turn: ";
int isOver = 0;

///////////////////////////////////////////////////////////////////////
// main() -> main logic flow of the game
///////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    // Set up game
    setUp();
    // Draw initial screen
    refreshScreen();

    // Get input, make a move on that input, and refresh screen
    int c;
    while((c = getchar()) != QUIT_CHAR) {
        makeMove(c);
        refreshScreen();

        if(isOver)
            gameOver();
    }

    // Gracefully quit if exit character is given
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
    // Get number of input
    int inNum = in - '0';

    // Ensure that the input is a valid spot
    if(inNum < 10 && inNum > 0) {
        // Attempt to take a turn
        if(takeTurn(&board, inNum, isP1Turn) == 1) {
            // Check victory
            int res = checkVictory(&board, isP1Turn);
            if(res == 1) {
                isOver = 1;
                prompt = (isP1Turn) ? "Player 1 wins!" : "Player 2 wins!";
            }
            else if(res == -1) {
                isOver = 1;
                prompt = "Tie game!";
            }
                

            // Switch turns and change prompts
            if(isOver != 1) {
                isP1Turn = !isP1Turn;
                if(isP1Turn)
                    prompt = "Player 1's turn: ";
                else
                    prompt = "Player 2's turn: ";
            }
            
        }
    }
}

///////////////////////////////////////////////////////////////////////
// drawPrompt() -> draws game prompt at correct position
///////////////////////////////////////////////////////////////////////
void drawPrompt() {
    // Move to the corrects position, add the prompt string, and refresh
    move(15, 5);
    addstr(prompt);
    refresh();
}

///////////////////////////////////////////////////////////////////////
// refreshScreen() -> refresh screen
///////////////////////////////////////////////////////////////////////
void refreshScreen() {
    // Draw the board and the prompt
    drawBoard(&board);
    drawPrompt();
}

///////////////////////////////////////////////////////////////////////
// gameOver() -> game over screen
///////////////////////////////////////////////////////////////////////
void gameOver() {
    clear();
    drawPrompt();
    refresh();
}

///////////////////////////////////////////////////////////////////////
// quit() -> gracefully quit the game
///////////////////////////////////////////////////////////////////////
void quit() {
    endwin();
    exit(0);
}