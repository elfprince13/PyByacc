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

%start start_expr 

%%

start_expr : expr
    {
      $$ = $1;
      print "ans = ",$$,"\n";
    }
    ;

expr: '(' expr ')'
    { 
      $$ = $2 ;
    }
    | expr '+' expr
    { 
      $$ = $1 + $3;
      print "sum=", $1, $3, $$, "\n";
    }
    | expr '-' expr
    { 
      $$ = $1 - $3 ;
    }
    | expr '*' expr
    { 
      $$ = $1 * $3 ;
    }
    | expr '/' expr
    { 
      $$ = $1 / $3 ;
    }
    | INT
    { 
      $$ = $1;
    }
    ;

%%

@tokenlist = ( $INT, ord('+'), $INT, ord('*'), $INT );
@lvallist = ( 6, 0, 5, 0, 2 );


# Hand-coded lex until I write lex -p, too!
sub yylex
{
  if( length( @tokenlist ) )
  {
    $yylval = shift( @lvallist );
    return  shift(@tokenlist );
  }
  else
  {
    return 0;
  }
}

yyparse()

