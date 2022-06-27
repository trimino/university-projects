#!/usr/bin/env python

# Written by Chris Conly based on C++
# code provided by Dr. Vassilis Athitsos
# Written to be Python 2.4 compatible for omega

from ast import arg
import sys
from MaxConnect4Game import *


def oneMoveGame(currentGame):
    if currentGame.pieceCount == 42:    # Is the board full already?
        print ('BOARD FULL\n\nGame Over!\n')
        sys.exit(0)

    # TODO: CHANGE ME
    #currentGame.aiPlay() # Make a move (only random is implemented)
    currentGame.minMaxDecision(10)

    print ('Game state after move:')
    currentGame.printGameBoard()

    currentGame.countScore()
    print('Score: Player 1 = %d, Player 2 = %d\n' % (currentGame.player1Score, currentGame.player2Score))

    currentGame.printGameBoardToFile()
    currentGame.gameFile.close()


def interactiveGame(currentGame, depth):
    # Fill me i
    while(currentGame.pieceCount != 42):
        if currentGame.currentTurn == 1:
            # AI's Turn to make a move
            print('AI\'s turn <-----')
            print('AI deciding move....')
            currentGame.minMaxDecision(depth)
            currentGame.printGameBoard()
            currentGame.currentTurn = 2
        else:
            # Humans turn to make a move
            print('Human\'s <-----')
            print('Human make a move')
            move = input('Please pick a column: ')
            if move.isdigit() and int(move) < 8:
                currentGame.playPiece(int(move) - 1)
                currentGame.printGameBoard()
                currentGame.currentTurn = 1
            else:
                print('Move unable to make because it is not a number or its greater than 7')
        currentGame.countScore()
        print('\nScore: Player 1 = %d, Player 2 = %d\n' % (currentGame.player1Score, currentGame.player2Score)+ '\n')
    
    winner = '2'
    if currentGame.player1Score > currentGame.player2Score:
        winner = '1'

    sys.exit('PLAYER ' + winner + ' WINNS')


def main(argv):
    # Make sure we have enough command-line arguments
    if len(argv) != 5:
        print('Four command-line arguments are needed:')
        print('Usage: %s interactive [input_file] [computer-next/human-next] [depth]' % argv[0])
        print('or: %s one-move [input_file] [output_file] [depth]' % argv[0])
        sys.exit(2)

    game_mode, inFile = argv[1:3]

    if not game_mode == 'interactive' and not game_mode == 'one-move':
        print('%s is an unrecognized game mode' % game_mode)
        sys.exit(2)

    currentGame = maxConnect4Game() # Create a game

    # Try to open the input file
    try:
        currentGame.gameFile = open(inFile, 'r')
    except IOError:
        sys.exit("\nError opening input file.\nCheck file name.\n")

    # Read the initial game state from the file and save in a 2D list
    file_lines = currentGame.gameFile.readlines()
    currentGame.gameBoard = [[int(char) for char in line[0:7]] for line in file_lines[0:-1]]
    currentGame.currentTurn = int(file_lines[-1][0])
    currentGame.gameFile.close()

    print('\nMaxConnect-4 game\n')
    print('Game state before move:')
    currentGame.printGameBoard()

    # Update a few game variables based on initial state and print the score
    currentGame.checkPieceCount()
    currentGame.countScore()
    print('Score: Player 1 = %d, Player 2 = %d\n' % (currentGame.player1Score, currentGame.player2Score))

    if game_mode == 'interactive':
        if argv[3] == 'human-next':
            currentGame.currentTurn = 2
        else:
            currentGame.currentTurn = 1
        interactiveGame(currentGame, int(argv[4])) 
    else:
        # Set up the output file
        outFile = argv[3]
        try:
            currentGame.gameFile = open(outFile, 'w')
        except:
            sys.exit('Error opening output file.')
        oneMoveGame(currentGame) # Be sure to pass any other arguments from the command line you might need.


if __name__ == '__main__':
    main(sys.argv)



