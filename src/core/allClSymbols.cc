/*
    File: allClSymbols.cc
*/

/*
Copyright (c) 2014, Christian E. Schafmeister

CLASP is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

See directory 'clasp/licenses' for full details.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
/* -^- */
#include <string>
#include <map>
#include <clasp/core/foundation.h>
#include <clasp/core/package.h>
#include <clasp/core/array.h>
#include <clasp/core/allClSymbols.h>

#ifdef DEFINE_CL_SYMBOLS

namespace core {

map<string, int> globalAllClSymbols;
set<string> globalMissingClSymbols;

void throwIfNotValidClSymbol(const string &name) {
  map<string, int>::iterator it = globalAllClSymbols.find(name);
  if (it == globalAllClSymbols.end()) {
    SIMPLE_ERROR(BF("They symbol %s is being exported from COMMON-LISP but it is not one of the canonical CL symbols") % name);
  }
  ++it->second;
}

CL_LAMBDA()
CL_DECLARE();
CL_DOCSTRING(R"dx(calculateMissingCommonLispSymbols)dx")
CL_DEFUN T_sp core__calculate_missing_common_lisp_symbols() {
  Package_sp commonLispPackage = _lisp->commonLispPackage();
  List_sp missing = nil<T_O>();
  for (auto it : globalAllClSymbols) {
    T_mv sym = commonLispPackage->findSymbol(it.first);
    T_sp found = sym.valueGet_(1);
    if (found.nilp()) {
      missing = Cons_O::create(SimpleBaseString_O::make(it.first), missing);
    }
  }
  return missing;
}

void initializeAllClSymbols(Package_sp commonLispPkg) {
#define AddClSymbol(name)                        \
  {                                              \
    Symbol_sp sym = commonLispPkg->intern(SimpleBaseString_O::make(name)); \
    commonLispPkg->_export2(sym);                \
  }
  AddClSymbol("&ALLOW-OTHER-KEYS");
  AddClSymbol("&AUX");
  AddClSymbol("&BODY");
  AddClSymbol("&ENVIRONMENT");
  AddClSymbol("&KEY");
  AddClSymbol("&OPTIONAL");
  AddClSymbol("&REST");
  AddClSymbol("&WHOLE");
  AddClSymbol("*");
  AddClSymbol("**");
  AddClSymbol("***");
  AddClSymbol("*BREAK-ON-SIGNALS*");
  AddClSymbol("*COMPILE-FILE-PATHNAME*");
  AddClSymbol("*COMPILE-FILE-TRUENAME*");
  AddClSymbol("*COMPILE-PRINT*");
  AddClSymbol("*COMPILE-VERBOSE*");
  AddClSymbol("*DEBUG-IO*");
  AddClSymbol("*DEBUGGER-HOOK*");
  AddClSymbol("*DEFAULT-PATHNAME-DEFAULTS*");
  AddClSymbol("*ERROR-OUTPUT*");
  AddClSymbol("*FEATURES*");
  AddClSymbol("*GENSYM-COUNTER*");
  AddClSymbol("*LOAD-PATHNAME*");
  AddClSymbol("*LOAD-PRINT*");
  AddClSymbol("*LOAD-TRUENAME*");
  AddClSymbol("*LOAD-VERBOSE*");
  AddClSymbol("*MACROEXPAND-HOOK*");
  AddClSymbol("*MODULES*");
  AddClSymbol("*PACKAGE*");
  AddClSymbol("*PRINT-ARRAY*");
  AddClSymbol("*PRINT-BASE*");
  AddClSymbol("*PRINT-CASE*");
  AddClSymbol("*PRINT-CIRCLE*");
  AddClSymbol("*PRINT-ESCAPE*");
  AddClSymbol("*PRINT-GENSYM*");
  AddClSymbol("*PRINT-LENGTH*");
  AddClSymbol("*PRINT-LEVEL*");
  AddClSymbol("*PRINT-LINES*");
  AddClSymbol("*PRINT-MISER-WIDTH*");
  AddClSymbol("*PRINT-PPRINT-DISPATCH*");
  AddClSymbol("*PRINT-PRETTY*");
  AddClSymbol("*PRINT-RADIX*");
  AddClSymbol("*PRINT-READABLY*");
  AddClSymbol("*PRINT-RIGHT-MARGIN*");
  AddClSymbol("*QUERY-IO*");
  AddClSymbol("*RANDOM-STATE*");
  AddClSymbol("*READ-BASE*");
  AddClSymbol("*READ-DEFAULT-FLOAT-FORMAT*");
  AddClSymbol("*READ-EVAL*");
  AddClSymbol("*READ-SUPPRESS*");
  AddClSymbol("*READTABLE*");
  AddClSymbol("*STANDARD-INPUT*");
  AddClSymbol("*STANDARD-OUTPUT*");
  AddClSymbol("*TERMINAL-IO*");
  AddClSymbol("*TRACE-OUTPUT*");
  AddClSymbol("+");
  AddClSymbol("++");
  AddClSymbol("+++");
  AddClSymbol("-");
  AddClSymbol("/");
  AddClSymbol("//");
  AddClSymbol("///");
  AddClSymbol("/=");
  AddClSymbol("1+");
  AddClSymbol("1-");
  AddClSymbol("<");
  AddClSymbol("<=");
  AddClSymbol("=");
  AddClSymbol(">");
  AddClSymbol(">=");
  AddClSymbol("ABORT");
  AddClSymbol("ABS");
  AddClSymbol("ACONS");
  AddClSymbol("ACOS");
  AddClSymbol("ACOSH");
  AddClSymbol("ADD-METHOD");
  AddClSymbol("ADJOIN");
  AddClSymbol("ADJUST-ARRAY");
  AddClSymbol("ADJUSTABLE-ARRAY-P");
  AddClSymbol("ALLOCATE-INSTANCE");
  AddClSymbol("ALPHA-CHAR-P");
  AddClSymbol("ALPHANUMERICP");
  AddClSymbol("AND");
  AddClSymbol("APPEND");
  AddClSymbol("APPLY");
  AddClSymbol("APROPOS");
  AddClSymbol("APROPOS-LIST");
  AddClSymbol("AREF");
  AddClSymbol("ARITHMETIC-ERROR");
  AddClSymbol("ARITHMETIC-ERROR-OPERANDS");
  AddClSymbol("ARITHMETIC-ERROR-OPERATION");
  AddClSymbol("ARRAY");
  AddClSymbol("ARRAY-DIMENSION");
  AddClSymbol("ARRAY-DIMENSION-LIMIT");
  AddClSymbol("ARRAY-DIMENSIONS");
  AddClSymbol("ARRAY-DISPLACEMENT");
  AddClSymbol("ARRAY-ELEMENT-TYPE");
  AddClSymbol("ARRAY-HAS-FILL-POINTER-P");
  AddClSymbol("ARRAY-IN-BOUNDS-P");
  AddClSymbol("ARRAY-RANK");
  AddClSymbol("ARRAY-RANK-LIMIT");
  AddClSymbol("ARRAY-ROW-MAJOR-INDEX");
  AddClSymbol("ARRAY-TOTAL-SIZE");
  AddClSymbol("ARRAY-TOTAL-SIZE-LIMIT");
  AddClSymbol("ARRAYP");
  AddClSymbol("ASH");
  AddClSymbol("ASIN");
  AddClSymbol("ASINH");
  AddClSymbol("ASSERT");
  AddClSymbol("ASSOC");
  AddClSymbol("ASSOC-IF");
  AddClSymbol("ASSOC-IF-NOT");
  AddClSymbol("ATAN");
  AddClSymbol("ATANH");
  AddClSymbol("ATOM");
  AddClSymbol("BASE-CHAR");
  AddClSymbol("BASE-STRING");
  AddClSymbol("BIGNUM");
  AddClSymbol("BIT");
  AddClSymbol("BIT-AND");
  AddClSymbol("BIT-ANDC1");
  AddClSymbol("BIT-ANDC2");
  AddClSymbol("BIT-EQV");
  AddClSymbol("BIT-IOR");
  AddClSymbol("BIT-NAND");
  AddClSymbol("BIT-NOR");
  AddClSymbol("BIT-NOT");
  AddClSymbol("BIT-ORC1");
  AddClSymbol("BIT-ORC2");
  AddClSymbol("BIT-VECTOR");
  AddClSymbol("BIT-VECTOR-P");
  AddClSymbol("BIT-XOR");
  AddClSymbol("BLOCK");
  AddClSymbol("BOOLE");
  AddClSymbol("BOOLE-1");
  AddClSymbol("BOOLE-2");
  AddClSymbol("BOOLE-AND");
  AddClSymbol("BOOLE-ANDC1");
  AddClSymbol("BOOLE-ANDC2");
  AddClSymbol("BOOLE-C1");
  AddClSymbol("BOOLE-C2");
  AddClSymbol("BOOLE-CLR");
  AddClSymbol("BOOLE-EQV");
  AddClSymbol("BOOLE-IOR");
  AddClSymbol("BOOLE-NAND");
  AddClSymbol("BOOLE-NOR");
  AddClSymbol("BOOLE-ORC1");
  AddClSymbol("BOOLE-ORC2");
  AddClSymbol("BOOLE-SET");
  AddClSymbol("BOOLE-XOR");
  AddClSymbol("BOOLEAN");
  AddClSymbol("BOTH-CASE-P");
  AddClSymbol("BOUNDP");
  AddClSymbol("BREAK");
  AddClSymbol("BROADCAST-STREAM");
  AddClSymbol("BROADCAST-STREAM-STREAMS");
  AddClSymbol("BUILT-IN-CLASS");
  AddClSymbol("BUTLAST");
  AddClSymbol("BYTE");
  AddClSymbol("BYTE-POSITION");
  AddClSymbol("BYTE-SIZE");
  AddClSymbol("CAAAAR");
  AddClSymbol("CAAADR");
  AddClSymbol("CAAAR");
  AddClSymbol("CAADAR");
  AddClSymbol("CAADDR");
  AddClSymbol("CAADR");
  AddClSymbol("CAAR");
  AddClSymbol("CADAAR");
  AddClSymbol("CADADR");
  AddClSymbol("CADAR");
  AddClSymbol("CADDAR");
  AddClSymbol("CADDDR");
  AddClSymbol("CADDR");
  AddClSymbol("CADR");
  AddClSymbol("CALL-ARGUMENTS-LIMIT");
  AddClSymbol("CALL-METHOD");
  AddClSymbol("CALL-NEXT-METHOD");
  AddClSymbol("CAR");
  AddClSymbol("CASE");
  AddClSymbol("CATCH");
  AddClSymbol("CCASE");
  AddClSymbol("CDAAAR");
  AddClSymbol("CDAADR");
  AddClSymbol("CDAAR");
  AddClSymbol("CDADAR");
  AddClSymbol("CDADDR");
  AddClSymbol("CDADR");
  AddClSymbol("CDAR");
  AddClSymbol("CDDAAR");
  AddClSymbol("CDDADR");
  AddClSymbol("CDDAR");
  AddClSymbol("CDDDAR");
  AddClSymbol("CDDDDR");
  AddClSymbol("CDDDR");
  AddClSymbol("CDDR");
  AddClSymbol("CDR");
  AddClSymbol("CEILING");
  AddClSymbol("CELL-ERROR");
  AddClSymbol("CELL-ERROR-NAME");
  AddClSymbol("CERROR");
  AddClSymbol("CHANGE-CLASS");
  AddClSymbol("CHAR");
  AddClSymbol("CHAR-CODE");
  AddClSymbol("CHAR-CODE-LIMIT");
  AddClSymbol("CHAR-DOWNCASE");
  AddClSymbol("CHAR-EQUAL");
  AddClSymbol("CHAR-GREATERP");
  AddClSymbol("CHAR-INT");
  AddClSymbol("CHAR-LESSP");
  AddClSymbol("CHAR-NAME");
  AddClSymbol("CHAR-NOT-EQUAL");
  AddClSymbol("CHAR-NOT-GREATERP");
  AddClSymbol("CHAR-NOT-LESSP");
  AddClSymbol("CHAR-UPCASE");
  AddClSymbol("CHAR/=");
  AddClSymbol("CHAR<");
  AddClSymbol("CHAR<=");
  AddClSymbol("CHAR=");
  AddClSymbol("CHAR>");
  AddClSymbol("CHAR>=");
  AddClSymbol("CHARACTER");
  AddClSymbol("CHARACTERP");
  AddClSymbol("CHECK-TYPE");
  AddClSymbol("CIS");
  AddClSymbol("CLASS");
  AddClSymbol("CLASS-NAME");
  AddClSymbol("CLASS-OF");
  AddClSymbol("CLEAR-INPUT");
  AddClSymbol("CLEAR-OUTPUT");
  AddClSymbol("CLOSE");
  AddClSymbol("CLRHASH");
  AddClSymbol("CODE-CHAR");
  AddClSymbol("COERCE");
  AddClSymbol("COMPILATION-SPEED");
  AddClSymbol("COMPILE");
  AddClSymbol("COMPILE-FILE");
  AddClSymbol("COMPILE-FILE-PATHNAME");
  AddClSymbol("COMPILED-FUNCTION");
  AddClSymbol("COMPILED-FUNCTION-P");
  AddClSymbol("COMPILER-MACRO");
  AddClSymbol("COMPILER-MACRO-FUNCTION");
  AddClSymbol("COMPLEMENT");
  AddClSymbol("COMPLEX");
  AddClSymbol("COMPLEXP");
  AddClSymbol("COMPUTE-APPLICABLE-METHODS");
  AddClSymbol("COMPUTE-RESTARTS");
  AddClSymbol("CONCATENATE");
  AddClSymbol("CONCATENATED-STREAM");
  AddClSymbol("CONCATENATED-STREAM-STREAMS");
  AddClSymbol("COND");
  AddClSymbol("CONDITION");
  AddClSymbol("CONJUGATE");
  AddClSymbol("CONS");
  AddClSymbol("CONSP");
  AddClSymbol("CONSTANTLY");
  AddClSymbol("CONSTANTP");
  AddClSymbol("CONTINUE");
  AddClSymbol("CONTROL-ERROR");
  AddClSymbol("COPY-ALIST");
  AddClSymbol("COPY-LIST");
  AddClSymbol("COPY-PPRINT-DISPATCH");
  AddClSymbol("COPY-READTABLE");
  AddClSymbol("COPY-SEQ");
  AddClSymbol("COPY-STRUCTURE");
  AddClSymbol("COPY-SYMBOL");
  AddClSymbol("COPY-TREE");
  AddClSymbol("COS");
  AddClSymbol("COSH");
  AddClSymbol("COUNT");
  AddClSymbol("COUNT-IF");
  AddClSymbol("COUNT-IF-NOT");
  AddClSymbol("CTYPECASE");
  AddClSymbol("DEBUG");
  AddClSymbol("DECF");
  AddClSymbol("DECLAIM");
  AddClSymbol("DECLARATION");
  AddClSymbol("DECLARE");
  AddClSymbol("DECODE-FLOAT");
  AddClSymbol("DECODE-UNIVERSAL-TIME");
  AddClSymbol("DEFCLASS");
  AddClSymbol("DEFCONSTANT");
  AddClSymbol("DEFGENERIC");
  AddClSymbol("DEFINE-COMPILER-MACRO");
  AddClSymbol("DEFINE-CONDITION");
  AddClSymbol("DEFINE-METHOD-COMBINATION");
  AddClSymbol("DEFINE-MODIFY-MACRO");
  AddClSymbol("DEFINE-SETF-EXPANDER");
  AddClSymbol("DEFINE-SYMBOL-MACRO");
  AddClSymbol("DEFMACRO");
  AddClSymbol("DEFMETHOD");
  AddClSymbol("DEFPACKAGE");
  AddClSymbol("DEFPARAMETER");
  AddClSymbol("DEFSETF");
  AddClSymbol("DEFSTRUCT");
  AddClSymbol("DEFTYPE");
  AddClSymbol("DEFUN");
  AddClSymbol("DEFVAR");
  AddClSymbol("DELETE");
  AddClSymbol("DELETE-DUPLICATES");
  AddClSymbol("DELETE-FILE");
  AddClSymbol("DELETE-IF");
  AddClSymbol("DELETE-IF-NOT");
  AddClSymbol("DELETE-PACKAGE");
  AddClSymbol("DENOMINATOR");
  AddClSymbol("DEPOSIT-FIELD");
  AddClSymbol("DESCRIBE");
  AddClSymbol("DESCRIBE-OBJECT");
  AddClSymbol("DESTRUCTURING-BIND");
  AddClSymbol("DIGIT-CHAR");
  AddClSymbol("DIGIT-CHAR-P");
  AddClSymbol("DIRECTORY");
  AddClSymbol("DIRECTORY-NAMESTRING");
  AddClSymbol("DISASSEMBLE");
  AddClSymbol("DIVISION-BY-ZERO");
  AddClSymbol("DO");
  AddClSymbol("DO*");
  AddClSymbol("DO-ALL-SYMBOLS");
  AddClSymbol("DO-EXTERNAL-SYMBOLS");
  AddClSymbol("DO-SYMBOLS");
  AddClSymbol("DOCUMENTATION");
  AddClSymbol("DOLIST");
  AddClSymbol("DOTIMES");
  AddClSymbol("DOUBLE-FLOAT");
  AddClSymbol("DOUBLE-FLOAT-EPSILON");
  AddClSymbol("DOUBLE-FLOAT-NEGATIVE-EPSILON");
  AddClSymbol("DPB");
  AddClSymbol("DRIBBLE");
  AddClSymbol("DYNAMIC-EXTENT");
  AddClSymbol("ECASE");
  AddClSymbol("ECHO-STREAM");
  AddClSymbol("ECHO-STREAM-INPUT-STREAM");
  AddClSymbol("ECHO-STREAM-OUTPUT-STREAM");
  AddClSymbol("ED");
  AddClSymbol("EIGHTH");
  AddClSymbol("ELT");
  AddClSymbol("ENCODE-UNIVERSAL-TIME");
  AddClSymbol("END-OF-FILE");
  AddClSymbol("ENDP");
  AddClSymbol("ENOUGH-NAMESTRING");
  AddClSymbol("ENSURE-DIRECTORIES-EXIST");
  AddClSymbol("ENSURE-GENERIC-FUNCTION");
  AddClSymbol("EQ");
  AddClSymbol("EQL");
  AddClSymbol("EQUAL");
  AddClSymbol("EQUALP");
  AddClSymbol("ERROR");
  AddClSymbol("ETYPECASE");
  AddClSymbol("EVAL");
  AddClSymbol("EVAL-WHEN");
  AddClSymbol("EVENP");
  AddClSymbol("EVERY");
  AddClSymbol("EXP");
  AddClSymbol("EXPORT");
  AddClSymbol("EXPT");
  AddClSymbol("EXTENDED-CHAR");
  AddClSymbol("FBOUNDP");
  AddClSymbol("FCEILING");
  AddClSymbol("FDEFINITION");
  AddClSymbol("FFLOOR");
  AddClSymbol("FIFTH");
  AddClSymbol("FILE-AUTHOR");
  AddClSymbol("FILE-ERROR");
  AddClSymbol("FILE-ERROR-PATHNAME");
  AddClSymbol("FILE-LENGTH");
  AddClSymbol("FILE-NAMESTRING");
  AddClSymbol("FILE-POSITION");
  AddClSymbol("FILE-STREAM");
  AddClSymbol("FILE-STRING-LENGTH");
  AddClSymbol("FILE-WRITE-DATE");
  AddClSymbol("FILL");
  AddClSymbol("FILL-POINTER");
  AddClSymbol("FIND");
  AddClSymbol("FIND-ALL-SYMBOLS");
  AddClSymbol("FIND-CLASS");
  AddClSymbol("FIND-IF");
  AddClSymbol("FIND-IF-NOT");
  AddClSymbol("FIND-METHOD");
  AddClSymbol("FIND-PACKAGE");
  AddClSymbol("FIND-RESTART");
  AddClSymbol("FIND-SYMBOL");
  AddClSymbol("FINISH-OUTPUT");
  AddClSymbol("FIRST");
  AddClSymbol("FIXNUM");
  AddClSymbol("FLET");
  AddClSymbol("FLOAT");
  AddClSymbol("FLOAT-DIGITS");
  AddClSymbol("FLOAT-PRECISION");
  AddClSymbol("FLOAT-RADIX");
  AddClSymbol("FLOAT-SIGN");
  AddClSymbol("FLOATING-POINT-INEXACT");
  AddClSymbol("FLOATING-POINT-INVALID-OPERATION");
  AddClSymbol("FLOATING-POINT-OVERFLOW");
  AddClSymbol("FLOATING-POINT-UNDERFLOW");
  AddClSymbol("FLOATP");
  AddClSymbol("FLOOR");
  AddClSymbol("FMAKUNBOUND");
  AddClSymbol("FORCE-OUTPUT");
  AddClSymbol("FORMAT");
  AddClSymbol("FORMATTER");
  AddClSymbol("FOURTH");
  AddClSymbol("FRESH-LINE");
  AddClSymbol("FROUND");
  AddClSymbol("FTRUNCATE");
  AddClSymbol("FTYPE");
  AddClSymbol("FUNCALL");
  AddClSymbol("FUNCTION");
  AddClSymbol("FUNCTION-KEYWORDS");
  AddClSymbol("FUNCTION-LAMBDA-EXPRESSION");
  AddClSymbol("FUNCTIONP");
  AddClSymbol("GCD");
  AddClSymbol("GENERIC-FUNCTION");
  AddClSymbol("GENSYM");
  AddClSymbol("GENTEMP");
  AddClSymbol("GET");
  AddClSymbol("GET-DECODED-TIME");
  AddClSymbol("GET-DISPATCH-MACRO-CHARACTER");
  AddClSymbol("GET-INTERNAL-REAL-TIME");
  AddClSymbol("GET-INTERNAL-RUN-TIME");
  AddClSymbol("GET-MACRO-CHARACTER");
  AddClSymbol("GET-OUTPUT-STREAM-STRING");
  AddClSymbol("GET-PROPERTIES");
  AddClSymbol("GET-SETF-EXPANSION");
  AddClSymbol("GET-UNIVERSAL-TIME");
  AddClSymbol("GETF");
  AddClSymbol("GETHASH");
  AddClSymbol("GO");
  AddClSymbol("GRAPHIC-CHAR-P");
  AddClSymbol("HANDLER-BIND");
  AddClSymbol("HANDLER-CASE");
  AddClSymbol("HASH-TABLE");
  AddClSymbol("HASH-TABLE-COUNT");
  AddClSymbol("HASH-TABLE-P");
  AddClSymbol("HASH-TABLE-REHASH-SIZE");
  AddClSymbol("HASH-TABLE-REHASH-THRESHOLD");
  AddClSymbol("HASH-TABLE-SIZE");
  AddClSymbol("HASH-TABLE-TEST");
  AddClSymbol("HOST-NAMESTRING");
  AddClSymbol("IDENTITY");
  AddClSymbol("IF");
  AddClSymbol("IGNORABLE");
  AddClSymbol("IGNORE");
  AddClSymbol("IGNORE-ERRORS");
  AddClSymbol("IMAGPART");
  AddClSymbol("IMPORT");
  AddClSymbol("IN-PACKAGE");
  AddClSymbol("INCF");
  AddClSymbol("INITIALIZE-INSTANCE");
  AddClSymbol("INLINE");
  AddClSymbol("INPUT-STREAM-P");
  AddClSymbol("INSPECT");
  AddClSymbol("INTEGER");
  AddClSymbol("INTEGER-DECODE-FLOAT");
  AddClSymbol("INTEGER-LENGTH");
  AddClSymbol("INTEGERP");
  AddClSymbol("INTERACTIVE-STREAM-P");
  AddClSymbol("INTERN");
  AddClSymbol("INTERNAL-TIME-UNITS-PER-SECOND");
  AddClSymbol("INTERSECTION");
  AddClSymbol("INVALID-METHOD-ERROR");
  AddClSymbol("INVOKE-DEBUGGER");
  AddClSymbol("INVOKE-RESTART");
  AddClSymbol("INVOKE-RESTART-INTERACTIVELY");
  AddClSymbol("ISQRT");
  AddClSymbol("KEYWORD");
  AddClSymbol("KEYWORDP");
  AddClSymbol("LABELS");
  AddClSymbol("LAMBDA");
  AddClSymbol("LAMBDA-LIST-KEYWORDS");
  AddClSymbol("LAMBDA-PARAMETERS-LIMIT");
  AddClSymbol("LAST");
  AddClSymbol("LCM");
  AddClSymbol("LDB");
  AddClSymbol("LDB-TEST");
  AddClSymbol("LDIFF");
  AddClSymbol("LEAST-NEGATIVE-DOUBLE-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-LONG-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-NORMALIZED-DOUBLE-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-NORMALIZED-LONG-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-NORMALIZED-SHORT-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-NORMALIZED-SINGLE-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-SHORT-FLOAT");
  AddClSymbol("LEAST-NEGATIVE-SINGLE-FLOAT");
  AddClSymbol("LEAST-POSITIVE-DOUBLE-FLOAT");
  AddClSymbol("LEAST-POSITIVE-LONG-FLOAT");
  AddClSymbol("LEAST-POSITIVE-NORMALIZED-DOUBLE-FLOAT");
  AddClSymbol("LEAST-POSITIVE-NORMALIZED-LONG-FLOAT");
  AddClSymbol("LEAST-POSITIVE-NORMALIZED-SHORT-FLOAT");
  AddClSymbol("LEAST-POSITIVE-NORMALIZED-SINGLE-FLOAT");
  AddClSymbol("LEAST-POSITIVE-SHORT-FLOAT");
  AddClSymbol("LEAST-POSITIVE-SINGLE-FLOAT");
  AddClSymbol("LENGTH");
  AddClSymbol("LET");
  AddClSymbol("LET*");
  AddClSymbol("LISP-IMPLEMENTATION-TYPE");
  AddClSymbol("LISP-IMPLEMENTATION-VERSION");
  AddClSymbol("LIST");
  AddClSymbol("LIST*");
  AddClSymbol("LIST-ALL-PACKAGES");
  AddClSymbol("LIST-LENGTH");
  AddClSymbol("LISTEN");
  AddClSymbol("LISTP");
  AddClSymbol("LOAD");
  AddClSymbol("LOAD-LOGICAL-PATHNAME-TRANSLATIONS");
  AddClSymbol("LOAD-TIME-VALUE");
  AddClSymbol("LOCALLY");
  AddClSymbol("LOG");
  AddClSymbol("LOGAND");
  AddClSymbol("LOGANDC1");
  AddClSymbol("LOGANDC2");
  AddClSymbol("LOGBITP");
  AddClSymbol("LOGCOUNT");
  AddClSymbol("LOGEQV");
  AddClSymbol("LOGICAL-PATHNAME");
  AddClSymbol("LOGICAL-PATHNAME-TRANSLATIONS");
  AddClSymbol("LOGIOR");
  AddClSymbol("LOGNAND");
  AddClSymbol("LOGNOR");
  AddClSymbol("LOGNOT");
  AddClSymbol("LOGORC1");
  AddClSymbol("LOGORC2");
  AddClSymbol("LOGTEST");
  AddClSymbol("LOGXOR");
  AddClSymbol("LONG-FLOAT");
  AddClSymbol("LONG-FLOAT-EPSILON");
  AddClSymbol("LONG-FLOAT-NEGATIVE-EPSILON");
  AddClSymbol("LONG-SITE-NAME");
  AddClSymbol("LOOP");
  AddClSymbol("LOOP-FINISH");
  AddClSymbol("LOWER-CASE-P");
  AddClSymbol("MACHINE-INSTANCE");
  AddClSymbol("MACHINE-TYPE");
  AddClSymbol("MACHINE-VERSION");
  AddClSymbol("MACRO-FUNCTION");
  AddClSymbol("MACROEXPAND");
  AddClSymbol("MACROEXPAND-1");
  AddClSymbol("MACROLET");
  AddClSymbol("MAKE-ARRAY");
  AddClSymbol("MAKE-BROADCAST-STREAM");
  AddClSymbol("MAKE-CONCATENATED-STREAM");
  AddClSymbol("MAKE-CONDITION");
  AddClSymbol("MAKE-DISPATCH-MACRO-CHARACTER");
  AddClSymbol("MAKE-ECHO-STREAM");
  AddClSymbol("MAKE-HASH-TABLE");
  AddClSymbol("MAKE-INSTANCE");
  AddClSymbol("MAKE-INSTANCES-OBSOLETE");
  AddClSymbol("MAKE-LIST");
  AddClSymbol("MAKE-LOAD-FORM");
  AddClSymbol("MAKE-LOAD-FORM-SAVING-SLOTS");
  AddClSymbol("MAKE-METHOD");
  AddClSymbol("MAKE-PACKAGE");
  AddClSymbol("MAKE-PATHNAME");
  AddClSymbol("MAKE-RANDOM-STATE");
  AddClSymbol("MAKE-SEQUENCE");
  AddClSymbol("MAKE-STRING");
  AddClSymbol("MAKE-STRING-INPUT-STREAM");
  AddClSymbol("MAKE-STRING-OUTPUT-STREAM");
  AddClSymbol("MAKE-SYMBOL");
  AddClSymbol("MAKE-SYNONYM-STREAM");
  AddClSymbol("MAKE-TWO-WAY-STREAM");
  AddClSymbol("MAKUNBOUND");
  AddClSymbol("MAP");
  AddClSymbol("MAP-INTO");
  AddClSymbol("MAPC");
  AddClSymbol("MAPCAN");
  AddClSymbol("MAPCAR");
  AddClSymbol("MAPCON");
  AddClSymbol("MAPHASH");
  AddClSymbol("MAPL");
  AddClSymbol("MAPLIST");
  AddClSymbol("MASK-FIELD");
  AddClSymbol("MAX");
  AddClSymbol("MEMBER");
  AddClSymbol("MEMBER-IF");
  AddClSymbol("MEMBER-IF-NOT");
  AddClSymbol("MERGE");
  AddClSymbol("MERGE-PATHNAMES");
  AddClSymbol("METHOD");
  AddClSymbol("METHOD-COMBINATION");
  AddClSymbol("METHOD-COMBINATION-ERROR");
  AddClSymbol("METHOD-QUALIFIERS");
  AddClSymbol("MIN");
  AddClSymbol("MINUSP");
  AddClSymbol("MISMATCH");
  AddClSymbol("MOD");
  AddClSymbol("MOST-NEGATIVE-DOUBLE-FLOAT");
  AddClSymbol("MOST-NEGATIVE-FIXNUM");
  AddClSymbol("MOST-NEGATIVE-LONG-FLOAT");
  AddClSymbol("MOST-NEGATIVE-SHORT-FLOAT");
  AddClSymbol("MOST-NEGATIVE-SINGLE-FLOAT");
  AddClSymbol("MOST-POSITIVE-DOUBLE-FLOAT");
  AddClSymbol("MOST-POSITIVE-FIXNUM");
  AddClSymbol("MOST-POSITIVE-LONG-FLOAT");
  AddClSymbol("MOST-POSITIVE-SHORT-FLOAT");
  AddClSymbol("MOST-POSITIVE-SINGLE-FLOAT");
  AddClSymbol("MUFFLE-WARNING");
  AddClSymbol("MULTIPLE-VALUE-BIND");
  AddClSymbol("MULTIPLE-VALUE-CALL");
  AddClSymbol("MULTIPLE-VALUE-LIST");
  AddClSymbol("MULTIPLE-VALUE-PROG1");
  AddClSymbol("MULTIPLE-VALUE-SETQ");
  AddClSymbol("MULTIPLE-VALUES-LIMIT");
  AddClSymbol("NAME-CHAR");
  AddClSymbol("NAMESTRING");
  AddClSymbol("NBUTLAST");
  AddClSymbol("NCONC");
  AddClSymbol("NEXT-METHOD-P");
  AddClSymbol("NIL");
  AddClSymbol("NINTERSECTION");
  AddClSymbol("NINTH");
  AddClSymbol("NO-APPLICABLE-METHOD");
  AddClSymbol("NO-NEXT-METHOD");
  AddClSymbol("NOT");
  AddClSymbol("NOTANY");
  AddClSymbol("NOTEVERY");
  AddClSymbol("NOTINLINE");
  AddClSymbol("NRECONC");
  AddClSymbol("NREVERSE");
  AddClSymbol("NSET-DIFFERENCE");
  AddClSymbol("NSET-EXCLUSIVE-OR");
  AddClSymbol("NSTRING-CAPITALIZE");
  AddClSymbol("NSTRING-DOWNCASE");
  AddClSymbol("NSTRING-UPCASE");
  AddClSymbol("NSUBLIS");
  AddClSymbol("NSUBST");
  AddClSymbol("NSUBST-IF");
  AddClSymbol("NSUBST-IF-NOT");
  AddClSymbol("NSUBSTITUTE");
  AddClSymbol("NSUBSTITUTE-IF");
  AddClSymbol("NSUBSTITUTE-IF-NOT");
  AddClSymbol("NTH");
  AddClSymbol("NTH-VALUE");
  AddClSymbol("NTHCDR");
  AddClSymbol("NULL");
  AddClSymbol("NUMBER");
  AddClSymbol("NUMBERP");
  AddClSymbol("NUMERATOR");
  AddClSymbol("NUNION");
  AddClSymbol("ODDP");
  AddClSymbol("OPEN");
  AddClSymbol("OPEN-STREAM-P");
  AddClSymbol("OPTIMIZE");
  AddClSymbol("OR");
  AddClSymbol("OTHERWISE");
  AddClSymbol("OUTPUT-STREAM-P");
  AddClSymbol("PACKAGE");
  AddClSymbol("PACKAGE-ERROR");
  AddClSymbol("PACKAGE-ERROR-PACKAGE");
  AddClSymbol("PACKAGE-NAME");
  AddClSymbol("PACKAGE-NICKNAMES");
  AddClSymbol("PACKAGE-SHADOWING-SYMBOLS");
  AddClSymbol("PACKAGE-USE-LIST");
  AddClSymbol("PACKAGE-USED-BY-LIST");
  AddClSymbol("PACKAGEP");
  AddClSymbol("PAIRLIS");
  AddClSymbol("PARSE-ERROR");
  AddClSymbol("PARSE-INTEGER");
  AddClSymbol("PARSE-NAMESTRING");
  AddClSymbol("PATHNAME");
  AddClSymbol("PATHNAME-DEVICE");
  AddClSymbol("PATHNAME-DIRECTORY");
  AddClSymbol("PATHNAME-HOST");
  AddClSymbol("PATHNAME-MATCH-P");
  AddClSymbol("PATHNAME-NAME");
  AddClSymbol("PATHNAME-TYPE");
  AddClSymbol("PATHNAME-VERSION");
  AddClSymbol("PATHNAMEP");
  AddClSymbol("PEEK-CHAR");
  AddClSymbol("PHASE");
  AddClSymbol("PI");
  AddClSymbol("PLUSP");
  AddClSymbol("POP");
  AddClSymbol("POSITION");
  AddClSymbol("POSITION-IF");
  AddClSymbol("POSITION-IF-NOT");
  AddClSymbol("PPRINT");
  AddClSymbol("PPRINT-DISPATCH");
  AddClSymbol("PPRINT-EXIT-IF-LIST-EXHAUSTED");
  AddClSymbol("PPRINT-FILL");
  AddClSymbol("PPRINT-INDENT");
  AddClSymbol("PPRINT-LINEAR");
  AddClSymbol("PPRINT-LOGICAL-BLOCK");
  AddClSymbol("PPRINT-NEWLINE");
  AddClSymbol("PPRINT-POP");
  AddClSymbol("PPRINT-TAB");
  AddClSymbol("PPRINT-TABULAR");
  AddClSymbol("PRIN1");
  AddClSymbol("PRIN1-TO-STRING");
  AddClSymbol("PRINC");
  AddClSymbol("PRINC-TO-STRING");
  AddClSymbol("PRINT");
  AddClSymbol("PRINT-NOT-READABLE");
  AddClSymbol("PRINT-NOT-READABLE-OBJECT");
  AddClSymbol("PRINT-OBJECT");
  AddClSymbol("PRINT-UNREADABLE-OBJECT");
  AddClSymbol("PROBE-FILE");
  AddClSymbol("PROCLAIM");
  AddClSymbol("PROG");
  AddClSymbol("PROG*");
  AddClSymbol("PROG1");
  AddClSymbol("PROG2");
  AddClSymbol("PROGN");
  AddClSymbol("PROGRAM-ERROR");
  AddClSymbol("PROGV");
  AddClSymbol("PROVIDE");
  AddClSymbol("PSETF");
  AddClSymbol("PSETQ");
  AddClSymbol("PUSH");
  AddClSymbol("PUSHNEW");
  AddClSymbol("QUOTE");
  AddClSymbol("RANDOM");
  AddClSymbol("RANDOM-STATE");
  AddClSymbol("RANDOM-STATE-P");
  AddClSymbol("RASSOC");
  AddClSymbol("RASSOC-IF");
  AddClSymbol("RASSOC-IF-NOT");
  AddClSymbol("RATIO");
  AddClSymbol("RATIONAL");
  AddClSymbol("RATIONALIZE");
  AddClSymbol("RATIONALP");
  AddClSymbol("READ");
  AddClSymbol("READ-BYTE");
  AddClSymbol("READ-CHAR");
  AddClSymbol("READ-CHAR-NO-HANG");
  AddClSymbol("READ-DELIMITED-LIST");
  AddClSymbol("READ-FROM-STRING");
  AddClSymbol("READ-LINE");
  AddClSymbol("READ-PRESERVING-WHITESPACE");
  AddClSymbol("READ-SEQUENCE");
  AddClSymbol("READER-ERROR");
  AddClSymbol("READTABLE");
  AddClSymbol("READTABLE-CASE");
  AddClSymbol("READTABLEP");
  AddClSymbol("REAL");
  AddClSymbol("REALP");
  AddClSymbol("REALPART");
  AddClSymbol("REDUCE");
  AddClSymbol("REINITIALIZE-INSTANCE");
  AddClSymbol("REM");
  AddClSymbol("REMF");
  AddClSymbol("REMHASH");
  AddClSymbol("REMOVE");
  AddClSymbol("REMOVE-DUPLICATES");
  AddClSymbol("REMOVE-IF");
  AddClSymbol("REMOVE-IF-NOT");
  AddClSymbol("REMOVE-METHOD");
  AddClSymbol("REMPROP");
  AddClSymbol("RENAME-FILE");
  AddClSymbol("RENAME-PACKAGE");
  AddClSymbol("REPLACE");
  AddClSymbol("REQUIRE");
  AddClSymbol("REST");
  AddClSymbol("RESTART");
  AddClSymbol("RESTART-BIND");
  AddClSymbol("RESTART-CASE");
  AddClSymbol("RESTART-NAME");
  AddClSymbol("RETURN");
  AddClSymbol("RETURN-FROM");
  AddClSymbol("REVAPPEND");
  AddClSymbol("REVERSE");
  AddClSymbol("ROOM");
  AddClSymbol("ROTATEF");
  AddClSymbol("ROUND");
  AddClSymbol("ROW-MAJOR-AREF");
  AddClSymbol("RPLACA");
  AddClSymbol("RPLACD");
  AddClSymbol("SAFETY");
  AddClSymbol("SATISFIES");
  AddClSymbol("SBIT");
  AddClSymbol("SCALE-FLOAT");
  AddClSymbol("SCHAR");
  AddClSymbol("SEARCH");
  AddClSymbol("SECOND");
  AddClSymbol("SEQUENCE");
  AddClSymbol("SERIOUS-CONDITION");
  AddClSymbol("SET");
  AddClSymbol("SET-DIFFERENCE");
  AddClSymbol("SET-DISPATCH-MACRO-CHARACTER");
  AddClSymbol("SET-EXCLUSIVE-OR");
  AddClSymbol("SET-MACRO-CHARACTER");
  AddClSymbol("SET-PPRINT-DISPATCH");
  AddClSymbol("SET-SYNTAX-FROM-CHAR");
  AddClSymbol("SETF");
  AddClSymbol("SETQ");
  AddClSymbol("SEVENTH");
  AddClSymbol("SHADOW");
  AddClSymbol("SHADOWING-IMPORT");
  AddClSymbol("SHARED-INITIALIZE");
  AddClSymbol("SHIFTF");
  AddClSymbol("SHORT-FLOAT");
  AddClSymbol("SHORT-FLOAT-EPSILON");
  AddClSymbol("SHORT-FLOAT-NEGATIVE-EPSILON");
  AddClSymbol("SHORT-SITE-NAME");
  AddClSymbol("SIGNAL");
  AddClSymbol("SIGNED-BYTE");
  AddClSymbol("SIGNUM");
  AddClSymbol("SIMPLE-ARRAY");
  AddClSymbol("SIMPLE-BASE-STRING");
  AddClSymbol("SIMPLE-BIT-VECTOR");
  AddClSymbol("SIMPLE-BIT-VECTOR-P");
  AddClSymbol("SIMPLE-CONDITION");
  AddClSymbol("SIMPLE-CONDITION-FORMAT-ARGUMENTS");
  AddClSymbol("SIMPLE-CONDITION-FORMAT-CONTROL");
  AddClSymbol("SIMPLE-ERROR");
  AddClSymbol("SIMPLE-STRING");
  AddClSymbol("SIMPLE-STRING-P");
  AddClSymbol("SIMPLE-TYPE-ERROR");
  AddClSymbol("SIMPLE-VECTOR");
  AddClSymbol("SIMPLE-VECTOR-P");
  AddClSymbol("SIMPLE-WARNING");
  AddClSymbol("SIN");
  AddClSymbol("SINGLE-FLOAT");
  AddClSymbol("SINGLE-FLOAT-EPSILON");
  AddClSymbol("SINGLE-FLOAT-NEGATIVE-EPSILON");
  AddClSymbol("SINH");
  AddClSymbol("SIXTH");
  AddClSymbol("SLEEP");
  AddClSymbol("SLOT-BOUNDP");
  AddClSymbol("SLOT-EXISTS-P");
  AddClSymbol("SLOT-MAKUNBOUND");
  AddClSymbol("SLOT-MISSING");
  AddClSymbol("SLOT-UNBOUND");
  AddClSymbol("SLOT-VALUE");
  AddClSymbol("SOFTWARE-TYPE");
  AddClSymbol("SOFTWARE-VERSION");
  AddClSymbol("SOME");
  AddClSymbol("SORT");
  AddClSymbol("SPACE");
  AddClSymbol("SPECIAL");
  AddClSymbol("SPECIAL-OPERATOR-P");
  AddClSymbol("SPEED");
  AddClSymbol("SQRT");
  AddClSymbol("STABLE-SORT");
  AddClSymbol("STANDARD");
  AddClSymbol("STANDARD-CHAR");
  AddClSymbol("STANDARD-CHAR-P");
  AddClSymbol("STANDARD-CLASS");
  AddClSymbol("STANDARD-GENERIC-FUNCTION");
  AddClSymbol("STANDARD-METHOD");
  AddClSymbol("STANDARD-OBJECT");
  AddClSymbol("STEP");
  AddClSymbol("STORAGE-CONDITION");
  AddClSymbol("STORE-VALUE");
  AddClSymbol("STREAM");
  AddClSymbol("STREAM-ELEMENT-TYPE");
  AddClSymbol("STREAM-ERROR");
  AddClSymbol("STREAM-ERROR-STREAM");
  AddClSymbol("STREAM-EXTERNAL-FORMAT");
  AddClSymbol("STREAMP");
  AddClSymbol("STRING");
  AddClSymbol("STRING-CAPITALIZE");
  AddClSymbol("STRING-DOWNCASE");
  AddClSymbol("STRING-EQUAL");
  AddClSymbol("STRING-GREATERP");
  AddClSymbol("STRING-LEFT-TRIM");
  AddClSymbol("STRING-LESSP");
  AddClSymbol("STRING-NOT-EQUAL");
  AddClSymbol("STRING-NOT-GREATERP");
  AddClSymbol("STRING-NOT-LESSP");
  AddClSymbol("STRING-RIGHT-TRIM");
  AddClSymbol("STRING-STREAM");
  AddClSymbol("STRING-TRIM");
  AddClSymbol("STRING-UPCASE");
  AddClSymbol("STRING/=");
  AddClSymbol("STRING<");
  AddClSymbol("STRING<=");
  AddClSymbol("STRING=");
  AddClSymbol("STRING>");
  AddClSymbol("STRING>=");
  AddClSymbol("STRINGP");
  AddClSymbol("STRUCTURE");
  AddClSymbol("STRUCTURE-CLASS");
  AddClSymbol("STRUCTURE-OBJECT");
  AddClSymbol("STYLE-WARNING");
  AddClSymbol("SUBLIS");
  AddClSymbol("SUBSEQ");
  AddClSymbol("SUBSETP");
  AddClSymbol("SUBST");
  AddClSymbol("SUBST-IF");
  AddClSymbol("SUBST-IF-NOT");
  AddClSymbol("SUBSTITUTE");
  AddClSymbol("SUBSTITUTE-IF");
  AddClSymbol("SUBSTITUTE-IF-NOT");
  AddClSymbol("SUBTYPEP");
  AddClSymbol("SVREF");
  AddClSymbol("SXHASH");
  AddClSymbol("SYMBOL");
  AddClSymbol("SYMBOL-FUNCTION");
  AddClSymbol("SYMBOL-MACROLET");
  AddClSymbol("SYMBOL-NAME");
  AddClSymbol("SYMBOL-PACKAGE");
  AddClSymbol("SYMBOL-PLIST");
  AddClSymbol("SYMBOL-VALUE");
  AddClSymbol("SYMBOLP");
  AddClSymbol("SYNONYM-STREAM");
  AddClSymbol("SYNONYM-STREAM-SYMBOL");
  AddClSymbol("T");
  AddClSymbol("TAGBODY");
  AddClSymbol("TAILP");
  AddClSymbol("TAN");
  AddClSymbol("TANH");
  AddClSymbol("TENTH");
  AddClSymbol("TERPRI");
  AddClSymbol("THE");
  AddClSymbol("THIRD");
  AddClSymbol("THROW");
  AddClSymbol("TIME");
  AddClSymbol("TRACE");
  AddClSymbol("TRANSLATE-LOGICAL-PATHNAME");
  AddClSymbol("TRANSLATE-PATHNAME");
  AddClSymbol("TREE-EQUAL");
  AddClSymbol("TRUENAME");
  AddClSymbol("TRUNCATE");
  AddClSymbol("TWO-WAY-STREAM");
  AddClSymbol("TWO-WAY-STREAM-INPUT-STREAM");
  AddClSymbol("TWO-WAY-STREAM-OUTPUT-STREAM");
  AddClSymbol("TYPE");
  AddClSymbol("TYPE-ERROR");
  AddClSymbol("TYPE-ERROR-DATUM");
  AddClSymbol("TYPE-ERROR-EXPECTED-TYPE");
  AddClSymbol("TYPE-OF");
  AddClSymbol("TYPECASE");
  AddClSymbol("TYPEP");
  AddClSymbol("UNBOUND-SLOT");
  AddClSymbol("UNBOUND-SLOT-INSTANCE");
  AddClSymbol("UNBOUND-VARIABLE");
  AddClSymbol("UNDEFINED-FUNCTION");
  AddClSymbol("UNEXPORT");
  AddClSymbol("UNINTERN");
  AddClSymbol("UNION");
  AddClSymbol("UNLESS");
  AddClSymbol("UNREAD-CHAR");
  AddClSymbol("UNSIGNED-BYTE");
  AddClSymbol("UNTRACE");
  AddClSymbol("UNUSE-PACKAGE");
  AddClSymbol("UNWIND-PROTECT");
  AddClSymbol("UPDATE-INSTANCE-FOR-DIFFERENT-CLASS");
  AddClSymbol("UPDATE-INSTANCE-FOR-REDEFINED-CLASS");
  AddClSymbol("UPGRADED-ARRAY-ELEMENT-TYPE");
  AddClSymbol("UPGRADED-COMPLEX-PART-TYPE");
  AddClSymbol("UPPER-CASE-P");
  AddClSymbol("USE-PACKAGE");
  AddClSymbol("USE-VALUE");
  AddClSymbol("USER-HOMEDIR-PATHNAME");
  AddClSymbol("VALUES");
  AddClSymbol("VALUES-LIST");
  AddClSymbol("VARIABLE");
  AddClSymbol("VECTOR");
  AddClSymbol("VECTOR-POP");
  AddClSymbol("VECTOR-PUSH");
  AddClSymbol("VECTOR-PUSH-EXTEND");
  AddClSymbol("VECTORP");
  AddClSymbol("WARN");
  AddClSymbol("WARNING");
  AddClSymbol("WHEN");
  AddClSymbol("WILD-PATHNAME-P");
  AddClSymbol("WITH-ACCESSORS");
  AddClSymbol("WITH-COMPILATION-UNIT");
  AddClSymbol("WITH-CONDITION-RESTARTS");
  AddClSymbol("WITH-HASH-TABLE-ITERATOR");
  AddClSymbol("WITH-INPUT-FROM-STRING");
  AddClSymbol("WITH-OPEN-FILE");
  AddClSymbol("WITH-OPEN-STREAM");
  AddClSymbol("WITH-OUTPUT-TO-STRING");
  AddClSymbol("WITH-PACKAGE-ITERATOR");
  AddClSymbol("WITH-SIMPLE-RESTART");
  AddClSymbol("WITH-SLOTS");
  AddClSymbol("WITH-STANDARD-IO-SYNTAX");
  AddClSymbol("WRITE");
  AddClSymbol("WRITE-BYTE");
  AddClSymbol("WRITE-CHAR");
  AddClSymbol("WRITE-LINE");
  AddClSymbol("WRITE-SEQUENCE");
  AddClSymbol("WRITE-STRING");
  AddClSymbol("WRITE-TO-STRING");
  AddClSymbol("Y-OR-N-P");
  AddClSymbol("YES-OR-NO-P");
  AddClSymbol("ZEROP");
};

void initializeAllClSymbolsFunctions() {
  SYMBOL_EXPORT_SC_(CorePkg, calculateMissingCommonLispSymbols);
};
};
#endif
