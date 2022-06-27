# Compilers homework 1


**Homework 1** is to demonstrate a working flex/C development environment and to demonstrate ability to write a simple Regular Expression for a token category and its associated processing routine


## Compilation Instruction and Programming Versions ##

* The programming language used is C and flex and no third party was used
* The user needs a gcc compiler to compile the code (version 8.3.0-6)
* The user needs to ensure a flex version of 2.6 in order for it to work

### To Compile run the following:
	make clean 
	make 
	./myLexer Examples/id.asl	> id-output.txt 
	./myLexer Examples/int.asl	> int-output.txt 
	./myLexer Examples/real.asl	> real-output.txt 
	./myLexer Examples/str-output	> str-output.txt 


Once the program has been compiled and run compare the files of the program to the files in the "Final" directory (which has the desired output)
