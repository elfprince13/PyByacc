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

%left	'='
%left	'|'
%left	'&'
%left	EQ NE
%left	GT GE LT LE
%left	L_SHIFT R_SHIFT
%left	'+' '-'
%left	'*' '/'
%right	EXP
%right	'!'
%right	UNARY

%start	stmt_list

%%

stmt_list:	/* empty */
	|	stmt_list stmt
	;

stmt:		terminator
	|	expr terminator
		{ print $1, "\n" if $2 eq "\n"; $P = $1; }
	|	error terminator
		{ &yyerrok; }
	;

terminator:	';'
		{ $$ = $1; }
	|	'\n'
		{ $$ = $1; }
	;

expr:		'(' expr ')'
		{ $$ = $2; }
	|	expr '|' expr
		{ $$ = $1 || $3; }
	|	expr '&' expr
		{ $$ = $1 && $3; }
	|	expr EQ expr
		{ $$ = $1 == $3; }
	|	expr NE expr
		{ $$ = $1 != $3; }
	|	expr GT expr
		{ $$ = $1 > $3; }
	|	expr GE expr
		{ $$ = $1 >= $3; }
	|	expr LT expr
		{ $$ = $1 < $3; }
	|	expr LE expr
		{ $$ = $1 <= $3; }
	|	expr L_SHIFT expr
		{ $$ = $1 << $3; }
	|	expr R_SHIFT expr
		{ $$ = $1 >> $3; }
	|	expr '+' expr
		{ $$ = $1 + $3; }
	|	expr '-' expr
		{ $$ = $1 - $3; }
	|	expr '*' expr
		{ $$ = $1 * $3; }
	|	expr '/' expr
		{ $$ = $1 / $3; }
	|	expr EXP expr
		{ $$ = $1 ** $3; }
	|	expr '!'
		{ $$ = &fact($1); }
	|	'-' expr		%prec UNARY
		{ $$ = -$2; }
	|	'!' expr		%prec UNARY
		{ $$ = !$2; }
	|	'+' expr		%prec UNARY
		{ $$ = $2; }
	|	'&' STRING		%prec UNARY
		{ $$ = eval($2); }
	|	IDENT '=' expr
		{ eval '$V{'.$1.'}=('.$3.'); 1' || &yyerror($@); $$ = $V{$1}; }
	|	IDENT
		{ if (! defined $V{$1}) {
		    &yyerror($1.": undefined variable");
		    $V{$1} = 0;
		  }
		  $$ = $V{$1};
		}
	|	INT
		{ $$ = $1; }
	|	FLOAT
		{ $$ = $1; }
	|	STRING
		{ $$ = $1; }
	|	'%'
		{ $$ = $P; }
	;

%%

# Prompt the user on STDERR, but only prompt if STDERR and the input
# file are both terminals.

# read from STDIN if no files are named on the command line
unshift(@ARGV, '-') if $#ARGV < $[;

# After finishing a file, open the next one.  Return whether there
# really is a next one that was opened.
sub next_file
{
    while ($ARGV = shift(@ARGV)) {
	if (! open(ARGV, $ARGV)) {
	    print STDERR "$ARGV: cannot open file: $!\n";
	    next;
	}
	$prompt = (-t ARGV && -t STDERR) ? '(Calc) ' : '';
	last;
    }
    $ARGV >= $[;
}

# print he prompt
sub prompt
{
    print STDERR $prompt if $prompt;
}

# print an error message
sub yyerror
{
    print STDERR "\"$ARGV\", " if $ARGV ne '-';
    print STDERR "line $.: ", @_, "\n";
}

# Hand-coded lex until I write lex -p, too!
sub yylex
{
 lexloop:
    {
	# get a line of input, if we need it.
	if ($line eq '') {
	    &prompt;
	    $line = <ARGV>;
	    if ($line eq '') {
		close(ARGV);
		&next_file || return(0);
	    }
	}

	# Skip over white space, and grab the first character.
	# If there is no such character, then grab the next line.
	$line =~ s/^[ \t\f\r\v]*(.|\n)//	|| next lexloop;
	local($char) = $1;
	if ($char eq '#') {
	    # comment, so discard the line
	    $line = "\n";
	    &yylex;
	} elsif ($char =~ /^['"]/) {
	    # collect the string
	    if ($line =~ s/^([^$char]*)$char//) {
		$yylval = $1;
	    } else {
		&yyerror('unterminated string');
		$yylval = '';
	    }
	    $STRING;
	} elsif ($char =~ /^\d/) {
	    # number, is it integer or float?
	    if ($line =~ s/^(\d+)//) {
		$yylval = int($char . $1);
	    } else {
		$yylval = int($char);
	    }
	    $type = $INT;
	    if ($line =~ s/^(\.\d*)//) {
		$tmp = "0$1";
		$yylval += $tmp;
		$type = $FLOAT;
	    }
	    if ($line =~ s/^[eE]([-+]*\d+)//) {
		$yylval *= 10 ** $1;
		$type = $FLOAT;
	    }
	    $type;
	} elsif ($char =~ /^\w/) {
	    # identifier
	    $line =~ s/^([\w\d]*)//;
	    $yylval = $char.$1;
	    $IDENT;
	} elsif ($char eq '*' && $line =~ s/^\*//) {
	    $EXP;
	} elsif ($char eq '!' && $line =~ s/^=//) {
	    $NE;
	} elsif ($char eq '=' && $line =~ s/^=//) {
	    $EQ;
	} elsif ($char =~ /^[<>]/ && $line =~ s/^=//) {
	    $char eq '<' ? $LE : $GE;
	} elsif ($char =~ /^[<>]/ && $line =~ s/^$char//) {
	    $char eq '<' ? $L_SHIFT : $R_SHIFT;
	} else {
	    $yylval = $char;
	    ord($char);
	}
    }
}

# factorial
sub fact
{
    local($n) = @_;
    local($f) = 1;
    $f *= $n-- while ($n > 1) ;
    $f;
}

# catch signals
sub catch
{
    local($signum) = @_;
    print STDERR "\n" if (-t STDERR && -t STDIN);
    &yyerror("Floating point exception") if $signum = 8;
    next outer;
}
$SIG{'INT'} = 'catch';
$SIG{'FPE'} = 'catch';

select(STDERR); $| = 1;
select(STDOUT);
&next_file;

# main program
outer: while(1)
{
    $line = '';
    eval '$status = &yyparse;';
    exit $status if ! $@;
    &yyerror($@);
}
