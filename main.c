#include "defs.h"
#include <signal.h>

#define VERSION "Berkeley yacc version 1.8.2 (C or perl)"

char dflag;
char lflag;
char rflag;
char tflag;
char vflag;

char *myname = PROGRAM;

char *file_prefix = "y";
char *temp_form;

int prefix_changed = 0;
char *define_prefix = "YY";
char *symbol_prefix = "yy";

Language language = C;
char* c_suffixes[] =    { ".code.c",  ".tab.h",  ".tab.c",  ".output" };
char* perl_suffixes[] = { ".code.pl", ".tab.ph", ".tab.pl", ".output" };
char* python_suffixes[] = { ".code.py", ".tab.ph", ".tab.py", ".output" };
char** suffixes = c_suffixes;

int lineno;
int outline;

char *action_file_name;
char *code_file_name;
char *defines_file_name;
char *input_file_name = "";
char *output_file_name;
char *text_file_name;
char *union_file_name;
char *verbose_file_name;

FILE *action_file;	/*  a temp file, used to save actions associated    */
			/*  with rules until the parser is written	    */
FILE *code_file;	/*  y.code.c (used when the -r option is specified) */
FILE *defines_file;	/*  y.tab.h					    */
FILE *input_file;	/*  the input file				    */
FILE *output_file;	/*  y.tab.c					    */
FILE *text_file;	/*  a temp file, used to save text until all	    */
			/*  symbols have been defined			    */
FILE *union_file;	/*  a temp file, used to save the union		    */
			/*  definition until all symbol have been	    */
			/*  defined					    */
FILE *verbose_file;	/*  y.output					    */

int nitems;
int nrules;
int nsyms;
int ntokens;
int nvars;

int   start_symbol;
char  **symbol_name;
short *symbol_value;
short *symbol_prec;
char  *symbol_assoc;

short *ritem;
short *rlhs;
short *rrhs;
short *rprec;
char  *rassoc;
short **derives;
char *nullable;

#ifdef AMIGA
long __near __STKNEED = 1000;
#endif

#if __STDC__
extern char *mktemp(char *template);
#else
extern char *mktemp();
#endif

#if __STDC__ != 1
extern char *getenv();
#endif

#if __STDC__
void done(int k)
#else
void done(k)
int k;
#endif
{
    if (action_file) { fclose(action_file); unlink(action_file_name); }
    if (text_file) { fclose(text_file); unlink(text_file_name); }
    if (union_file) { fclose(union_file); unlink(union_file_name); }
    exit(k);
}


#if __STDC__
static SIG_TYPE onintr(int junk)
#else
static SIG_TYPE onintr()
#endif
{
    done(1);
}


#if __STDC__
static void set_signals(void)
#else
static void set_signals()
#endif
{
#ifdef SIGINT
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	signal(SIGINT, onintr);
#endif
#ifdef SIGTERM
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
	signal(SIGTERM, onintr);
#endif
#ifdef SIGHUP
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
	signal(SIGHUP, onintr);
#endif
}


#if __STDC__
static void usage(void)
#else
static void usage()
#endif
{
    fprintf(stderr,
	    "usage: %s [-CPYcdlrtv] [-b file_prefix] [-p symbol_prefix] filename\n",
	    myname);
    exit(1);
}


#if __STDC__
static void getargs(int argc, char *argv[])
#else
static void getargs(argc, argv)
int argc;
char *argv[];
#endif
{
    register int i;
    register char *s;

    if (argc > 0) myname = argv[0];

    s = strrchr(myname, '/');
    if (s == (char *) NULL) {
#ifdef AMIGA
	s = strrchr(myname, ':');
	if (s == (char *) NULL)
	    s = myname;
	else
	    s++;
#else
	s = myname;
#endif
    }
    else
	s++;
    temp_form = MALLOC(strlen(s) + sizeof(".XXXXXXX"));
    sprintf(temp_form, "%s.XXXXXXX", s);

    for (i = 1; i < argc; ++i)
    {
	s = argv[i];
	if (*s != '-') break;
	switch (*++s)
	{
	case '\0':
	    input_file = stdin;
	    if (i + 1 < argc) usage();
	    return;

	case '-':
	    ++i;
	    goto no_more_options;

	case 'b':
	    if (*++s)
		 file_prefix = s;
	    else if (++i < argc)
		file_prefix = argv[i];
	    else
		usage();
	    continue;

	case 'c':
	case 'C':
	    language = C;
	    suffixes = c_suffixes;
	    break;

	case 'd':
	    dflag = 1;
	    break;

	case 'l':
	    lflag = 1;
	    break;

	case 'p':
	    if (*++s)
		 symbol_prefix = s;
	    else if (++i < argc)
		symbol_prefix = argv[i];
	    else
		usage();
	    continue;

	case 'Y':
        // printf( "Python\n" );
	    language = PYTHON;
	    suffixes = python_suffixes;
	    break;

	case 'P':
	    language = PERL;
	    suffixes = perl_suffixes;
	    break;

	case 'r':
	    rflag = 1;
	    break;

	case 't':
	    tflag = 1;
	    break;

	case 'v':
	    vflag = 1;
	    break;

	case 'V':
	    fprintf(stderr, "%s: %s\n", myname, VERSION);
	    exit(1);

	default:
	    usage();
	}

	for (;;)
	{
	    switch (*++s)
	    {
	    case '\0':
		goto end_of_option;

	    case 'c':
	    case 'C':
		language = C;
		suffixes = c_suffixes;
		break;

	    case 'd':
		dflag = 1;
		break;

	    case 'l':
		lflag = 1;
		break;

	    case 'Y':
	    language = PYTHON;
	    suffixes = python_suffixes;
	    break;

	    case 'P':
		language = PERL;
		suffixes = perl_suffixes;
		break;

	    case 'r':
		rflag = 1;
		break;

	    case 't':
		tflag = 1;
		break;

	    case 'v':
		vflag = 1;
		break;

	    case 'V':
		fprintf(stderr, "%s: %s\n", myname, VERSION);
		exit(1);

	    default:
		usage();
	    }
	}
end_of_option:;
    }

    if (((language == PERL) || (language == PYTHON)) && rflag)
	fprintf(stderr, "%s: Warning: -r not recommended with Perl or Python mode.\n",
		myname);

no_more_options:;
    if (i + 1 != argc) usage();
    input_file_name = argv[i];
}


#if __STDC__
char *allocate(unsigned n)
#else
char *allocate(n)
unsigned n;
#endif
{
    register char *p;

    p = NULL;
    if (n)
    {
	p = CALLOC(1, n);
    }
    return (p);
}


#if __STDC__
char *my_calloc(unsigned k, unsigned n)
#else
char *my_calloc(k, n)
unsigned k;
unsigned n;
#endif
{
#ifndef __STDC__
    extern char *calloc();
#endif
    register char *p;

    p = calloc(k, n);
    if (!p) no_space();
    return (p);
}


#if __STDC__
char *my_malloc(unsigned n)
#else
char *my_malloc(n)
unsigned n;
#endif
{
#ifndef __STDC__
    extern char *malloc();
#endif
    register char *p;

    p = malloc(n);
    if (!p) no_space();
    return (p);
}


#if __STDC__
char *my_realloc(char *p, unsigned n)
#else
char *my_realloc(p, n)
char *p;
unsigned n;
#endif
{
#ifndef __STDC__
    extern char *realloc();
#endif

    p = realloc(p, n);
    if (!p) no_space();
    return (p);
}
    

#if __STDC__
static void create_file_names(void)
#else
static void create_file_names()
#endif
{
    int i, len;
    char *tmpdir;

    tmpdir = getenv("TMPDIR");
#ifdef AMIGA
    if (tmpdir == (char *) NULL) tmpdir = "T:";
#else
    if (tmpdir == (char *) NULL) tmpdir = "/tmp";
#endif

    len = strlen(tmpdir);
    i = len + strlen(temp_form) + 1;
#ifdef AMIGA
    if (len && tmpdir[len-1] != ':' && tmpdir[len-1] != '/')
	++i;
#else
    if (len && tmpdir[len-1] != '/')
	++i;
#endif

    action_file_name = MALLOC(i);
    text_file_name = MALLOC(i);
    union_file_name = MALLOC(i);

    strcpy(action_file_name, tmpdir);
    strcpy(text_file_name, tmpdir);
    strcpy(union_file_name, tmpdir);

#ifdef AMIGA
    if (len && tmpdir[len-1] != ':' && tmpdir[len - 1] != '/') {
	action_file_name[len] = '/';
	text_file_name[len] = '/';
	union_file_name[len] = '/';
	++len;
    }
#else
    if (len && tmpdir[len - 1] != '/') {
	action_file_name[len] = '/';
	text_file_name[len] = '/';
	union_file_name[len] = '/';
	++len;
    }
#endif

    strcpy(action_file_name + len, temp_form);
    strcpy(text_file_name + len, temp_form);
    strcpy(union_file_name + len, temp_form);

    FREE(temp_form);
    temp_form = (char *) NULL;

    action_file_name[len + 5] = 'a';
    text_file_name[len + 5] = 't';
    union_file_name[len + 5] = 'u';

    mktemp(action_file_name);
    mktemp(text_file_name);
    mktemp(union_file_name);

    len = strlen(file_prefix);

    output_file_name = MALLOC(len + strlen(suffixes[OUTPUT_SUFFIX]) + 1);
    strcpy(output_file_name, file_prefix);
    strcpy(output_file_name + len, suffixes[OUTPUT_SUFFIX]);

    if (rflag)
    {
	code_file_name = MALLOC(len + strlen(suffixes[CODE_SUFFIX]) + 1);
	strcpy(code_file_name, file_prefix);
	strcpy(code_file_name + len, suffixes[CODE_SUFFIX]);
    }
    else
	code_file_name = output_file_name;

    if (dflag)
    {
	defines_file_name = MALLOC(len + strlen(suffixes[DEFINES_SUFFIX]) + 1);
	strcpy(defines_file_name, file_prefix);
	strcpy(defines_file_name + len, suffixes[DEFINES_SUFFIX]);
    }

    if (vflag)
    {
	verbose_file_name = MALLOC(len + strlen(suffixes[VERBOSE_SUFFIX]) + 1);
	strcpy(verbose_file_name, file_prefix);
	strcpy(verbose_file_name + len, suffixes[VERBOSE_SUFFIX]);
    }
}


#if __STDC__
static void open_files(void)
#else
static void open_files()
#endif
{
    create_file_names();

    if (input_file == 0)
    {
	input_file = fopen(input_file_name, "r");
	if (input_file == 0)
	    open_error(input_file_name);
    }

    action_file = fopen(action_file_name, "w");
    if (action_file == 0)
	open_error(action_file_name);

    text_file = fopen(text_file_name, "w");
    if (text_file == 0)
	open_error(text_file_name);

    if (vflag)
    {
	verbose_file = fopen(verbose_file_name, "w");
	if (verbose_file == 0)
	    open_error(verbose_file_name);
    }

    if (dflag)
    {
	defines_file = fopen(defines_file_name, "w");
	if (defines_file == 0)
	    open_error(defines_file_name);
	union_file = fopen(union_file_name, "w");
	if (union_file ==  0)
	    open_error(union_file_name);
    }

    output_file = fopen(output_file_name, "w");
    if (output_file == 0)
	open_error(output_file_name);

    if (rflag)
    {
	code_file = fopen(code_file_name, "w");
	if (code_file == 0)
	    open_error(code_file_name);
    }
    else
	code_file = output_file;
}


#if __STDC__
static void fix_defsym_prefix(void)
#else
static void fix_defsym_prefix()
#endif
{
    char *from;
    int num_lower = 0;
    char *to;

    if (strcmp(symbol_prefix, "yy") == 0)
	return;

    from = symbol_prefix;

    /* check first character for [A-Za-z_] */
    if (!isalpha(*from) && *from != '_') {
	fprintf(stderr,
		"%s: symbol prefix (%s) must start with an underline or letter\n",
		myname, symbol_prefix);
	exit(1);
    }

    for (/* void */ ; *from; from++) {
	if (isalnum(*from) || *from == '_') {
	    if (islower(*from))
		num_lower++;
	}
	else {
	    fprintf(stderr,
		    "%s: invalid character (%c) in symbol prefix (%s)\n",
		    myname, isgraph(*from) ? *from : '?', symbol_prefix);
	    exit(1);
	}
    }
    if (num_lower == 0) {
	fprintf(stderr,
		"%s: symbol prefix (%s) must contain at least 1 lower case character\n",
		myname, symbol_prefix);
	exit(1);
    }
    define_prefix = MALLOC((from - symbol_prefix) + 1);
    for (to = define_prefix, from = symbol_prefix; *from; from++) {
	if (islower(*from))
	    *to++ = toupper(*from);
	else
	    *to++ = *from;
    }
    *to = *from;
    prefix_changed = 1;
}

#if __STDC__
int main(int argc, char *argv[])
#else
int main(argc, argv)
int argc;
char *argv[];
#endif
{
    set_signals();
    getargs(argc, argv);
    fix_defsym_prefix();
    open_files();
    reader();
    lr0();
    lalr();
    make_parser();
    verbose();
    output();
    done(0);
    /*NOTREACHED*/
}
