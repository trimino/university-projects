// David Trimino
// dat9459
// 2021-04-06

//----------------------------------------------------------
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "expr.h"

#include "parser.tab.h"
#include "lex.yy.h"

extern void resetColumnPosition();

//----------------------------------------------------------
int parseString( const char *exprStr, Expr **expr )
{
  YY_BUFFER_STATE  bufferState;
  int              parseState;
  yyscan_t         scanner;

  // Initialize the Lexical Analyzer (the scanner).
  if ( yylex_init( &scanner ) ) {
    printf(
      "Unable to initialize the lexical analyzer.  Error is (%d) \"%s\".\n",
      errno, strerror( errno ) );

    // We have to signal to the caller that we didn't even
    //   get to the parser so there's no expression.
    *expr = NULL;

    return -1;
  }

  // Set the given string as the input for the scanner to scan.
  bufferState = yy_scan_string( exprStr, scanner );

  // Reset the line number, column position.
  yyset_lineno( 1, scanner );
  resetColumnPosition();

  // Using the established scanner as a source of tokens, parse
  //   the input.  The returned state tells us whether it was a
  //   success or not.
  parseState = yyparse( expr, scanner );

  // Now that the parse is over, dispose of the scanner info.
  yy_delete_buffer( bufferState, scanner );
  yylex_destroy( scanner );

  // Return the state we got back from parsing.
  return parseState;
}

//----------------------------------------------------------
int main()
{
  char    *linePtr = NULL;
  size_t   sz = 0;
  ssize_t  len;
  ssize_t  start;

  Expr *expr;
  int   parseState;

  while ( 1 ) {
    // Prompt the user for some input.
    printf( "> " );
    fflush( stdin );

    // Get a line of characters.
    len = getline( &linePtr, &sz, stdin );

    // Oops, some error or maybe EOF.
    if ( len == -1 ) break;

    // Get rid of the newline character at the end of the input
    //  and any whitespace at the beginning of the input.
    linePtr[len-1] = '\0';
    for ( start=0; linePtr[start] && isspace( linePtr[start] ); start++ ) {}

    // If the string is empty, don't try to parse it.
    if ( !linePtr[start] ) continue;

    // Parse the string!
    parseState = parseString( linePtr + start, &expr );
    if ( parseState ) {
      // Didn't parse --
      //   Inform the user what happened.
      printf(
        "Unable to parse \"%s\".  Error is (%d) \"%s\".\n",
        linePtr,
        parseState,
        parseState == -1 ? "Unable to initialize lexical analyzer" :
        parseState ==  1 ? "Invalid input" :
        parseState ==  2 ? "Out of memory" : "Unknown error?" );
    } else {
      // Did parse -- show expression's structure.
      dumpExpr( expr );

      // Evaluate the expression and show the result.
      printf( "\n\"%s\" ==>\n", linePtr );
      dumpExpr( evalExpr( expr ) );
    }

    // Deallocate all expression nodes ...
    freeAllExprs();
  }

  // If we have a line buffer, deallocate it.
  if ( linePtr != NULL ) free( linePtr );

  return 0;
}

//----------------------------------------------------------
