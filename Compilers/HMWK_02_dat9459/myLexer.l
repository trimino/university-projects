  // David Trimino
  // dat9459
  // 2021-03-08

  //---- DEFINITIONS  --------------------------------------------

%option header-file="lex.yy.h"

/* Our input is not from an interactive source. */
%option never-interactive
/* Don't generate the default rule. */
%option nodefault
/* We don't directly read the input. */
%option noinput
/* Don't include <unistd.h>. */
%option nounistd
/* We don't 'unput' a character back. */
%option nounput
/* Don't call yywrap() on EOF. */
%option noyywrap

/* These two options are doubled to get more detailed reports. */
/* Write performance report to stderr. */
%option perf-report perf-report
/* Write statistics summary to stderr. */
%option verbose verbose

/* Generate warning messages for goofs. */
%option warn

/* Maintain current line number in yylineno. */
%option yylineno

%{
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token category names.  Usually defined by bison.  Since this is
//    a simple flex-only solution, we define them ourselves.
//   The numbers start at 256 to avoid clashing with the literal
//   'single character' token categories.
enum {
  tok_ID = 256,
  tok_INT_LIT,
  tok_REAL_LIT,
  tok_STR_LIT,
};

// This union is usually defined by bison.  Since this is a
//    simple flex-only solution, we have to make it ourselves.
union {
  double realval;
  int    intval;
} yylval;

// flex doesn't track the column number automatically.  We
//    keep these up-to-date ourselves.  We want to know not
//    only the column a token begins at but also where it ends.
int yycolnoBegin;
int yycolnoEnd;

//    Calling this routine at the start of an action routine will
//    set the current token's beginning and ending column numbers.
void _setTokenPos();
%}

/* Defined names ... */
BINARY_DIGIT  [0-1]
DIGIT         [0-9]
EXPONENT      [eE][-+]?[0-9]+
HEX_DIGIT     [0-9a-fA-F]
LETTER        [a-zA-Z]
OCTAL_DIGIT   [0-7]

HEX_ESCAPE    \\x{HEX_DIGIT}{1,2}
OCTAL_ESCAPE  \\[0-3]?{OCTAL_DIGIT}{1,2}

BINARY_LIT    [0][b]{BINARY_DIGIT}+
OCTAL_LIT     [0][o][0-3]?{OCTAL_DIGIT}+
HEX_LIT       [0][x]{HEX_DIGIT}+

ORDINARY_LIT  [']([^'\\\n])[']
ESCAPE_LIT    ['](\\[\\abfnrtv'"?])[']

%% //---- RULES --------------------------------------------------

{DIGIT}+  {
  // Set the token's position.
  _setTokenPos();

  // Convert the digit characters in yytext into an integer number
  //  and save that number in the proper slot of the yylval union.
  yylval.intval = atoi( yytext );

  // Let the caller know that an integer literal has been scanned.
  return tok_INT_LIT;
}


{BINARY_LIT}|{OCTAL_LIT}|{HEX_LIT}  {
  // Set the token's postion
  _setTokenPos();

  // Value of the end is set by function to the next character in yytext after last valid character
  char *end;

  if ( yytext[1] == 'b'){
    yytext = yytext + 2;
    yylval.intval = strtol( yytext, &end, 2 );  
  }

  else if ( yytext[1] == 'o' ){
    yytext = yytext + 2;
    yylval.intval = strtol( yytext, &end, 8 );
  }

  else if ( yytext[1] == 'x' ){
    yytext = yytext + 2;
    yylval.intval = strtol( yytext, &end, 16 );
  }

  else 
    printf("Illegal base: %s", yytext);
  
  return tok_INT_LIT;
}


{ORDINARY_LIT}  {
  _setTokenPos();
    
  yylval.intval =  (int) yytext[1];
  
  return tok_INT_LIT;
}


{ESCAPE_LIT}  {
  _setTokenPos();

  if ( yytext[2] == 'a' )
    yylval.intval = 7;
  
  else if ( yytext[2] == 'b' )
    yylval.intval = 8;
  
  else if ( yytext[2] == 't' )
    yylval.intval = 9;

  else if ( yytext[2] == 'n' )
    yylval.intval = 10;
  
  else if ( yytext[2] == 'v' )
    yylval.intval = 11;

  else if ( yytext[2] == 'f' )
    yylval.intval = 12;

  else if ( yytext[2] == 'r' )
    yylval.intval = 13;
  
  else if ( yytext[2] == '\"' )
    yylval.intval = 34;
  
  else if ( yytext[2] == '\'' )
    yylval.intval = 39;
  
  else if ( yytext[2] == '\?' )
    yylval.intval = 63;
  
  else if ( yytext[2] == '\\')
    yylval.intval = 92;
  
  else
    printf("ILLEGAL ERROR: %s\n", yytext);

  return tok_INT_LIT;
}


[']{HEX_ESCAPE}[']  {
  // Set the token's postion
  _setTokenPos();
  
  char *end; 

  // Move pointer to the actual value
  yytext = yytext + 3;

  // The identifier is the text in yytext
  yylval.intval = strtol( yytext, &end, 16 );

  // Let the caller know that a int literal has been scanned
  return tok_INT_LIT;
} 


[']{OCTAL_ESCAPE}[']  {
  // Set the token's postion
  _setTokenPos();

  char *end; 
  yytext = yytext + 2;
  
  // The identifier is the text in yytext
  yylval.intval = strtol( yytext, &end, 8 );

  // Let the caller know that an int literal has been scanned
  return tok_INT_LIT;
}

  
({DIGIT}+{EXPONENT})|({DIGIT}*({DIGIT}[.]|[.]{DIGIT}){DIGIT}*{EXPONENT}?) {
  // Set the token's position
  _setTokenPos();

  // The identifier is the text in yytext
  yylval.realval = atof( yytext );

  // Let the caller know that a real literal has been scanned
  return tok_REAL_LIT;
}


({LETTER}|_)({LETTER}|_|{DIGIT})*  {
  // Set the token's position.
  _setTokenPos();

  // The identifier is the text in yytext.  We don't have to
  //  convert it to anything else.

  // Let the caller know that an identifier has been scanned.
  return tok_ID;
}


["][^"\n]*["]  {
  // Set the token's position.
  _setTokenPos();

  // The string literal is the text in yytext.  We don't have to
  //  convert it to anything else.

  // Let the caller know that a string literal has been scanned.
  return tok_STR_LIT;
}


[ \f\t\v]+  {
  // Even though whitespace is not returned as a token, we have to
  //  count how many characters it was so the column positions of
  //  any tokens after the whitespace will be correct.
  _setTokenPos();
}


[\r\n]+|[//](.*)     {
  // \r and \n start new lines.  Therefore we want the column
  //  count to go back to the left margin again.
  yycolnoBegin = yycolnoEnd = 0;
}


.       {
  // An illegal character.
  //  This happens when a character is scanned that is not taken
  //  by any other rule's pattern.

  // As with whitespace, even though the illegal character does
  //  not return as a token, we have to track its position so we
  //  can properly track the column positions of anything after
  //  it on the same line.
  _setTokenPos();

  // We ignore the illegal character, but we do print a message
  //  saying that we ignored it.  (Hey, we are conscientious and
  //  tidy! :)

  //  Notice how we use yylineno and yycolnoBegin in the message
  //  so the user can look in their input file and directly find
  //  the spot with the illegal character.  (We don't use
  //  yycolnoEnd since the illegal character is a single
  //  character.)
  printf( "(%d:%d) Illegal character '%s' ignored.\n",
    yylineno, yycolnoBegin, yytext );
}

%% //---- USER CODE ----------------------------------------------

int main( int argc, char *argv[] )
{
  //--------------------------------------
  // Argument processing

  // Argument 0 is the name of the program.  We use it when
  //  printing messages.
  char *progName = argv[0];

  // After the program name (which is normally what argv[0]
  //  represents), we want the name of the file we are going to
  //  scan.  If it's not supplied, complain and exit.
  if ( argc != 2 ) {
    // Useful nag message about how to invoke this program.
    printf( "Usage: %s <inFileName>\n", progName );

    // Exit with useful error code so invoker knows why we failed.
    exit( 1 );
  }

  // Argument 1 is the name of the file we are to scan.  Try to
  //  open it for read.  If not possible, complain and exit.
  char *fileName = argv[1];
  FILE *inFP     = fopen( fileName, "r" );
  if ( inFP == NULL ) {
    // Useful nag message about WHY we couldn't open the indicated
    //  filename for reading.
    printf( "%s: Unable to open \"%s\" for input.  (%d) %s.\n",
      progName, fileName, errno, strerror( errno ) );

    // Exit with useful error code so invoker knows why we failed.
    exit( 2 );
  }

  //--------------------------------------
  // Initialize the current location.
  //  flex updates yylineno automatically, but it does not
  //    initialize it.  We start on line 1.  (Duh.)
  //  We have to keep track of yycolnoBegin and yycolnoEnd
  //    ourselves.  We start them at 0 so we can just add each
  //    time we track a new token.  (See _setTokenPos().)
  yylineno     = 1;
  yycolnoBegin = 0;
  yycolnoEnd   = 0;

  //--------------------------------------
  // Start reading from this input file.
  yyrestart( inFP );

  //--------------------------------------
  // Get the tokens one-by-one and print an informative message
  //  about what we got.
  int tok;
  while ( ( tok = yylex() ) ) {
    printf( "(%d:%d-%d) ", yylineno, yycolnoBegin, yycolnoEnd );

    switch ( tok ) {
      case tok_ID:
        printf( "ID '%s'\n", yytext );
        break;

      case tok_INT_LIT:
        printf( "INT_LIT %d\n", yylval.intval );
        break;

      case tok_REAL_LIT:
        printf( "REAL_LIT %.15e\n", yylval.realval );
        break;

      case tok_STR_LIT:
        printf( "STR_LIT %s\n", yytext );
        break;

      default:
        printf( "Unknown token category %d?\n", tok );
        break;
    }
  }

  //--------------------------------------
  // All done!  Be tidy and get rid of allocated objects, close
  //   files, etc.
  fclose( inFP );

  // No errors!
  return 0;
}

void _setTokenPos()
{
  yycolnoBegin = yycolnoEnd + 1;
  yycolnoEnd   = yycolnoBegin + yyleng - 1;
}
//----------------------------------------------------------------
