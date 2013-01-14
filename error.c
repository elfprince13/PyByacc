/* routines for printing error messages	 */

#include "defs.h"


#if __STDC__
void fatal(char *msg)
#else
void fatal(msg)
char *msg;
#endif
{
    fprintf(stderr, "%s: f - %s\n", myname, msg);
    done(2);
}


#if __STDC__
void no_space(void)
#else
void no_space()
#endif
{
    fprintf(stderr, "%s: f - out of space\n", myname);
    done(2);
}


#if __STDC__
void open_error(char *filename)
#else
void open_error(filename)
char *filename;
#endif
{
    fprintf(stderr, "%s: f - cannot open \"%s\"\n", myname, filename);
    done(2);
}


#if __STDC__
void unexpected_EOF(void)
#else
void unexpected_EOF()
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", unexpected end-of-file\n",
	    myname, lineno, input_file_name);
    done(1);
}


#if __STDC__
void print_pos(char *st_line, char *st_cptr)
#else
void print_pos(st_line, st_cptr)
char *st_line;
char *st_cptr;
#endif
{
    register char *s;

    if (st_line == 0) return;
    for (s = st_line; *s != '\n'; ++s)
    {
	if (isprint(*s) || *s == '\t')
	    putc(*s, stderr);
	else
	    putc('?', stderr);
    }
    putc('\n', stderr);
    for (s = st_line; s < st_cptr; ++s)
    {
	if (*s == '\t')
	    putc('\t', stderr);
	else
	    putc(' ', stderr);
    }
    putc('^', stderr);
    putc('\n', stderr);
}


#if __STDC__
void syntax_error(int st_lineno, char *st_line, char *st_cptr)
#else
void syntax_error(st_lineno, st_line, st_cptr)
int st_lineno;
char *st_line;
char *st_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", syntax error\n",
	    myname, st_lineno, input_file_name);
    print_pos(st_line, st_cptr);
    done(1);
}


#if __STDC__
void unterminated_comment(int c_lineno, char *c_line, char *c_cptr)
#else
void unterminated_comment(c_lineno, c_line, c_cptr)
int c_lineno;
char *c_line;
char *c_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", unmatched /*\n",
	    myname, c_lineno, input_file_name);
    print_pos(c_line, c_cptr);
    done(1);
}


#if __STDC__
void unterminated_string(int s_lineno, char *s_line, char *s_cptr)
#else
void unterminated_string(s_lineno, s_line, s_cptr)
int s_lineno;
char *s_line;
char *s_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", unterminated string\n",
	    myname, s_lineno, input_file_name);
    print_pos(s_line, s_cptr);
    done(1);
}


#if __STDC__
void unterminated_text(int t_lineno, char *t_line, char *t_cptr)
#else
void unterminated_text(t_lineno, t_line, t_cptr)
int t_lineno;
char *t_line;
char *t_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", unmatched %%{\n",
	    myname, t_lineno, input_file_name);
    print_pos(t_line, t_cptr);
    done(1);
}


#if __STDC__
void unterminated_union(int u_lineno, char *u_line, char *u_cptr)
#else
void unterminated_union(u_lineno, u_line, u_cptr)
int u_lineno;
char *u_line;
char *u_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", unterminated %%union \
declaration\n", myname, u_lineno, input_file_name);
    print_pos(u_line, u_cptr);
    done(1);
}


#if __STDC__
void over_unionized(char *u_cptr)
#else
void over_unionized(u_cptr)
char *u_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", too many %%union \
declarations\n", myname, lineno, input_file_name);
    print_pos(line, u_cptr);
    done(1);
}


#if __STDC__
void illegal_tag(int t_lineno, char *t_line, char *t_cptr)
#else
void illegal_tag(t_lineno, t_line, t_cptr)
int t_lineno;
char *t_line;
char *t_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", illegal tag\n",
	    myname, t_lineno, input_file_name);
    print_pos(t_line, t_cptr);
    done(1);
}


#if __STDC__
void illegal_character(char *c_cptr)
#else
void illegal_character(c_cptr)
char *c_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", illegal character\n",
	    myname, lineno, input_file_name);
    print_pos(line, c_cptr);
    done(1);
}


#if __STDC__
void used_reserved(char *s)
#else
void used_reserved(s)
char *s;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", illegal use of reserved symbol \
%s\n", myname, lineno, input_file_name, s);
    done(1);
}


#if __STDC__
void tokenized_start(char *s)
#else
void tokenized_start(s)
char *s;
#endif
{
     fprintf(stderr, "%s: e - line %d of \"%s\", the start symbol %s cannot be \
declared to be a token\n", myname, lineno, input_file_name, s);
     done(1);
}


#if __STDC__
void retyped_warning(char *s)
#else
void retyped_warning(s)
char *s;
#endif
{
    fprintf(stderr, "%s: w - line %d of \"%s\", the type of %s has been \
redeclared\n", myname, lineno, input_file_name, s);
}


#if __STDC__
void reprec_warning(char *s)
#else
void reprec_warning(s)
char *s;
#endif
{
    fprintf(stderr, "%s: w - line %d of \"%s\", the precedence of %s has been \
redeclared\n", myname, lineno, input_file_name, s);
}


#if __STDC__
void revalued_warning(char *s)
#else
void revalued_warning(s)
char *s;
#endif
{
    fprintf(stderr, "%s: w - line %d of \"%s\", the value of %s has been \
redeclared\n", myname, lineno, input_file_name, s);
}


#if __STDC__
void terminal_start(char *s)
#else
void terminal_start(s)
char *s;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", the start symbol %s is a \
token\n", myname, lineno, input_file_name, s);
    done(1);
}


#if __STDC__
void restarted_warning(void)
#else
void restarted_warning()
#endif
{
    fprintf(stderr, "%s: w - line %d of \"%s\", the start symbol has been \
redeclared\n", myname, lineno, input_file_name);
}


#if __STDC__
void no_grammar(void)
#else
void no_grammar()
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", no grammar has been \
specified\n", myname, lineno, input_file_name);
    done(1);
}


#if __STDC__
void terminal_lhs(int s_lineno)
#else
void terminal_lhs(s_lineno)
int s_lineno;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", a token appears on the lhs \
of a production\n", myname, s_lineno, input_file_name);
    done(1);
}


#if __STDC__
void prec_redeclared(void)
#else
void prec_redeclared()
#endif
{
    fprintf(stderr, "%s: w - line %d of  \"%s\", conflicting %%prec \
specifiers\n", myname, lineno, input_file_name);
}


#if __STDC__
void unterminated_action(int a_lineno, char *a_line, char *a_cptr)
#else
void unterminated_action(a_lineno, a_line, a_cptr)
int a_lineno;
char *a_line;
char *a_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", unterminated action\n",
	    myname, a_lineno, input_file_name);
    print_pos(a_line, a_cptr);
    done(1);
}


#if __STDC__
void dollar_warning(int a_lineno, int i)
#else
void dollar_warning(a_lineno, i)
int a_lineno;
int i;
#endif
{
    fprintf(stderr, "%s: w - line %d of \"%s\", $%d references beyond the \
end of the current rule\n", myname, a_lineno, input_file_name, i);
}


#if __STDC__
void dollar_error(int a_lineno, char *a_line, char *a_cptr)
#else
void dollar_error(a_lineno, a_line, a_cptr)
int a_lineno;
char *a_line;
char *a_cptr;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", illegal $-name\n",
	    myname, a_lineno, input_file_name);
    print_pos(a_line, a_cptr);
    done(1);
}


#if __STDC__
void untyped_lhs(void)
#else
void untyped_lhs()
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", $$ is untyped\n",
	    myname, lineno, input_file_name);
    done(1);
}


#if __STDC__
void untyped_rhs(int i, char *s)
#else
void untyped_rhs(i, s)
int i;
char *s;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", $%d (%s) is untyped\n",
	    myname, lineno, input_file_name, i, s);
    done(1);
}


#if __STDC__
void unknown_rhs(int i)
#else
void unknown_rhs(i)
int i;
#endif
{
    fprintf(stderr, "%s: e - line %d of \"%s\", $%d is untyped\n",
	    myname, lineno, input_file_name, i);
    done(1);
}


#if __STDC__
void default_action_warning(void)
#else
void default_action_warning()
#endif
{
    fprintf(stderr, "%s: w - line %d of \"%s\", the default action assigns an \
undefined value to $$\n", myname, lineno, input_file_name);
}


#if __STDC__
void undefined_goal(char *s)
#else
void undefined_goal(s)
char *s;
#endif
{
    fprintf(stderr, "%s: e - the start symbol %s is undefined\n", myname, s);
    done(1);
}


#if __STDC__
void undefined_symbol_warning(char *s)
#else
void undefined_symbol_warning(s)
char *s;
#endif
{
    fprintf(stderr, "%s: w - the symbol %s is undefined\n", myname, s);
}
