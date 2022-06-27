// David Trimino
// dat9495
// 2021-04-06

//----------------------------------------------------------------
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "expr.h"

static Expr *_evalBOPIntInt( ExprKind opr, Expr *left, Expr *right );
static Expr *_evalBOPRealReal( ExprKind opr, Expr *left, Expr *right );
static Expr *_evalBOPMRealMReal( ExprKind opr, Expr *left, Expr *right );

//----------------------------------------------------------------
// These have to be in the same order as the enum _ExprKind.
char *_exprKindStr[] = {
  "EXPONENT", "ADD", "DIVIDE", "MULTIPLY","SUBTRACT",
  "INTEGER", "REAL",
  "NEGATE",  "POSITE"
};

//----------------------------------------------------------------
// Some standard literals ...
Expr *_zeroIntLit;    // Literal Integer 0.
Expr *_oneIntLit;     // Literal Integer 1.
Expr *_zeroRealLit;   // Literal Real 0.0.

//----------------------------------------------------------------
// We keep a linked list of every Expr node that gets allocated
//   so they are easy to clean up later.
static Expr *_exprList;

// Allocate an Expr node -- by default we make it a literal
//    integer 0.
// Return NULL if the allocation fails.
static Expr *_allocExpr()
{
  // Get a zeroed-out expression structure.
  Expr *e = (Expr *) calloc( 1, sizeof( Expr ) );

  // Oops, couldn't allocate!
  if ( e == NULL ) return NULL;

  // Make the newly allocated expr struct a literal integer 0.
  //  (Remember, all fields are zero since we used calloc().)
  e->kind = eLIT_INTEGER;

  // If nothing is on the expr list yet, that means we have to
  //  create the standard literals.
  int needInit = _exprList == NULL;

  // Stick this newly created literal on the list of all expr
  //  structs.
  e->next   = _exprList;
  _exprList = e;

  // If we needed to create the standard literals, do so now.
  if ( needInit ) {
    _zeroIntLit  = litInteger( 0 );
    _oneIntLit   = litInteger( 1 );
    _zeroRealLit = litReal( 0.0 );
  }

  // Success!  Return the literal we just created.
  return e;
}

// Free all Expr nodes that have been allocated so far.
void freeAllExprs()
{
  Expr *e    = _exprList;
  Expr *next = NULL;

  // As long as there's an expr struct on the expr struct list,
  //  free it.  We go down the list freeing them one after
  //  another, remembering the pointer to the next one as we go.
  while ( e ) {
    next = e->next;
    free( e );
    e = next;
  }

  // List is empty now ...
  _exprList = NULL;
}

//----------------------------------------------------------------
// Dump the given Expr node (hierarchically).
static void _dumpExprInternal( Expr *e, int indent, FILE *fp )
{
  switch ( e->kind ) {
    //--------------------------------------
    // Binary operators
    case eBOP_EXPONENT:		
    case eBOP_ADD :
    case eBOP_DIVIDE :
    case eBOP_MULTIPLY :
    case eBOP_SUBTRACT :
      fprintf( fp, "%*c(BOP %s\n",
        indent, ' ', _exprKindStr[ e->kind ] );

      _dumpExprInternal( e->left,  indent+1, fp );
      _dumpExprInternal( e->right, indent+1, fp );

      fprintf( fp, "%*c)\n",
        indent, ' ' );

      break;

    //--------------------------------------
    // Unary operators
    case eUOP_NEGATE :
      fprintf( fp, "%*c(UOP %s\n",
        indent, ' ', _exprKindStr[ e->kind ] );

      _dumpExprInternal( e->left,  indent+1, fp );

      fprintf( fp, "%*c)\n",
        indent, ' ' );

      break;

    case eUOP_POSITE :
      fprintf( fp, "%*c(UOP %s\n",
        indent, ' ', _exprKindStr[ e->kind ] );

      _dumpExprInternal( e->left, indent+1, fp );

      fprintf( fp, "%*c\n", 
        indent, ' ' );

      break;

    //--------------------------------------
    // Literals
    case eLIT_INTEGER :
      fprintf( fp, "%*c(LITERAL %s %d)\n",
        indent, ' ', _exprKindStr[ e->kind ], e->litInteger );

      break;

    case eLIT_REAL :
      fprintf( fp, "%*c(LITERAL %s %.16e)\n",
        indent, ' ', _exprKindStr[ e->kind ], e->litReal );

      break;

    //--------------------------------------
    // Don't you hate it when something like this happens?
    default :
      fprintf( stderr, "Unknown expression kind %d.\n", e->kind );
      _dumpExprInternal( e, indent, fp );

      break;
  }
}

void dumpExpr( Expr *e )
{
  _dumpExprInternal( e, 1, stdout );
}
//----------------------------------------------------------------
// Evaluate an Expr node, including any hierarchical nodes.
Expr *evalExpr( Expr *e )
{
  switch ( e->kind ) {
    //--------------------------------------
    // Binary operators
    case eBOP_EXPONENT : 		// ADDITION TO THE EXPONENT OPERATOR
    case eBOP_ADD :
    case eBOP_DIVIDE :
    case eBOP_MULTIPLY :
    case eBOP_SUBTRACT :
    {
      Expr *left   = evalExpr( e->left );
      Expr *right  = evalExpr( e->right );
      Expr *result;

      // int == int or real == real 
      if ( left->kind == right->kind ) {
	// int == eLIT_INTEGERi else real == eLIT_REAL
        if ( left->kind == eLIT_INTEGER ) {
          result = _evalBOPIntInt( e->kind, left, right );
        } else {
          result = _evalBOPRealReal( e->kind, left, right );
        }
      } else {
        result = _evalBOPMRealMReal( e->kind, left, right );
      }

      return result;
    }

    //--------------------------------------
    // Unary operators
    case eUOP_NEGATE : {
      Expr *operand = evalExpr( e->left );
      Expr *result  = _allocExpr();

      if ( operand->kind == eLIT_INTEGER ) {
        result->litInteger = -operand->litInteger;
      } else {
        result->litReal = -operand->litReal;
      }

      return result;
    }

    case eUOP_POSITE : {
      Expr *operand = evalExpr( e->left );
      Expr *result  = _allocExpr();

      if ( operand->kind == eLIT_INTEGER ) {
        result->litInteger = +operand->litInteger;
      }else{
        result->litReal = +operand->litReal;
      }

      return result;   
    }

    //--------------------------------------
    // Literals
    case eLIT_INTEGER :
    case eLIT_REAL :
      return e;

    //--------------------------------------
    // Don't you hate it when something like this happens?
    default :
      printf( "Unknown expression kind %d.\n", e->kind );

      return _zeroIntLit;
  }
}

//----------------------------------------------------------------
// Build an integer literal Expr node with the given value.
//   Return NULL if the allocation fails.
Expr *litInteger( int value )
{
  // Get an expr struct.
  Expr *e = _allocExpr();

  // Allocation failure -- return NULL.
  if ( e == NULL ) return NULL;

  // Set the value of the literal to be what we were given.
  e->litInteger = value;

  return e;
}

Expr *litReal( double value )
{
  // Get an expr struct.
  Expr *e = _allocExpr();

  // Allocation failure -- return NULL.
  if ( e == NULL ) return NULL;

  // Set the kind of this literal to be real.
  e->kind = eLIT_REAL;

  // Set the value of the literal to be what we were given.
  e->litReal = value;

  return e;
}

//----------------------------------------------------------------
// Build a binary operator Expr node with the given left and
//   right operands.
//   Return NULL if the allocation fails.
Expr *oprBinary( ExprKind kind, Expr *left, Expr *right )
{
  Expr *e = _allocExpr();

  if ( e == NULL ) return NULL;

  e->kind  = kind;

  e->left  = left;
  e->right = right;

  return e;
}

// Build a unary operator Expr node with the given operand.
//   Return NULL if the allocation fails.
Expr *oprUnary( ExprKind kind, Expr *operand )
{
  Expr *e = _allocExpr();

  if ( e == NULL ) return NULL;

  e->kind  = kind;

  e->left  = operand;

  return e;
}

//----------------------------------------------------------------
// Evaluate BOP, both sides integer.
static Expr *_evalBOPIntInt( ExprKind opr, Expr *left, Expr *right )
{
  int   iLeft  = left->litInteger;
  int   iRight = right->litInteger;
  Expr *result = _allocExpr();

  switch ( opr ) {
    case eBOP_EXPONENT :
      result->litInteger = 1;	    
      int i = 0;
      // iRight is the amount we want to multiply iLeft by
      for (i = iRight; i > 0; i--)
        result->litInteger *= iLeft;
      break;
    
    case eBOP_ADD :
      result->litInteger = iLeft + iRight;
      break;

    case eBOP_DIVIDE :
      if ( iRight == 0 ) {
        printf( "Attempt to compute %d/0.\n", iLeft );

        // Well, we don't want to just crash out, so return some
        //   kind of useful value:  +/- "infinity" if the
        //   numerator isn't zero also.  On 0 / 0, return 0.
        if ( iLeft == 0 ) {
          result = _zeroIntLit;

        } else {
          result->litInteger = iLeft > 0 ? INT_MAX : INT_MIN;
        }
      } else {
        result->litInteger = iLeft / iRight;
      }

      break;

    case eBOP_MULTIPLY :
      result->litInteger = iLeft * iRight; break;

    case eBOP_SUBTRACT :
      result->litInteger = iLeft - iRight; break;

    default :
      // How is this even possible?
      printf( "evalBOPIntInt: Unknown expression kind %d.\n", opr );
      break;
  }

  return result;
}

// Evaluate BOP, both sides real.
static Expr *_evalBOPRealReal( ExprKind opr, Expr *left, Expr *right )
{
  double rLeft  = left->litReal;
  double rRight = right->litReal;
  Expr *result  = _allocExpr();

  result->kind = eLIT_REAL;

  switch ( opr ) {
    case eBOP_ADD :
      result->litReal = rLeft + rRight; break;

    case eBOP_DIVIDE :
      if ( rRight == 0.0 ) {
        printf( "Attempt to compute %g/0.\n", rLeft );

        // Well, we don't want to just crash out, so return some
        //   kind of useful value:  +/- "infinity" if the
        //   numerator isn't zero also.  On 0 / 0, return 0.
        if ( rLeft == 0.0 ) {
          result = _zeroRealLit;

        } else {
          result->litReal = rLeft > 0.0 ? INFINITY : -INFINITY;
        }
      } else {
        result->litReal = rLeft / rRight;
      }

      break;

    case eBOP_MULTIPLY :
      result->litReal = rLeft * rRight; break;

    case eBOP_SUBTRACT :
      result->litReal = rLeft - rRight; break;

    case eBOP_EXPONENT :
      result->litReal = pow(rLeft, rRight); break;

    default :
      // How is this even possible?
      printf( "_evalBOPRealReal: Unknown expression kind %d.\n", opr );
      break;
  }

  return result;
}

// Evaluate BOP, sides differ in type, which means the integer
//  side will be forced to real.
static Expr *_evalBOPMRealMReal( ExprKind opr, Expr *left, Expr *right )
{
#define ENSURE_REAL(e) ( (e)->kind == eLIT_REAL ? (e)->litReal : (double) (e)->litInteger )

  double rLeft  = ENSURE_REAL( left );
  double rRight = ENSURE_REAL( right );
  Expr *result  = _allocExpr();

  result->kind = eLIT_REAL;

  switch ( opr ) {
    case eBOP_ADD :
      result->litReal = rLeft + rRight; break;

    case eBOP_DIVIDE :
      if ( rRight == 0.0 ) {
        printf( "Attempt to compute %g/0.\n", rLeft );

        // Well, we don't want to just crash out, so return some
        //   kind of useful value:  +/- "infinity" if the
        //   numerator isn't zero also.  On 0 / 0, return 0.
        if ( rLeft == 0.0 ) {
          result = _zeroRealLit;

        } else {
          result->litReal = rLeft > 0 ? INFINITY : -INFINITY;
        }
      } else {
        result->litReal = rLeft / rRight;
      }

      break;

    case eBOP_MULTIPLY :
      result->litReal = rLeft * rRight; break;

    case eBOP_EXPONENT :
      result->litReal = pow(rLeft, rRight); break;

    case eBOP_SUBTRACT :
      result->litReal = rLeft - rRight; break;

    default :
      // How is this even possible?
      printf( "_evalBOPMRealMReal: Unknown expression kind %d.\n", opr );
      break;
  }

  return result;
}
//----------------------------------------------------------------
