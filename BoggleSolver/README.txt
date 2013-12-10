Bog Solver
Project 2 Part 2
Comp15- Spring 2013
Shea Clark-Tieche

Bruce's Files:
Dictionary.cpp 
Dictionary.h 
BogWordList.h

BogSolver: This program was written to solve a boggle board. It uses a 2D dyanmic array to store all the letters in the board also keeping track of their coordinates. This program includes a dictionary against which it compares all possible words in the boggle board to see if it's a valid solution. The program uses recursion to go through each spot on the board and use its neighbors to build potential words. When words are found, they're stored in a dynamic array of BogWords which is made up of arrays of characters.
Files:
BogSolver.h
BogSolver.cpp
solverMain.cpp

BogValidator:
This program takes in user input and sees if they are valid solutions for a given boggle board. It operates in much of the same way as the solver solution. Essentially, it solves a boggle board using a dictionary of real words given by a user. It outputs either OK or NO before each word entered depending on if it's valid or not. The boggle board is solved by iterating through each spot and recursing through each possible neighbor until all neighbors are invalid.
Files:
BogValidator.h
BogValidator.cpp
checkerMain.cpp

BogScorer: This program takes the output produced by bogValidator to correctly count the number of words and count the score based on the proper boggle rules.
Files:
BogScorer.h
BogScorer.cpp
scorerMain.cpp

AllFiles to Provide:
BogScorer.h
BogScorer.cpp
scorerMain.cpp
BogValidator.h
BogValidator.cpp
checkerMain.cpp
BogSolver.h
BogSolver.cpp
solverMain.cpp
Dictionary.cpp 
Dictionary.h 
BogWordList.h

Compile Codes:
bbsolver: g++ -g -Wall -Wextra Dictionary.cpp BogSolver.cpp solverMain.cpp -o bbsolver
bbchecker: g++ -g -Wall -Wextra Dictionary.cpp BogValidator.cpp checkerMain.cpp -o bbchecker
bbscorer: g++ -g -Wall -Wextra BogScorer.cpp scorerMain.cpp -o bbscorer
