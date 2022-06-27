# Compilers homework 2


**Homework 2** is to demonstrate the ability to write some more simple Regular Expressions for various token categories and their associated processing routines


## Token Categories

### Full Real Literals
  1.  A decimal point followed by a series of decimal digits, 0 through 9
  2.  A series of decimal digits followed by a decimal point
  3.  A series of decimal digits followed by a decimal point followed by a series of decimal digits.
  4.  Either (1), (2), or (3) followed by an exponent.
  5.  A series of decimal digits followed by an exponent.
  6.  An exponent is the letter e or E ( optionally followed by a + or - sign ) followed by a series of decimal digits.


### Interger Based Literals
  1.  The characters 0b followed by a series of binary digits, 0 and 1.
  2.  The characters 0o followed by a series of octal digits, 0 though 7.
  3.  The characters 0x followed by a series of hex digits, 0 through 9 and A through F (upper or lower case).


### Character Literal
  1.  Any character except [', \\, or a newline].
  2.  An escape sequence.


### Escape Sequence
  1.  A '\' character followed by one of the characters ', ", ?, \, a, b, f, n, r, t, v 
  2.  The following are the integer value of each of these sequences: 
	  >\\'    39 </br>
	   \\"    34 </br>
	   \\?    63 </br>
	   \\\    92 </br>
	   \\a     7 </br>
	   \\b     8 </br>
	   \\f    12 </br>
	   \\n    10 </br>
	   \\r    13 </br>
	   \t     9 </br>
	   \v    11 </br>
   3.  The character x followed by one or two hex digits. The integer value of this sequence is the value of the hex digits
   4.  One, two, or three octal digits.  If three octal digits are supplied, the first digit is limited to the digits 0, 1, 2, 3.  The integer value of this sequence is the value of the octal digits



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
