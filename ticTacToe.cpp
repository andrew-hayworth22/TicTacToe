/////////////////////////////////////////////////////////////////////////////
//  
//  Michael Hayworth
//  ticTacToe.cpp
//
//  Tic Tac Toe Program!

#include <iostream>

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int moveCount = 0;

bool stop();
void print();

int main() {
    int player = 0;
    int move;

    do {
        print();

        player = player % 2 + 1;

        char marked;
        if(player == 1) marked = 'X';
        else marked = 'O';

        std::cout << "Player " << player << "'s turn: ";
        std::cin >> move;

        if(move == 1 && board[0] == '1')
            board[0] = marked;
        else if(move == 2 && board[1] == '2')
            board[1] = marked;
        else if(move == 3 && board[2] == '3')
            board[2] = marked;
        else if(move == 4 && board[3] == '4')
            board[3] = marked;
        else if(move == 5 && board[4] == '5')
            board[4] = marked;
        else if(move == 6 && board[5] == '6')
            board[5] = marked;
        else if(move == 7 && board[6] == '7')
            board[6] = marked;
        else if(move == 8 && board[7] == '8')
            board[7] = marked;
        else if(move == 9 && board[8] == '9')
            board[8] = marked;
        else {
            std::cout << "Invalid move!" << std::endl;
            --player;
        }
        ++moveCount;
    } while(!stop());

    if(moveCount == 9)
        std::cout << "It's a draw!" << std::endl;
    else
        std::cout << "Player " << player << " won!!!" << std::endl;

    return 1;
}

bool stop() {
    if(moveCount >= 9)
        return true;
    else if(board[0] == board[3] && board[3] == board[6])
        return true;
    else if(board[1] == board[4] && board[4] == board[7])
        return true;
    else if(board[2] == board[5] && board[5] == board[8])
        return true;
    else if(board[0] == board[1] && board[1] == board[2])
        return true;
    else if(board[3] == board[4] && board[4] == board[5])
        return true;
    else if(board[6] == board[7] && board[7] == board[8])
        return true;
    else if(board[0] == board[4] && board[4] == board[8])
        return true;
    else if(board[2] == board[4] && board[4] == board[6])
        return true;
    else return false;
}

void print() {
    std::cout "Player One(X) | Player Two(O)" << std::endl;
    std::cout << "   |   |   " << std::endl;
    std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << "   |   |   " << std::endl;
    std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
    std::cout << "___|___|___" << std::endl;
    std::cout << "   |   |   " << std::endl;
    std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
    std::cout << "   |   |   " << std::endl << std::endl;
}