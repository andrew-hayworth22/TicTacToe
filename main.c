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
#include "server.h"

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
void oops(const char*);

// Game variables
struct Board board;
int isP1 = 0;
int isP1Turn = 1;
char* prompt = "Player 1's Turn: ";
int isOver = 0;

// Server variable
int server_sock;

///////////////////////////////////////////////////////////////////////
// main() -> main logic flow of the game
///////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    // Determine if it is in server mode
    if(argc == 2)
        isP1 = 1;
    else if(argc != 3)
        oops("Invalid input");

    // If it's a server, set up the server
    if(isP1 == 1) {
        int sock_fd;

        // Create the socket
        if((server_sock = make_server_socket(atoi(argv[1]))) == -1)
            oops("Error starting server");

        // Wait for a call
        printf("Awaiting connection...\n");
        sock_fd = accept(server_sock, NULL, NULL);
        //Verify connection
        if(sock_fd == -1)
            oops("Error connecting");
        printf("Player successfully connected\n");
    }

    // If it's a client, connect to the server
    else {
        if(SCconnect(argv[1], atoi(argv[2])) == -1)
            oops("Failed to connect to server");
    }

    // Set up game
    setUp();
    // Draw initial screen
    refreshScreen();

    // Get input, make a move on that input, and refresh screen
    char buf[MAXMSG];
    int c;
    while(1) {
        if(isP1 && !isP1Turn) {
            if(read(server_sock, buf, 1) < 0)
                oops("Error reading stream");
            
            makeMove(atoi(buf[0]));
            strcpy(buf, "");
        }
        else if(!isP1 && isP1Turn) {
            if(SCgetstr(buf, 1) == -1)
                oops("Error reading from server");
            makeMove(atoi(buf[0]));
            strcpy(buf, "");
        }
        refreshScreen();

        if(isOver)
            gameOver();

        while((c = getchar()) != QUIT_CHAR) {
            buf[0] = c;
            if(isP1)
                write(server_sock, buf, 1);
            else
                SCtell_server(buf);
            
            makeMove(c);
            refreshScreen();

            if(isOver)
                gameOver();
        }

        // Gracefully quit if exit character is given
        quit();
    }
    
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

void oops(const char* str) {
    perror(str);
    exit(1);
}