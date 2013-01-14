/*
    Simple calculator implemented in Perl.
    The grammar is standard YACC, but the actions are in Perl.
    This YACC file must be processed by a version of YACC that
    supports Perl output.

    The calculator handles the basic operations, but nothing fancy.
    This is mostly a demonstration of the Perl/Yacc combination.

    $P holds the previous value, that is, the value of the most
       recent expression.  The user can refer to this with "%".
    %V holds user-defined variables; variables are defined by assinging
       to them.  References to an undefined variable produces a warning,
       and assigns 0 to the variable.
    The user can also get a Perl escape with &, followed by a string.

    Ray Lischner
    17 August 1990
*/

%token INT FLOAT STRING IDENT

%left   '='
%left   '|'
%left   '&'
%left   EQ NE PLUS
%left   GT GE LT LE
%left   L_SHIFT R_SHIFT
%left   '+' '-'
%left   '*' '/'
%right  EXP
%right  '!'
%right  UNARY

%start  start_expr

%{ 
/* Python Declarations */
import re
debug = 0
%}

%%

start_expr : expr
    {
      print "And the answer is ", $1
    }
    | # empty
    ;

expr: '(' expr ')'
    { 
      $$ = $2 
    }
    | expr '+' expr
    { 
      $$ = $1 + $3
      if debug : print "sum=", $$
    }
    | expr '-' expr
    { 
      $$ = $1 - $3 
    }
    | expr '*' expr
    { 
      $$ = $1 * $3 
      if debug : print "prod:", $1, "*", $3, "=", $$
    }
    | expr '/' expr
    { 
      $$ = $1 / $3 
    }
    | INT
    { 
      $$ = $1
    }
    ;

%%

def yylex() :

  # 
  # You may return single punctuation characters as strings.
  #
  # The return value is a 2-tuple consisting of ( token, yylval ).
  #

  global line, debug

  # Whitspace
  m = re.match( "^(\s*)(.*)", line )

  if m :
    line = m.group( 2 )
  else :
    return ( 0, 0 )

  # Punctuation
  m = re.match( "^([\+\-\*\/])(.*)", line )
  if m : 
    line = m.group( 2 )
    if debug: print "sym = ", m.group(1)
    return ( m.group( 1 ), 0 )

  # Numbers
  m = re.match( "^(\d+)(.*)", line )
  if m : 
    line = m.group( 2 )
    if debug: print "num = ", m.group(1)
    return ( INT, int( m.group( 1 )) )

  # Anything else is unrecognized
  if len( line ) :
    try :
      yyerror()
    except NameError :
      print( "lex error '%s'" % line )

  # We're all out of input
  return ( 0, 0 )

while 1 :
  line = raw_input( "Enter expression (. to quit) " )

  if line == '.' :
    break
  else:
    yyparse()

