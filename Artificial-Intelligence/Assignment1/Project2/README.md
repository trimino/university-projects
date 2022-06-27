# Artficial-Intelligence

**Project 2** is to implement an agent that plays the Max-Connect4 game using search. Figure 2 above shows the first few moves of a game. The game is played on a 6x7 grid, with six rows and seven columns. There are two players, player A (red) and player B (green). The two players take turns placing pieces on the board: the red player can only place red pieces, and the green player can only place green pieces. 

The game is over when all positions are occupied. Obviously, every complete game consists of 42 moves, and each player makes 21 moves. The score, at the end of the game is determined as follows: consider each quadruple of four consecutive positions on board, either in the horizontal, vertical, or each of the two diagonal directions (from bottom left to top right and from bottom right to top left). The red player gets a point for each such quadruple where all four positions are occupied by red pieces. Similarly, the green player gets a point for each such quadruple where all four positions are occupied by green pieces. The player with the most points wins the game. Your program will run in two modes: an interactive mode, that is best suited for the program playing against a human player, and a one-move mode, where the program reads the current state of the game from an input file, makes a single move, and writes the resulting state to an output file. The one-move mode can be used to make programs play against each other. Note that **THE PROGRAM MAY BE EITHER THE RED OR THE GREEN PLAYER, THAT WILL BE SPECIFIED BY THE STATE, AS SAVED IN THE INPUT FILE.** **RED PLAYER IS PLAYER: 1 and GREEN PLAYER IS PLAYER: 2**


## One-Move Mode
The purpose of the one-move mode is to make it easy for programs to compete against each other, and communicate their moves to each other using text files. The one-move mode is invoked as follows:

**python3 maxconnect4.py one-move [input_file] [output_file] [depth]**

For example:

  >python3 maxconnect4.py one-move input2.txt o.txt 10 

In this case, the program simply makes a single move and terminates. In particular, the program should:
  - Read the input file and initialize the board state and current score, as in interactive mode.
  - Print the current board state and score. If the board is full, exit.
  - Choose and make the next move.
  - Print the current board state and score.
  - Save the current board state to the output file IN EXACTLY THE SAME FORMAT THAT IS USED FOR INPUT FILES.
  - Exit

 
 
 ## Interactive Mode
In the interactive mode, the game should run from the command line with the following arguments (assuming a Java implementation, with obvious changes for C++ or other implementations):
**python3 maxconnect4.py interactive [input_file] [computer-next/human-next] [depth]**

For example:

  > python3 maxconnect4.py interactive input1.txt computer-next 7


- Argument interactive specifies that the program runs in interactive mode.
- Argument [input_file] specifies an input file that contains an initial board state. This way we can start the program from a non-empty board state. If the input file does not exist, the program should just create an empty board state and start again from there.
- Argument [computer-first/human-first] specifies whether the computer should make the next move or the human.
- Argument [depth] specifies the number of moves in advance that the computer should consider while searching for its next move. In other words, this argument specifies the depth of the search tree. Essentially, this argument will control the time takes for the computer to make a move.

After reading the input file, the program gets into the following loop:
1. If computer-next, goto 2, else goto 5.
2. Print the current board state and score. If the board is full, exit.
3. Choose and make the next move.
4. Save the current board state in a file called computer.txt (in same format as input file).
5. Print the current board state and score. If the board is full, exit.
6. Ask the human user to make a move (make sure that the move is valid, otherwise repeat request to the user).
7. Save the current board state in a file called human.txt (in same format as input file).
8. Goto 2.


## About the Code
* **aimove.py**
  - Describes the AIMove class
* **MaxConnect4Game.py** 
  - The defines the Connect 4 game 
  - All AI Implementation is in this file
  - Also keeps track of the gameboard
* **maxconnect4.py** 
  - The implmentation of maxConnect4Game class in MaxConnect4Game.py
  - Also handles the interaction (one-move/interaction)
