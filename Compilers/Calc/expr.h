// David Trimino
// dat9459
// 2021-04-06

#if !defined( __EXPR_H__ )
#define __EXPR_H__

#include <stdio.h>
#include <math.h>

//----------------------------------------------------------
typedef enum _ExprKind
{
  eBOP_EXPONENT,
  eBOP_ADD,
  eBOP_DIVIDE,
  eBOP_MULTIPLY,
  eBOP_SUBTRACT,

  eLIT_INTEGER,
  eLIT_REAL,

  eUOP_NEGATE,
  eUOP_POSITE,
} ExprKind;

typedef struct _Expr
{
  struct _Expr *next;

  ExprKind kind;

  int litInteger;
  double litReal;

  struct _Expr *left;
  struct _Expr *right;
} Expr;

//----------------------------------------------------------
void dumpExpr( Expr *e );

Expr *evalExpr( Expr *e );
void  freeAllExprs();

Expr *litInteger( int value );
Expr *litReal( double value );
Expr *oprBinary( ExprKind kind, Expr *left, Expr *right );
Expr *oprUnary( ExprKind kind, Expr *operand );

//----------------------------------------------------------
#endif
