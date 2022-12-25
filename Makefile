###################################################################
# Michael Hayworth
# 3/12/2022
###################################################################
# Makefile
# Eases the compilation of the program
###################################################################

tictactoe: main.c board.c server.h
	cc main.c board.c server.c -lcurses -o tictactoe -Wall

test:
	cc test.c server.c -o test -Wall

clean:
	rm -f tictactoe test