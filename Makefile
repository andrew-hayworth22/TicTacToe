###################################################################
# Michael Hayworth
# 3/12/2022
###################################################################
# Makefile
# Eases the compilation of the program
###################################################################

tictactoe: main.c board.c
	cc main.c board.c -lcurses -o tictactoe -Wall

clean:
	rm -f tictactoe