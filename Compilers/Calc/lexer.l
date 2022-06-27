/* David Trimino   */
/* dat9459         */
/* 2021-04-06      */

  //---- DEFINITIONS  --------------------------------------------

/* Ensure the lexer is reentrant -- avoid the original mess of
    global variables for everything. */
%option reentrant

/* We're a lexer for a bison-generated parser, so adjust our
    functional interface to match. */
%option bison-bridge

/* Establish the connection between bison and flex for tracking
    locations of tokens.  (Even with this, the locations are NOT
    tracked automatically.  We have to do that ourself.  See
    below for more details. */
%option bison-locations

/* Create the lexer exports header file with this name. */
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
#include <stdio.h>
#include "expr.h"
#include "parser.tab.h"

void printLocation( YYLTYPE *loc, FILE *fp );
static void _updateYYLLOC( char *txt, YYLTYPE *loc, int lineno );

/* YY_USER_ACTION is automatically inserted at the beginning of
    every action routine.  All we use it for is to help us do the
    tracking of token line and column locations. */
#define YY_USER_ACTION _updateYYLLOC( yytext, yylloc, yylineno );

%}

/* Defined names ... */
DIGIT         [0-9]
EXPONENT      [eE][-+]?{DIGIT}+

BINARY_DIGIT  [0-1]
HEX_DIGIT     [0-9a-fA-F]
OCTAL_DIGIT   [0-7]

BINARY_LIT    [0][b]{BINARY_DIGIT}+
OCTAL_LIT     [0][o][0-3]?{OCTAL_DIGIT}+
HEX_LIT       [0][x]{HEX_DIGIT}+

%% //---- RULES --------------------------------------------------

"-"     { return TOKEN_MINUS; }
"+"     { return TOKEN_PLUS; }
"/"     { return TOKEN_SLASH; }
"*"     { return TOKEN_STAR; }
"^"	{ return TOKEN_EXPONENT; }
"("     { return TOKEN_LPAREN; }
")"     { return TOKEN_RPAREN; }

{DIGIT}+  {
  // A string of decimal digits -- an integer literal.
  sscanf( yytext, "%d", &yylval->litInteger );
  return TOKEN_INTEGER;
}

(({DIGIT}*(({DIGIT}\.)|(\.{DIGIT})){DIGIT}*){EXPONENT}?) {
  // The kind of real literal that has a decimal point in it
  //  somewhere;  either at the front, the back, or somewhere in
  //  the middle.  The exponent is optional since the DP indicates
  //  it's a real literal.
  yylval->litReal = atof( yytext );
  return TOKEN_REAL;
}

({DIGIT}+{EXPONENT})  {
  // The kind of real literal that does NOT have a DP.  For this
  //  style, the exponent is required.
  yylval->litReal = atof( yytext );
  return TOKEN_REAL;
}


{BINARY_LIT}|{OCTAL_LIT}|{HEX_LIT} {
  char *end;

  if ( yytext[1] == 'b' ){
    yytext = yytext + 2;
    yylval->litInteger = strtol( yytext, &end, 2 );
  }

  else if ( yytext[1] == 'o' ){
    yytext = yytext + 2;
    yylval->litInteger = strtol( yytext, &end, 8 );
  }

  else if ( yytext[1] == 'x' ){
    yytext = yytext + 2;
    yylval->litInteger = strtol( yytext, &end, 16 );
  }

  else 
    printf("Illegal base: %s", yytext);

  return TOKEN_INTEGER;
}


[ \f\n\r\t\v]+  {  /* Ignore extraneous whitespace. */ }

.           {
  // Illegal character.  Ignore it, but print a message.
  printLocation( yylloc, stdout );

  printf( ":  Illegal character '%s' ignored.\n", yytext );
}

%% //---- USER CODE ----------------------------------------------

void printLocation( YYLTYPE *loc, FILE *fp )
{
  if ( loc->first_line == loc->last_line ) {
    if ( loc->first_column == loc->last_column ) {
      fprintf( fp, "%d(%d)",
        loc->first_line, loc->first_column );
    } else {
      fprintf( fp, "%d(%d-%d)",
        loc->first_line,
        loc->first_column, loc->last_column );
    }
  } else {
    fprintf( fp, "%d(%d)-%d(%d)",
      loc->first_line, loc->first_column,
      loc->last_line, loc->last_column );
  }
}

/*----------------------------------------------------------------
  All the poop we need to track the location of a token:
    which line it's on, which column it starts in, and which
    column it ends in. */
static int yycolnoBegin;
static int yycolnoEnd;

void resetColumnPosition()
{
  yycolnoBegin = yycolnoEnd = 0;
}

static void _updateYYLLOC( char *txt, YYLTYPE *loc, int lineno )
{
  // The first line of this token has to be the last line of the
  //  previous token.
  loc->first_line = loc->last_line;

  // The last line of this token is whatever line flex thinks we
  //  are on now.
  loc->last_line  = lineno;

  // The first column of this token has to be one past the last
  //  column of the previous token.
  yycolnoBegin = yycolnoEnd + 1;

  // We count the characters this token matched to determine its
  //  last column.  If the token includes a newline or a carriage
  //  return, we start over again at the left margin.
  for ( int i=0; txt[i] != '\0'; i++ ) {
    if ( txt[i] == '\n' || txt[i] == '\r' ) {
      yycolnoEnd = 0;
    } else {
      yycolnoEnd++;
    }
  }

  // Now that we know the begin / end column of the token, place
  //  this info in the yylloc location so flex / bison can see it.
  loc->first_column = yycolnoBegin;
  loc->last_column  = yycolnoEnd;

#if defined( DEBUG )
  // Useful info when debugging the scanner, but very noisy for
  //  any production use.
  printLocation( loc, stdout );
  printf( ": >%s<\n", txt );
#endif
}

//----------------------------------------------------------------
