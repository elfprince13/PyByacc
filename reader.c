#include "defs.h"

/*  The line size must be a positive integer.  One hundred was chosen	*/
/*  because few lines in Yacc input grammars exceed 100 characters.	*/
/*  Note that if a line exceeds LINESIZE characters, the line buffer	*/
/*  will be expanded to accomodate it.					*/

#define LINESIZE 100

char *cache;
int cinc, cache_size;

int ntags, tagmax;
char **tag_table;

char saw_eof, unionized;
char *cptr, *line;
int linesize;

bucket *goal;
int prec;
int gensym;
char last_was_action;

int maxitems;
bucket **pitem;

int maxrules;
bucket **plhs;

int name_pool_size;
char *name_pool;

char line_format[] = "#line %d \"%s\"\n";

/* dollar sign is allowed in identifiers */
#define dollar_ok()	(language==C)


static void cachec _P_((int c));
static void get_line _P_((void));
static char *dup_line _P_((void));
static void skip_comment _P_((void));
static int nextc _P_((void));
static int keyword _P_((void));
static void copy_ident _P_((void));
static void copy_text _P_((void));
static void perl_comment _P_((FILE *text_file, FILE *other_file));
static void copy_union _P_((void));
static int hexval _P_((int c));
static bucket *get_literal _P_((void));
static int is_reserved _P_((char *name));
static bucket *get_name _P_((void));
static int get_number _P_((void));
static char *get_tag _P_((void));
static void declare_tokens _P_((int assoc));
static void declare_types _P_((void));
static void declare_start _P_((void));
static void read_declarations _P_((void));
static void initialize_grammar _P_((void));
static void expand_items _P_((void));
static void expand_rules _P_((void));
static void advance_to_start _P_((void));
static void start_rule _P_((register bucket *bp, int s_lineno));
static void end_rule _P_((void));
static void insert_empty_rule _P_((void));
static void add_symbol _P_((void));
static void copy_action _P_((void));
static int mark_symbol _P_((void));
static void read_grammar _P_((void));
static void free_tags _P_((void));
static void pack_names _P_((void));
static void check_symbols _P_((void));
static void pack_symbols _P_((void));
static void pack_grammar _P_((void));
static void print_grammar _P_((void));


#if __STDC__
static void cachec(int c)
#else
static void cachec(c)
int c;
#endif
{
    assert(cinc >= 0);
    if (cinc >= cache_size)
    {
	cache_size += 256;
	cache = REALLOC(cache, cache_size);
    }
    cache[cinc] = c;
    ++cinc;
}


#if __STDC__
static void get_line(void)
#else
static void get_line()
#endif
{
    register FILE *f = input_file;
    register int c;
    register int i;

    if (saw_eof || (c = getc(f)) == EOF)
    {
	if (line) { FREE(line); line = 0; }
	cptr = 0;
	saw_eof = 1;
	return;
    }

    if (line == 0 || linesize != (LINESIZE + 1))
    {
	if (line) FREE(line);
	linesize = LINESIZE + 1;
	line = MALLOC(linesize);
    }

    i = 0;
    ++lineno;
    for (;;)
    {
	line[i]	 =  c;
	if (c == '\n') { cptr = line; return; }
	if (++i >= linesize)
	{
	    linesize += LINESIZE;
	    line = REALLOC(line, linesize);
	}
	c = getc(f);
	if (c ==  EOF)
	{
	    line[i] = '\n';
	    saw_eof = 1;
	    cptr = line;
	    return;
	}
    }
}


#if __STDC__
static char *dup_line(void)
#else
static char *dup_line()
#endif
{
    register char *p, *s, *t;

    if (line == 0) return (0);
    s = line;
    while (*s != '\n') ++s;
    p = MALLOC(s - line + 1);

    s = line;
    t = p;
    while ((*t++ = *s++) != '\n') continue;
    return (p);
}


#if __STDC__
static void skip_comment(void)
#else
static void skip_comment()
#endif
{
    register char *s;

    int st_lineno = lineno;
    char *st_line = dup_line();
    char *st_cptr = st_line + (cptr - line);

    s = cptr + 2;
    for (;;)
    {
	if (*s == '*' && s[1] == '/')
	{
	    cptr = s + 2;
	    FREE(st_line);
	    return;
	}
	if (*s == '\n')
	{
	    get_line();
	    if (line == 0)
		unterminated_comment(st_lineno, st_line, st_cptr);
	    s = cptr;
	}
	else
	    ++s;
    }
}


#if __STDC__
static int nextc(void)
#else
static int nextc()
#endif
{
    register char *s;

    if (line == 0)
    {
	get_line();
	if (line == 0)
	    return (EOF);
    }

    s = cptr;
    for (;;)
    {
	switch (*s)
	{
	case '\n':
	    get_line();
	    if (line == 0) return (EOF);
	    s = cptr;
	    break;

	case ' ':
	case '\t':
	case '\f':
	case '\r':
	case '\v':
	case ',':
	case ';':
	    ++s;
	    break;

	case '\\':
	    cptr = s;
	    return ('%');

	case '#':
	    if ((language == PERL) || (language == PYTHON)) {
		get_line();
		if (line == 0) return (EOF);
		s = cptr;
		break;
	    }
	    cptr = s;
	    return (*s);

	case '/':
	    if (s[1] == '*')
	    {
		cptr = s;
		skip_comment();
		s = cptr;
		break;
	    }
	    else if (s[1] == '/')
	    {
		get_line();
		if (line == 0) return (EOF);
		s = cptr;
		break;
	    }
	    cptr = s;
	    return (*s);

	default:
	    cptr = s;
	    return (*s);
	}
    }
}


#if __STDC__
static int keyword(void)
#else
static int keyword()
#endif
{
    register int c;
    char *t_cptr = cptr;

    c = *++cptr;
    if (isalpha(c))
    {
	cinc = 0;
	for (;;)
	{
	    if (isalpha(c))
	    {
		if (isupper(c)) c = tolower(c);
		cachec(c);
	    }
	    else if (isdigit(c) || c == '_' || c == '.' || (dollar_ok() && c == '$'))
		cachec(c);
	    else
		break;
	    c = *++cptr;
	}
	cachec(NUL);

	if (strcmp(cache, "token") == 0 || strcmp(cache, "term") == 0)
	    return (TOKEN);
	if (strcmp(cache, "type") == 0)
	    return (TYPE);
	if (strcmp(cache, "left") == 0)
	    return (LEFT);
	if (strcmp(cache, "right") == 0)
	    return (RIGHT);
	if (strcmp(cache, "nonassoc") == 0 || strcmp(cache, "binary") == 0)
	    return (NONASSOC);
	if (strcmp(cache, "start") == 0)
	    return (START);
	if (strcmp(cache, "union") == 0)
	    return (UNION);
	if (strcmp(cache, "ident") == 0)
	    return (IDENT);
    }
    else
    {
	++cptr;
	if (c == '{')
	    return (TEXT);
	if (c == '%' || c == '\\')
	    return (MARK);
	if (c == '<')
	    return (LEFT);
	if (c == '>')
	    return (RIGHT);
	if (c == '0')
	    return (TOKEN);
	if (c == '2')
	    return (NONASSOC);
    }
    syntax_error(lineno, line, t_cptr);
    /*NOTREACHED*/
}


#if __STDC__
static void copy_ident(void)
#else
static void copy_ident()
#endif
{
    register int c;
    register FILE *f = output_file;

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c != '"') syntax_error(lineno, line, cptr);
    ++outline;
    fprintf(f, "#ident \"");
    for (;;)
    {
	c = *++cptr;
	if (c == '\n')
	{
	    fprintf(f, "\"\n");
	    return;
	}
	putc(c, f);
	if (c == '"')
	{
	    putc('\n', f);
	    ++cptr;
	    return;
	}
    }
}


#if __STDC__
static void copy_text(void)
#else
static void copy_text()
#endif
{
    register int c;
    int quote;
    register FILE *f = text_file;
    int need_newline = 0;
    int t_lineno = lineno;
    char *t_line = dup_line();
    char *t_cptr = t_line + (cptr - line - 2);

    if (*cptr == '\n')
    {
	get_line();
	if (line == 0)
	    unterminated_text(t_lineno, t_line, t_cptr);
    }
    if (!lflag) fprintf(f, line_format, lineno, input_file_name);

loop:
    c = *cptr++;
    switch (c)
    {
    case '\n':
    next_line:
	putc('\n', f);
	need_newline = 0;
	get_line();
	if (line) goto loop;
	unterminated_text(t_lineno, t_line, t_cptr);

    case '\'':
    case '"':
	{
	    int s_lineno = lineno;
	    char *s_line = dup_line();
	    char *s_cptr = s_line + (cptr - line - 1);

	    quote = c;
	    putc(c, f);
	    for (;;)
	    {
		c = *cptr++;
		putc(c, f);
		if (c == quote)
		{
		    need_newline = 1;
		    FREE(s_line);
		    goto loop;
		}
		if (c == '\n')
		    unterminated_string(s_lineno, s_line, s_cptr);
		if (c == '\\')
		{
		    c = *cptr++;
		    putc(c, f);
		    if (c == '\n')
		    {
			get_line();
			if (line == 0)
			    unterminated_string(s_lineno, s_line, s_cptr);
		    }
		}
	    }
	}

    case '/':
	need_newline = 1;
	c = *cptr;
	if (c == '/')
	{
	    if ((language == PERL) || (language == PYTHON))
		fprintf(f, (cptr == line + 1) ? ";#" : "#");
	    else
		fprintf(f, "/*");
	    while ((c = *++cptr) != '\n')
	    {
		if (c == '*' && cptr[1] == '/')
		    fprintf(f, "* ");
		else
		    putc(c, f);
	    }
	    if (language == C)
		fprintf(f, "*/");
	    goto next_line;
	}
	else if (c == '*')
	{
	    int c_lineno = lineno;
	    char *c_line = dup_line();
	    char *c_cptr = c_line + (cptr - line - 1);

	    if ((language == PERL) || (language == PYTHON))
		fprintf(f, (cptr == line + 1) ? ";#" : "#");
	    else
		fprintf(f, "/*");
	    ++cptr;
	    for (;;)
	    {
		c = *cptr++;
		putc(c, f);
		if (c == '*' && *cptr == '/')
		{
		    if (language == C)
			putc('/', f);
		    ++cptr;
		    FREE(c_line);
		    goto loop;
		}
		if (c == '\n')
		{
		    get_line();
		    if (line == 0)
			unterminated_comment(c_lineno, c_line, c_cptr);
		}
	    }
	}
	else
	    putc('/', f);
	goto loop;

    case '%':
    case '\\':
	if (*cptr == '}')
	{
	    if (need_newline) putc('\n', f);
	    ++cptr;
	    FREE(t_line);
	    return;
	}
	putc(c, f);
	need_newline = 1;
	goto loop;

    case '#':
	if ((language == PERL) || (language == PYTHON)) {
	    fprintf(f, (cptr == line + 1) ? ";#" : "#");
	    need_newline = 1;
	    while ((c = *cptr++) != '\n')
		putc(c, f);
	    goto next_line;
	}
	putc(c, f);
	need_newline = 1;
	goto loop;
	
    default:
	putc(c, f);
	need_newline = 1;
	goto loop;
    }
}

#if __STDC__
static void perl_comment(FILE *text_file, FILE *other_file)
#else
static void perl_comment(text_file, other_file)
FILE *text_file;
FILE *other_file;
#endif
{
	if ((language == PERL) || (language == PYTHON))
    {
	fprintf(text_file, (cptr == line + 1) ? ";#" : "#");
	if (dflag)
	    fprintf(other_file, (cptr == line + 1) ? ";#" : "#");
    }
}
  
#if __STDC__
static void copy_union(void)
#else
static void copy_union()
#endif
{
    register int c;
    int quote;
    int depth;
    int u_lineno = lineno;
    char *u_line = dup_line();
    char *u_cptr = u_line + (cptr - line - 6);

    if (unionized) over_unionized(cptr - 6);
    unionized = 1;

    if (!lflag)
	fprintf(text_file, line_format, lineno, input_file_name);

    perl_comment(text_file, union_file);
    fprintf(text_file, "typedef union");
    if (dflag) fprintf(union_file, "typedef union");

    depth = 0;
loop:
    c = *cptr++;
    putc(c, text_file);
    if (dflag) putc(c, union_file);
    switch (c)
    {
    case '\n':
    next_line:
	get_line();
	if (line == 0) unterminated_union(u_lineno, u_line, u_cptr);
	perl_comment(text_file, union_file);
	goto loop;

    case '{':
	++depth;
	goto loop;

    case '}':
	if (--depth == 0)
	{
	    fprintf(text_file, " %sSTYPE;\n", define_prefix);
	    FREE(u_line);
	    return;
	}
	goto loop;

    case '\'':
    case '"':
	{
	    int s_lineno = lineno;
	    char *s_line = dup_line();
	    char *s_cptr = s_line + (cptr - line - 1);

	    quote = c;
	    for (;;)
	    {
		c = *cptr++;
		putc(c, text_file);
		if (dflag) putc(c, union_file);
		if (c == quote)
		{
		    FREE(s_line);
		    goto loop;
		}
		if (c == '\n')
		    unterminated_string(s_lineno, s_line, s_cptr);
		if (c == '\\')
		{
		    c = *cptr++;
		    putc(c, text_file);
		    if (dflag) putc(c, union_file);
		    if (c == '\n')
		    {
			get_line();
			if (line == 0)
			    unterminated_string(s_lineno, s_line, s_cptr);
		    }
		}
	    }
	}

    case '/':
	c = *cptr;
	if (c == '/')
	{
	    putc('*', text_file);
	    if (dflag) putc('*', union_file);
	    while ((c = *++cptr) != '\n')
	    {
		if (c == '*' && cptr[1] == '/')
		{
		    fprintf(text_file, "* ");
		    if (dflag) fprintf(union_file, "* ");
		}
		else
		{
		    putc(c, text_file);
		    if (dflag) putc(c, union_file);
		}
	    }
	    fprintf(text_file, "*/\n");
	    if (dflag) fprintf(union_file, "*/\n");
	    goto next_line;
	}
	if (c == '*')
	{
	    int c_lineno = lineno;
	    char *c_line = dup_line();
	    char *c_cptr = c_line + (cptr - line - 1);

	    putc('*', text_file);
	    if (dflag) putc('*', union_file);
	    ++cptr;
	    for (;;)
	    {
		c = *cptr++;
		putc(c, text_file);
		if (dflag) putc(c, union_file);
		if (c == '*' && *cptr == '/')
		{
		    putc('/', text_file);
		    if (dflag) putc('/', union_file);
		    ++cptr;
		    FREE(c_line);
		    goto loop;
		}
		if (c == '\n')
		{
		    get_line();
		    if (line == 0)
			unterminated_comment(c_lineno, c_line, c_cptr);
		}
	    }
	}
	goto loop;

    default:
	goto loop;
    }
}


#if __STDC__
static int hexval(int c)
#else
static int hexval(c)
int c;
#endif
{
    if (c >= '0' && c <= '9')
	return (c - '0');
    if (c >= 'A' && c <= 'F')
	return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f')
	return (c - 'a' + 10);
    return (-1);
}


#if __STDC__
static bucket *get_literal(void)
#else
static bucket *get_literal()
#endif
{
    register int c, quote;
    register int i;
    register int n;
    register char *s;
    register bucket *bp;
    int s_lineno = lineno;
    char *s_line = dup_line();
    char *s_cptr = s_line + (cptr - line);

    quote = *cptr++;
    cinc = 0;
    for (;;)
    {
	c = *cptr++;
	if (c == quote) break;
	if (c == '\n') unterminated_string(s_lineno, s_line, s_cptr);
	if (c == '\\')
	{
	    char *c_cptr = cptr - 1;

	    c = *cptr++;
	    switch (c)
	    {
	    case '\n':
		get_line();
		if (line == 0) unterminated_string(s_lineno, s_line, s_cptr);
		continue;

	    case '0': case '1': case '2': case '3':
	    case '4': case '5': case '6': case '7':
		n = c - '0';
		c = *cptr;
		if (IS_OCTAL(c))
		{
		    n = (n << 3) + (c - '0');
		    c = *++cptr;
		    if (IS_OCTAL(c))
		    {
			n = (n << 3) + (c - '0');
			++cptr;
		    }
		}
		if (n > MAXCHAR) illegal_character(c_cptr);
		c = n;
		break;

	    case 'x':
		c = *cptr++;
		n = hexval(c);
		if (n < 0 || n >= 16)
		    illegal_character(c_cptr);
		for (;;)
		{
		    c = *cptr;
		    i = hexval(c);
		    if (i < 0 || i >= 16) break;
		    ++cptr;
		    n = (n << 4) + i;
		    if (n > MAXCHAR) illegal_character(c_cptr);
		}
		c = n;
		break;

	    case 'a': c = 7; break;
	    case 'b': c = '\b'; break;
	    case 'f': c = '\f'; break;
	    case 'n': c = '\n'; break;
	    case 'r': c = '\r'; break;
	    case 't': c = '\t'; break;
	    case 'v': c = '\v'; break;
	    }
	}
	cachec(c);
    }
    FREE(s_line);

    n = cinc;
    s = MALLOC(n);
    
    for (i = 0; i < n; ++i)
	s[i] = cache[i];

    cinc = 0;
    if (n == 1)
	cachec('\'');
    else
	cachec('"');

    for (i = 0; i < n; ++i)
    {
	c = ((unsigned char *)s)[i];
	if (c == '\\' || c == cache[0])
	{
	    cachec('\\');
	    cachec(c);
	}
	else if (isprint(c))
	    cachec(c);
	else
	{
	    cachec('\\');
	    switch (c)
	    {
	    case 7: cachec('a'); break;
	    case '\b': cachec('b'); break;
	    case '\f': cachec('f'); break;
	    case '\n': cachec('n'); break;
	    case '\r': cachec('r'); break;
	    case '\t': cachec('t'); break;
	    case '\v': cachec('v'); break;
	    default:
		cachec(((c >> 6) & 7) + '0');
		cachec(((c >> 3) & 7) + '0');
		cachec((c & 7) + '0');
		break;
	    }
	}
    }

    if (n == 1)
	cachec('\'');
    else
	cachec('"');

    cachec(NUL);
    bp = lookup(cache);
    bp->class = TERM;
    if (n == 1 && bp->value == UNDEFINED)
	bp->value = *(unsigned char *)s;
    FREE(s);

    return (bp);
}


#if __STDC__
static int is_reserved(char *name)
#else
static int is_reserved(name)
char *name;
#endif
{
    char *s;

    if (strcmp(name, ".") == 0 ||
	    strcmp(name, "$accept") == 0 ||
	    strcmp(name, "$end") == 0)
	return (1);

    if (name[0] == '$' && name[1] == '$' && isdigit(name[2]))
    {
	s = name + 3;
	while (isdigit(*s)) ++s;
	if (*s == NUL) return (1);
    }

    return (0);
}


#if __STDC__
static bucket *get_name(void)
#else
static bucket *get_name()
#endif
{
    register int c;

    cinc = 0;
    for (c = *cptr; IS_IDENT(c); c = *++cptr)
	cachec(c);
    cachec(NUL);

    if (is_reserved(cache)) used_reserved(cache);

    return (lookup(cache));
}


#if __STDC__
static int get_number(void)
#else
static int get_number()
#endif
{
    register int c;
    register int n;

    n = 0;
    for (c = *cptr; isdigit(c); c = *++cptr)
	n = 10*n + (c - '0');

    return (n);
}


#if __STDC__
static char *get_tag(void)
#else
static char *get_tag()
#endif
{
    register int c;
    register int i;
    register char *s;
    int t_lineno = lineno;
    char *t_line = dup_line();
    char *t_cptr = t_line + (cptr - line);

    ++cptr;
    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (!isalpha(c) && c != '_' && c != '$')
	illegal_tag(t_lineno, t_line, t_cptr);
    else if (! dollar_ok() && c == '$')
	illegal_tag(t_lineno, t_line, t_cptr);

    cinc = 0;
    do { cachec(c); c = *++cptr; } while (IS_IDENT(c));
    cachec(NUL);

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c != '>')
	illegal_tag(t_lineno, t_line, t_cptr);
    ++cptr;

    for (i = 0; i < ntags; ++i)
    {
	if (strcmp(cache, tag_table[i]) == 0)
	    return (tag_table[i]);
    }

    if (ntags >= tagmax)
    {
	tagmax += 16;
	tag_table = (char **)
			(tag_table ? REALLOC(tag_table, tagmax*sizeof(char *))
				   : MALLOC(tagmax*sizeof(char *)));
    }

    s = MALLOC(cinc);
    strcpy(s, cache);
    tag_table[ntags] = s;
    ++ntags;
    FREE(t_line);
    return (s);
}


#if __STDC__
static void declare_tokens(int assoc)
#else
static void declare_tokens(assoc)
int assoc;
#endif
{
    register int c;
    register bucket *bp;
    int value;
    char *tag = 0;

    if (assoc != TOKEN) ++prec;

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c == '<')
    {
	tag = get_tag();
	c = nextc();
	if (c == EOF) unexpected_EOF();
    }

    for (;;)
    {
	if (isalpha(c) || c == '_' || c == '.' || (dollar_ok() && c == '$'))
	    bp = get_name();
	else if (c == '\'' || c == '"')
	    bp = get_literal();
	else
	    return;

	if (bp == goal) tokenized_start(bp->name);
	bp->class = TERM;

	if (tag)
	{
	    if (bp->tag && tag != bp->tag)
		retyped_warning(bp->name);
	    bp->tag = tag;
	}

	if (assoc != TOKEN)
	{
	    if (bp->prec && prec != bp->prec)
		reprec_warning(bp->name);
	    bp->assoc = assoc;
	    bp->prec = prec;
	}

	c = nextc();
	if (c == EOF) unexpected_EOF();
	value = UNDEFINED;
	if (isdigit(c))
	{
	    value = get_number();
	    if (bp->value != UNDEFINED && value != bp->value)
		revalued_warning(bp->name);
	    bp->value = value;
	    c = nextc();
	    if (c == EOF) unexpected_EOF();
	}
    }
}


#if __STDC__
static void declare_types(void)
#else
static void declare_types()
#endif
{
    register int c;
    register bucket *bp;
    char *tag;

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c != '<') syntax_error(lineno, line, cptr);
    tag = get_tag();

    for (;;)
    {
	c = nextc();
	if (isalpha(c) || c == '_' || c == '.' || (dollar_ok() && c == '$'))
	    bp = get_name();
	else if (c == '\'' || c == '"')
	    bp = get_literal();
	else
	    return;

	if (bp->tag && tag != bp->tag)
	    retyped_warning(bp->name);
	bp->tag = tag;
    }
}


#if __STDC__
static void declare_start(void)
#else
static void declare_start()
#endif
{
    register int c;
    register bucket *bp;

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (!isalpha(c) && c != '_' && c != '.' && c != '$')
	syntax_error(lineno, line, cptr);
    else if (! dollar_ok() && c == '$')
	syntax_error(lineno, line, cptr);
    bp = get_name();
    if (bp->class == TERM)
	terminal_start(bp->name);
    if (goal && goal != bp)
	restarted_warning();
    goal = bp;
}


#if __STDC__
static void read_declarations(void)
#else
static void read_declarations()
#endif
{
    register int c, k;

    cache_size = 256;
    cache = MALLOC(cache_size);

    for (;;)
    {
	c = nextc();
	if (c == EOF) unexpected_EOF();
	if (c != '%') syntax_error(lineno, line, cptr);
	switch (k = keyword())
	{
	case MARK:
	    return;

	case IDENT:
	    copy_ident();
	    break;

	case TEXT:
	    copy_text();
	    break;

	case UNION:
	    copy_union();
	    break;

	case TOKEN:
	case LEFT:
	case RIGHT:
	case NONASSOC:
	    declare_tokens(k);
	    break;

	case TYPE:
	    declare_types();
	    break;

	case START:
	    declare_start();
	    break;
	}
    }
}


#if __STDC__
static void initialize_grammar(void)
#else
static void initialize_grammar()
#endif
{
    nitems = 4;
    maxitems = 300;
    pitem = (bucket **) MALLOC(maxitems*sizeof(bucket *));
    pitem[0] = 0;
    pitem[1] = 0;
    pitem[2] = 0;
    pitem[3] = 0;

    nrules = 3;
    maxrules = 100;
    plhs = (bucket **) MALLOC(maxrules*sizeof(bucket *));
    plhs[0] = 0;
    plhs[1] = 0;
    plhs[2] = 0;

    rprec = (short *) MALLOC(maxrules*sizeof(short));
    rprec[0] = 0;
    rprec[1] = 0;
    rprec[2] = 0;

    rassoc = (char *) MALLOC(maxrules*sizeof(char));
    rassoc[0] = TOKEN;
    rassoc[1] = TOKEN;
    rassoc[2] = TOKEN;
}


#if __STDC__
static void expand_items(void)
#else
static void expand_items()
#endif
{
    maxitems += 300;
    pitem = (bucket **) REALLOC(pitem, maxitems*sizeof(bucket *));
}


#if __STDC__
static void expand_rules(void)
#else
static void expand_rules()
#endif
{
    maxrules += 100;
    plhs = (bucket **) REALLOC(plhs, maxrules*sizeof(bucket *));
    rprec = (short *) REALLOC(rprec, maxrules*sizeof(short));
    rassoc = (char *) REALLOC(rassoc, maxrules*sizeof(char));
}


#if __STDC__
static void advance_to_start(void)
#else
static void advance_to_start()
#endif
{
    register int c;
    register bucket *bp;
    char *s_cptr;
    int s_lineno;

    for (;;)
    {
	c = nextc();
	if (c != '%') break;
	s_cptr = cptr;
	switch (keyword())
	{
	case MARK:
	    no_grammar();

	case TEXT:
	    copy_text();
	    break;

	case START:
	    declare_start();
	    break;

	default:
	    syntax_error(lineno, line, s_cptr);
	}
    }

    c = nextc();
    if (!isalpha(c) && c != '_' && c != '.')
	syntax_error(lineno, line, cptr);
    bp = get_name();
    if (goal == 0)
    {
	if (bp->class == TERM)
	    terminal_start(bp->name);
	goal = bp;
    }

    s_lineno = lineno;
    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c != ':') syntax_error(lineno, line, cptr);
    start_rule(bp, s_lineno);
    ++cptr;
}


#if __STDC__
static void start_rule(register bucket *bp, int s_lineno)
#else
static void start_rule(bp, s_lineno)
register bucket *bp;
int s_lineno;
#endif
{
    if (bp->class == TERM)
	terminal_lhs(s_lineno);
    bp->class = NONTERM;
    if (nrules >= maxrules)
	expand_rules();
    plhs[nrules] = bp;
    rprec[nrules] = UNDEFINED;
    rassoc[nrules] = TOKEN;
}


#if __STDC__
static void end_rule(void)
#else
static void end_rule()
#endif
{
    register int i;

    if (!last_was_action && plhs[nrules]->tag)
    {
	for (i = nitems - 1; pitem[i]; --i) continue;
	if (pitem[i+1] == 0 || pitem[i+1]->tag != plhs[nrules]->tag)
	    default_action_warning();
    }

    last_was_action = 0;
    if (nitems >= maxitems) expand_items();
    pitem[nitems] = 0;
    ++nitems;
    ++nrules;
}


#if __STDC__
static void insert_empty_rule(void)
#else
static void insert_empty_rule()
#endif
{
    register bucket *bp, **bpp;

    assert(cache != (char *) NULL);
    sprintf(cache, "$$%d", ++gensym);
    bp = make_bucket(cache);
    last_symbol->next = bp;
    last_symbol = bp;
    bp->tag = plhs[nrules]->tag;
    bp->class = NONTERM;

    if ((nitems += 2) > maxitems)
	expand_items();
    bpp = pitem + nitems - 1;
    *bpp-- = bp;
    while (bpp[0] = bpp[-1]) --bpp;

    if (++nrules >= maxrules)
	expand_rules();
    plhs[nrules] = plhs[nrules-1];
    plhs[nrules-1] = bp;
    rprec[nrules] = rprec[nrules-1];
    rprec[nrules-1] = 0;
    rassoc[nrules] = rassoc[nrules-1];
    rassoc[nrules-1] = TOKEN;
}


#if __STDC__
static void add_symbol(void)
#else
static void add_symbol()
#endif
{
    register int c;
    register bucket *bp;
    int s_lineno = lineno;

    c = *cptr;
    if (c == '\'' || c == '"')
	bp = get_literal();
    else
	bp = get_name();

    c = nextc();
    if (c == ':')
    {
	end_rule();
	start_rule(bp, s_lineno);
	++cptr;
	return;
    }

    if (last_was_action)
	insert_empty_rule();
    last_was_action = 0;

    if (++nitems > maxitems)
	expand_items();
    pitem[nitems-1] = bp;
}


#if __STDC__
static void copy_action(void)
#else
static void copy_action()
#endif
{
    register int c;
    register int i, n;
    int depth;
    int quote;
    char *tag;
    register FILE *f = action_file;
    int a_lineno = lineno;
    char *a_line = dup_line();
    char *a_cptr = a_line + (cptr - line);

    if (last_was_action)
	insert_empty_rule();
    last_was_action = 1;

    if (language == PYTHON)
	fprintf(f, "    if %sn == %d :\n", symbol_prefix, nrules - 2);
    else if (language == PERL)
	fprintf(f, "if ($%sn == %d) {\n", symbol_prefix, nrules - 2);
    else
	fprintf(f, "case %d:\n", nrules - 2);
    if (!lflag)
	fprintf(f, line_format, lineno, input_file_name);
    if (*cptr == '=') ++cptr;

    n = 0;
    for (i = nitems - 1; pitem[i]; --i) ++n;

    depth = 0;
loop:
    c = *cptr;
    if (c == '$')
    {
	if (cptr[1] == '<')
	{
	    int d_lineno = lineno;
	    char *d_line = dup_line();
	    char *d_cptr = d_line + (cptr - line);

	    ++cptr;
	    tag = get_tag();
	    c = *cptr;
	    if (c == '$')
	    {
		if (language == PYTHON)
		    fprintf(f, "%sval", symbol_prefix);
		else if (language == PERL)
		    fprintf(f, "$%sval", symbol_prefix);
		else
		    fprintf(f, "%sval.%s", symbol_prefix, tag);
		++cptr;
		FREE(d_line);
		goto loop;
	    }
	    else if (isdigit(c))
	    {
		i = get_number();
		if (i > n) dollar_warning(d_lineno, i);
		if (language == PYTHON)
		    fprintf(f, "%svs[%svsp-%d]",
			    symbol_prefix, symbol_prefix, n - i);
		else if (language == PERL)
		    fprintf(f, "$%svs[$%svsp-%d]",
			    symbol_prefix, symbol_prefix, n - i);
		else
		    fprintf(f, "%svsp[%d].%s", symbol_prefix, i - n, tag);
		FREE(d_line);
		goto loop;
	    }
	    else if (c == '-' && isdigit(cptr[1]))
	    {
		++cptr;
		i = -get_number() - n;
		if (language == PYTHON)
		    fprintf(f, "%svsp[%svsp-%d]",
			    symbol_prefix, symbol_prefix, -i);
		else if (language == PERL)
		    fprintf(f, "$%svsp[$%svsp-%d]",
			    symbol_prefix, symbol_prefix, -i);
		else
		    fprintf(f, "%svsp[%d].%s", symbol_prefix, i, tag);
		FREE(d_line);
		goto loop;
	    }
	    else
		dollar_error(d_lineno, d_line, d_cptr);
	}
	else if (cptr[1] == '$')
	{
	    if (ntags)
	    {
		tag = plhs[nrules]->tag;
		if (tag == 0) untyped_lhs();
		if (language == PYTHON)
		    fprintf(f, "%sval", symbol_prefix);
		else if (language == PERL)
		    fprintf(f, "$%sval", symbol_prefix);
		else
		    fprintf(f, "%sval.%s", symbol_prefix, tag);
	    }
	    else if (language == PYTHON)
		fprintf(f, "%sval", symbol_prefix);
	    else if (language == PERL)
		fprintf(f, "$%sval", symbol_prefix);
	    else
		fprintf(f, "%sval", symbol_prefix);
	    cptr += 2;
	    goto loop;
	}
	else if (isdigit(cptr[1]))
	{
	    ++cptr;
	    i = get_number();
	    if (ntags)
	    {
		if (i <= 0 || i > n)
		    unknown_rhs(i);
		tag = pitem[nitems + i - n - 1]->tag;
		if (tag == 0) untyped_rhs(i, pitem[nitems + i - n - 1]->name);
		if (language == PYTHON)
		    fprintf(f, "%svs[%svsp-%d]",
			    symbol_prefix, symbol_prefix, n - i);
		else if (language == PERL)
		    fprintf(f, "$%svs[$%svsp-%d]",
			    symbol_prefix, symbol_prefix, n - i);
		else
		    fprintf(f, "%svsp[%d].%s", symbol_prefix, i - n, tag);
	    }
	    else
	    {
		if (i > n)
		    dollar_warning(lineno, i);
		if (language == PYTHON)
		    fprintf(f, "%svs[%svsp-%d]",
			    symbol_prefix, symbol_prefix, n - i);
		else if (language == PERL)
		    fprintf(f, "$%svs[$%svsp-%d]",
			    symbol_prefix, symbol_prefix, n - i);
		else
		    fprintf(f, "%svsp[%d]", symbol_prefix, i - n);
	    }
	    goto loop;
	}
	else if (cptr[1] == '-')
	{
	    cptr += 2;
	    i = get_number();
	    if (ntags)
		unknown_rhs(-i);
	    if (language == PYTHON)
		fprintf(f, "%svs[%svsp-%d]",
			symbol_prefix, symbol_prefix, i + n);
	    else if (language == PERL)
		fprintf(f, "$%svs[$%svsp-%d]",
			symbol_prefix, symbol_prefix, i + n);
	    else
		fprintf(f, "%svsp[%d]", symbol_prefix, -i - n);
	    goto loop;
	}
    }
    if (isalpha(c) || c == '_' || (dollar_ok() && c == '$'))
    {
	do
	{
	    putc(c, f);
	    c = *++cptr;
	} while (isalnum(c) || c == '_' || (dollar_ok() && c == '$'));
	goto loop;
    }
    ++cptr;
    switch (c)
    {
    case '\n':
	putc(c, f);
next_line:
	get_line();
	if (line) goto loop;
	unterminated_action(a_lineno, a_line, a_cptr);

    case ';':
	putc(c, f);
	if (depth > 0) goto loop;
	if (language == PYTHON)
	    fprintf(f, "\nbreak; }\n");
	else if (language == PERL)
	    fprintf(f, "\nlast switch; }\n");
	else
	    fprintf(f, "\nbreak;\n");
	FREE(a_line);
	return;

    case '{':
	if (depth == 0 && language == PYTHON)
    {
        ++depth;
    }
    else
    {
        putc(c, f);
        ++depth;
    }
	goto loop;

    case '}':
	if (--depth > 0) {
	    putc(c, f);
	    goto loop;
	}

	if (language == PYTHON)
	    fprintf(f, "\n");
	else if (language == PERL)
	    fprintf(f, "\nlast switch;\n} }\n");
	else
	    fprintf(f, "}\nbreak;\n");
	FREE(a_line);
	return;

    case '\'':
    case '"':
	{
	    int s_lineno = lineno;
	    char *s_line = dup_line();
	    char *s_cptr = s_line + (cptr - line - 1);

	    putc(c, f);
	    quote = c;
	    for (;;)
	    {
		c = *cptr++;
		putc(c, f);
		if (c == quote)
		{
		    FREE(s_line);
		    goto loop;
		}
		if (c == '\n')
		    unterminated_string(s_lineno, s_line, s_cptr);
		if (c == '\\')
		{
		    c = *cptr++;
		    putc(c, f);
		    if (c == '\n')
		    {
			get_line();
			if (line == 0)
			    unterminated_string(s_lineno, s_line, s_cptr);
		    }
		}
	    }
	}

    case '/':
	c = *cptr;
	if (c == '/')
	{
	    if ((language == PERL) || (language == PYTHON)) {
		++cptr;
		goto perl_comment;
	    }
	    fprintf(f, "/*");
	    while ((c = *++cptr) != '\n')
	    {
		if (c == '*' && cptr[1] == '/')
		    fprintf(f, "* ");
		else
		    putc(c, f);
	    }
	    fprintf(f, "*/\n");
	    goto next_line;
	}
	if (c != '*')
	{
	    putc('/', f);
	}
	else
	{
	    int c_lineno = lineno;
	    char *c_line = dup_line();
	    char *c_cptr = c_line + (cptr - line - 1);

	    if ((language == PERL) || (language == PYTHON))
		fprintf(f, (cptr == line + 1) ? ";#" : "#");
	    else
		fprintf(f, "/*");
	    ++cptr;
	    for (;;)
	    {
		c = *cptr++;
		if (((language == PERL) || (language == PYTHON)) && c == '*' && *cptr == '/')
		{
		    putc('\n', f);
		    ++cptr;
		    FREE(c_line);
		    goto loop;
		}
		putc(c, f);
		if (c == '*' && *cptr == '/')
		{
		    putc('/', f);
		    ++cptr;
		    FREE(c_line);
		    goto loop;
		}
		if (c == '\n')
		{
		    get_line();
		    if (line == 0)
			unterminated_comment(c_lineno, c_line, c_cptr);
		    if ((language == PERL) || (language == PYTHON))
			fprintf(f, ";# ");
		}
	    }
	}
	goto loop;

    case '#':
perl_comment:
	if ((language == PERL) || (language == PYTHON))
	{
	    putc('#', f);
	    do {
		putc(*cptr, f);
	    } while (*cptr++ != '\n');
	    goto next_line;
	}
	else
	{
	    putc(c, f);
	}
	goto loop;

    default:
	putc(c, f);
	goto loop;
    }

    /*NOTREACHED*/ /* or at least it better not be reached*/
}


#if __STDC__
static int mark_symbol(void)
#else
static int mark_symbol()
#endif
{
    register int c;
    register bucket *bp;

    c = cptr[1];
    if (c == '%' || c == '\\')
    {
	cptr += 2;
	return (1);
    }

    if (c == '=')
	cptr += 2;
    else if ((c == 'p' || c == 'P') &&
	     ((c = cptr[2]) == 'r' || c == 'R') &&
	     ((c = cptr[3]) == 'e' || c == 'E') &&
	     ((c = cptr[4]) == 'c' || c == 'C') &&
	     ((c = cptr[5], !IS_IDENT(c))))
	cptr += 5;
    else
	syntax_error(lineno, line, cptr);

    c = nextc();
    if (isalpha(c) || c == '_' || c == '.' || (dollar_ok() && c == '$'))
	bp = get_name();
    else if (c == '\'' || c == '"')
	bp = get_literal();
    else
    {
	syntax_error(lineno, line, cptr);
	/*NOTREACHED*/
    }

    if (rprec[nrules] != UNDEFINED && bp->prec != rprec[nrules])
	prec_redeclared();

    rprec[nrules] = bp->prec;
    rassoc[nrules] = bp->assoc;
    return (0);
}


#if __STDC__
static void read_grammar(void)
#else
static void read_grammar()
#endif
{
    register int c;

    initialize_grammar();
    advance_to_start();

    for (;;)
    {
	c = nextc();
	if (c == EOF) break;
	if (isalpha(c) || c == '_' || c == '.' || (dollar_ok() && c == '$') || c == '\'' ||
		c == '"')
	    add_symbol();
	else if (c == '{' || c == '=')
	    copy_action();
	else if (c == '|')
	{
	    end_rule();
	    start_rule(plhs[nrules-1], 0);
	    ++cptr;
	}
	else if (c == '%')
	{
	    if (mark_symbol()) break;
	}
	else
	    syntax_error(lineno, line, cptr);
    }
    end_rule();
}


#if __STDC__
static void free_tags(void)
#else
static void free_tags()
#endif
{
    register int i;

    if (tag_table == 0) return;

    for (i = 0; i < ntags; ++i)
    {
	assert(tag_table[i] != (char *) NULL);
	FREE(tag_table[i]);
    }
    FREE(tag_table);
}


#if __STDC__
static void pack_names(void)
#else
static void pack_names()
#endif
{
    register bucket *bp;
    register char *p, *s, *t;

    name_pool_size = sizeof("$end") + sizeof("$accept");
    for (bp = first_symbol; bp; bp = bp->next)
	name_pool_size += strlen(bp->name) + 1;
    name_pool = MALLOC(name_pool_size);

    strcpy(name_pool, "$accept");
    strcpy(name_pool + sizeof("$accept"), "$end");
    t = name_pool + sizeof("$end") + sizeof("$accept");
    for (bp = first_symbol; bp; bp = bp->next)
    {
	p = t;
	s = bp->name;
	while (*t++ = *s++) continue;
	FREE(bp->name);
	bp->name = p;
    }
}


#if __STDC__
static void check_symbols(void)
#else
static void check_symbols()
#endif
{
    register bucket *bp;

    if (goal->class == UNKNOWN)
	undefined_goal(goal->name);

    for (bp = first_symbol; bp; bp = bp->next)
    {
	if (bp->class == UNKNOWN)
	{
	    undefined_symbol_warning(bp->name);
	    bp->class = TERM;
	}
    }
}


#if __STDC__
static void pack_symbols(void)
#else
static void pack_symbols()
#endif
{
    register bucket *bp;
    register bucket **v;
    register int i, j, k, n;

    nsyms = 2;
    ntokens = 1;
    for (bp = first_symbol; bp; bp = bp->next)
    {
	++nsyms;
	if (bp->class == TERM) ++ntokens;
    }
    start_symbol = ntokens;
    nvars = nsyms - ntokens;

    symbol_name = (char **) MALLOC(nsyms*sizeof(char *));
    symbol_value = (short *) MALLOC(nsyms*sizeof(short));
    symbol_prec = (short *) MALLOC(nsyms*sizeof(short));
    symbol_assoc = MALLOC(nsyms);

    v = (bucket **) MALLOC(nsyms*sizeof(bucket *));

    v[0] = 0;
    v[start_symbol] = 0;

    i = 1;
    j = start_symbol + 1;
    for (bp = first_symbol; bp; bp = bp->next)
    {
	if (bp->class == TERM)
	    v[i++] = bp;
	else
	    v[j++] = bp;
    }
    assert(i == ntokens && j == nsyms);

    for (i = 1; i < ntokens; ++i)
	v[i]->index = i;

    goal->index = start_symbol + 1;
    k = start_symbol + 2;
    while (++i < nsyms)
	if (v[i] != goal)
	{
	    v[i]->index = k;
	    ++k;
	}

    goal->value = 0;
    k = 1;
    for (i = start_symbol + 1; i < nsyms; ++i)
    {
	if (v[i] != goal)
	{
	    v[i]->value = k;
	    ++k;
	}
    }

    k = 0;
    for (i = 1; i < ntokens; ++i)
    {
	n = v[i]->value;
	if (n > 256)
	{
	    for (j = k++; j > 0 && symbol_value[j-1] > n; --j)
		symbol_value[j] = symbol_value[j-1];
	    symbol_value[j] = n;
	}
    }

    if (v[1]->value == UNDEFINED)
	v[1]->value = 256;

    j = 0;
    n = 257;
    for (i = 2; i < ntokens; ++i)
    {
	if (v[i]->value == UNDEFINED)
	{
	    while (j < k && n == symbol_value[j])
	    {
		while (++j < k && n == symbol_value[j]) continue;
		++n;
	    }
	    v[i]->value = n;
	    ++n;
	}
    }

    symbol_name[0] = name_pool + 8;
    symbol_value[0] = 0;
    symbol_prec[0] = 0;
    symbol_assoc[0] = TOKEN;
    for (i = 1; i < ntokens; ++i)
    {
	symbol_name[i] = v[i]->name;
	symbol_value[i] = v[i]->value;
	symbol_prec[i] = v[i]->prec;
	symbol_assoc[i] = v[i]->assoc;
    }
    symbol_name[start_symbol] = name_pool;
    symbol_value[start_symbol] = -1;
    symbol_prec[start_symbol] = 0;
    symbol_assoc[start_symbol] = TOKEN;
    for (++i; i < nsyms; ++i)
    {
	k = v[i]->index;
	symbol_name[k] = v[i]->name;
	symbol_value[k] = v[i]->value;
	symbol_prec[k] = v[i]->prec;
	symbol_assoc[k] = v[i]->assoc;
    }

    FREE(v);
}


#if __STDC__
static void pack_grammar(void)
#else
static void pack_grammar()
#endif
{
    register int i, j;
    int assoc, prec;

    ritem = (short *) MALLOC(nitems*sizeof(short));
    rlhs = (short *) MALLOC(nrules*sizeof(short));
    rrhs = (short *) MALLOC((nrules+1)*sizeof(short));
    rprec = (short *) REALLOC(rprec, nrules*sizeof(short));
    rassoc = REALLOC(rassoc, nrules);

    ritem[0] = -1;
    ritem[1] = goal->index;
    ritem[2] = 0;
    ritem[3] = -2;
    rlhs[0] = 0;
    rlhs[1] = 0;
    rlhs[2] = start_symbol;
    rrhs[0] = 0;
    rrhs[1] = 0;
    rrhs[2] = 1;

    j = 4;
    for (i = 3; i < nrules; ++i)
    {
	rlhs[i] = plhs[i]->index;
	rrhs[i] = j;
	assoc = TOKEN;
	prec = 0;
	while (pitem[j])
	{
	    ritem[j] = pitem[j]->index;
	    if (pitem[j]->class == TERM)
	    {
		prec = pitem[j]->prec;
		assoc = pitem[j]->assoc;
	    }
	    ++j;
	}
	ritem[j] = -i;
	++j;
	if (rprec[i] == UNDEFINED)
	{
	    rprec[i] = prec;
	    rassoc[i] = assoc;
	}
    }
    rrhs[i] = j;

    FREE(plhs);
    FREE(pitem);
}


#if __STDC__
static void print_grammar(void)
#else
static void print_grammar()
#endif
{
    register int i, j, k;
    int spacing;
    register FILE *f = verbose_file;

    if (!vflag) return;

    k = 1;
    for (i = 2; i < nrules; ++i)
    {
	if (rlhs[i] != rlhs[i-1])
	{
	    if (i != 2) fprintf(f, "\n");
	    fprintf(f, "%4d  %s :", i - 2, symbol_name[rlhs[i]]);
	    spacing = strlen(symbol_name[rlhs[i]]) + 1;
	}
	else
	{
	    fprintf(f, "%4d  ", i - 2);
	    j = spacing;
	    while (--j >= 0) putc(' ', f);
	    putc('|', f);
	}

	while (ritem[k] >= 0)
	{
	    fprintf(f, " %s", symbol_name[ritem[k]]);
	    ++k;
	}
	++k;
	putc('\n', f);
    }
}


#if __STDC__
void reader(void)
#else
void reader()
#endif
{
    write_section(banner);
    create_symbol_table();
    read_declarations();
    read_grammar();
    free_symbol_table();
    free_tags();
    pack_names();
    check_symbols();
    pack_symbols();
    pack_grammar();
    free_symbols();
    print_grammar();
}
