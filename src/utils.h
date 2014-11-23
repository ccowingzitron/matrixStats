#include <Rinternals.h>

#define R_TYPE_LGL  1 /* 0b0001 */
#define R_TYPE_INT  2 /* 0b0010 */
#define R_TYPE_REAL 4 /* 0b0100 */

inline void assertArgMatrix(SEXP x, SEXP dim, int type) {
  double nrow, ncol;

  /* Argument 'x': */
  if (isMatrix(x)) {
  } else if (isVector(x)) {
  } else {
    error("Argument 'x' must be a matrix or a vector.");
  }
  switch (TYPEOF(x)) {
    case LGLSXP:
      if (!(type & R_TYPE_LGL))
        error("Argument 'x' cannot be logical.");
      break;

    case INTSXP:
      if (!(type & R_TYPE_INT))
        error("Argument 'x' cannot be integer.");
      break;

    case REALSXP:
      if (!(type & R_TYPE_REAL))
        error("Argument 'x' cannot be numeric.");
      break;
  } /* switch */

  /* Argument 'dim': */
  if (!isVector(dim) || xlength(dim) != 2 || !isInteger(dim)) {
    error("Argument 'dim' must be an integer vector of length two.");
  }
  nrow = (double)INTEGER(dim)[0];
  ncol = (double)INTEGER(dim)[1];
  if (nrow * ncol != (double) xlength(x)) {
    error("Argument 'dim' does not match length of argument 'x': %g * %g != %g", nrow, ncol, (double)xlength(x));
  }
} /* assertArgMatrix() */ 



inline int asLogicalNoNA(SEXP x, char *label) {
  int value;

  if (!isLogical(x))
    error("Argument '%s' must be a logical.", label);
  if (length(x) != 1)
    error("Argument '%s' must be a single value.", label);
  value = asLogical(x);
  if (value != TRUE && value != FALSE)
    error("Argument '%s' must be either TRUE or FALSE.", label); 
  
  return value;
} /* asLogicalNoNA() */

