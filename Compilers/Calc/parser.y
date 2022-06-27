/* David Trimino   */
/* dat9459         */
/* 2021-04-06      */

   /*--- DEFINITIONS -------------------------------------------*/
%{
#include <stdio.h>

#include "expr.h"

#include "parser.tab.h"
#include "lex.yy.h"

void yyerror( YYLTYPE *, Expr **, void *, const char * );

%}

%code requires {
  typedef void *yyscan_t;
}

%define api.pure full

%defines

%locations

%lex-param   { yyscan_t scanner }
%parse-param { Expr **expr }
%parse-param { yyscan_t scanner }

  /* Value stack type */
%union {
  int     litInteger;
  double  litReal;
  Expr   *expr;
}

  /* Token names (and types, where necessary) */
%token TOKEN_MINUS
%token TOKEN_PLUS
%token TOKEN_SLASH
%token TOKEN_STAR
%token TOKEN_EXPONENT

%token TOKEN_LPAREN
%token TOKEN_RPAREN

%token <litInteger> TOKEN_INTEGER
%token <litReal>    TOKEN_REAL

  /* Nonterminal types */
%type <expr> expr

  /* Operator precedence / associativity */
%left TOKEN_MINUS TOKEN_PLUS
%left TOKEN_SLASH TOKEN_STAR
%right NEGATE POSITE
%right TOKEN_EXPONENT

%% /*--- RULES -------------------------------------------------*/

start
  : expr { *expr = $1; }
  ;

  /* Binary operators */
expr
  : expr TOKEN_MINUS    expr { $$ = oprBinary( eBOP_SUBTRACT, $1, $3 ); }
  | expr TOKEN_PLUS     expr { $$ = oprBinary( eBOP_ADD,      $1, $3 ); }
  | expr TOKEN_SLASH    expr { $$ = oprBinary( eBOP_DIVIDE,   $1, $3 ); }
  | expr TOKEN_STAR     expr { $$ = oprBinary( eBOP_MULTIPLY, $1, $3 ); }
  | expr TOKEN_EXPONENT expr { $$ = oprBinary( eBOP_EXPONENT, $1, $3 ); }
  ;

  /* Unary operators */
expr
  : TOKEN_MINUS expr  %prec NEGATE  { $$ = oprUnary( eUOP_NEGATE, $2 ); }
  | TOKEN_PLUS  expr  %prec POSITE  { $$ = oprUnary( eUOP_POSITE, $2 ); }
  ;

  /* Literals */
expr
  : TOKEN_INTEGER         { $$ = litInteger( $1 ); }
  | TOKEN_REAL            { $$ = litReal( $1 ); }
  ;

  /* Nesting */
expr
  : TOKEN_LPAREN expr TOKEN_RPAREN     { $$ = $2; }
  ;

%% /*--- USER CODE ---------------------------------------------*/

void yyerror( YYLTYPE *llocp, Expr **_expr, void *_scanner, const char *msg )
{
  /* Unused at present */ (void) _expr; (void) _scanner;

  if ( llocp->first_line == llocp->last_line ) {
    if ( llocp->first_column == llocp->last_column ) {
      printf( "%d(%d): ",
        llocp->first_line, llocp->first_column );
    } else {
      printf( "%d(%d-%d): ",
        llocp->first_line,
        llocp->first_column, llocp->last_column );
    }
  } else {
    printf( "%d(%d)-%d(%d): ",
      llocp->first_line, llocp->first_column,
      llocp->last_line, llocp->last_column );
  }

  printf( "%s\n", msg );
}

/*--------------------------------------------------------------*/
