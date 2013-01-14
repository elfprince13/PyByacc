#if __STDC__ || defined(__cplusplus)
#define _P_(s) s
#else
#define _P_(s) ()
#endif

#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#if __STDC__
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

#ifdef _AMIGA
#define AMIGA
#endif

#endif

/*  machine-dependent definitions			*/
/*  the following definitions are for the Tahoe		*/
/*  they might have to be changed for other machines	*/

/*  MAXCHAR is the largest unsigned character value	*/
/*  MAXSHORT is the largest value of a C short		*/
/*  MINSHORT is the most negative value of a C short	*/
/*  MAXTABLE is the maximum table size			*/
/*  BITS_PER_WORD is the number of bits in a C unsigned	*/
/*  WORDSIZE computes the number of words needed to	*/
/*	store n bits					*/
/*  BIT returns the value of the n-th bit starting	*/
/*	from r (0-indexed)				*/
/*  SETBIT sets the n-th bit starting from r		*/

#ifdef AMIGA
#define MAXCHAR		UCHAR_MAX
#define	MAXSHORT	SHRT_MAX
#define MINSHORT	SHRT_MIN
#else
#define	MAXCHAR		255
#define	MAXSHORT	32767
#define MINSHORT	-32768
#endif
#define MAXTABLE	32500
#define BITS_PER_WORD	32
#define	WORDSIZE(n)	(((n)+(BITS_PER_WORD-1))/BITS_PER_WORD)
#define	BIT(r, n)	((((r)[(n)>>5])>>((n)&31))&1)
#define	SETBIT(r, n)	((r)[(n)>>5]|=((unsigned)1<<((n)&31)))


/*  character names  */

#define	NUL		'\0'	/*  the null character	*/
#define	NEWLINE		'\n'	/*  line feed  */
#define	SP		' '	/*  space  */
#define	BS		'\b'	/*  backspace  */
#define	HT		'\t'	/*  horizontal tab  */
#define	VT		'\013'	/*  vertical tab  */
#define	CR		'\r'	/*  carriage return  */
#define	FF		'\f'	/*  form feed  */
#define	QUOTE		'\''	/*  single quote  */
#define	DOUBLE_QUOTE	'\"'	/*  double quote  */
#define	BACKSLASH	'\\'	/*  backslash  */


/* defines for constructing filenames */

#define CODE_SUFFIX	0
#define DEFINES_SUFFIX	1
#define OUTPUT_SUFFIX	2
#define VERBOSE_SUFFIX	3


/* keyword codes */

#define TOKEN 0
#define LEFT 1
#define RIGHT 2
#define NONASSOC 3
#define MARK 4
#define TEXT 5
#define TYPE 6
#define START 7
#define UNION 8
#define IDENT 9


/*  symbol classes  */

#define UNKNOWN 0
#define TERM 1
#define NONTERM 2


/*  the undefined value	 */

#define UNDEFINED (-1)


/*  action codes  */

#define SHIFT 1
#define REDUCE 2


/*  character macros  */

#define IS_IDENT(c)	(isalnum(c) || (c) == '_' || (c) == '.' || (c) == '$')
#define	IS_OCTAL(c)	((c) >= '0' && (c) <= '7')
#define	NUMERIC_VALUE(c)	((c) - '0')


/*  symbol macros  */

#define ISTOKEN(s)	((s) < start_symbol)
#define ISVAR(s)	((s) >= start_symbol)


/*  storage allocation macros  */

#define CALLOC(k,n)	(my_calloc((unsigned)(k),(unsigned)(n)))
#define	FREE(x)		(free((char*)(x)))
#define MALLOC(n)	(my_malloc((unsigned)(n)))
#define	NEW(t)		((t*)allocate(sizeof(t)))
#define	NEW2(n,t)	((t*)allocate((unsigned)((n)*sizeof(t))))
#define REALLOC(p,n)	(my_realloc((char*)(p),(unsigned)(n)))


/*  the structure of a symbol table entry  */

typedef struct bucket bucket;
struct bucket
{
    struct bucket *link;
    struct bucket *next;
    char *name;
    char *tag;
    short value;
    short index;
    short prec;
    char class;
    char assoc;
};


/*  the structure of the LR(0) state machine  */

typedef struct core core;
struct core
{
    struct core *next;
    struct core *link;
    short number;
    short accessing_symbol;
    short nitems;
    short items[1];
};


/*  the structure used to record shifts	 */

typedef struct shifts shifts;
struct shifts
{
    struct shifts *next;
    short number;
    short nshifts;
    short shift[1];
};


/*  the structure used to store reductions  */

typedef struct reductions reductions;
struct reductions
{
    struct reductions *next;
    short number;
    short nreds;
    short rules[1];
};


/*  the structure used to represent parser actions  */

typedef struct action action;
struct action
{
    struct action *next;
    short symbol;
    short number;
    short prec;
    char action_code;
    char assoc;
    char suppressed;
};

/* target language is one of these */
typedef enum { C, PERL, PYTHON } Language;

/* global variables */

extern char dflag;
extern char lflag;
extern char rflag;
extern char tflag;
extern char vflag;

extern Language language;

extern char *myname;
extern char *cptr;
extern char *line;
extern int lineno;
extern int outline;

extern char **banner[];
extern char **tables[];
extern char **header[];
extern char **body[];
extern char **trailer[];

extern int  prefix_changed;
extern char *define_prefix;
extern char *symbol_prefix;

extern char *action_file_name;
extern char *code_file_name;
extern char *defines_file_name;
extern char *input_file_name;
extern char *output_file_name;
extern char *text_file_name;
extern char *union_file_name;
extern char *verbose_file_name;

extern FILE *action_file;
extern FILE *code_file;
extern FILE *defines_file;
extern FILE *input_file;
extern FILE *output_file;
extern FILE *text_file;
extern FILE *union_file;
extern FILE *verbose_file;

extern int nitems;
extern int nrules;
extern int nsyms;
extern int ntokens;
extern int nvars;
extern int ntags;

extern char unionized;
extern char line_format[];

extern int   start_symbol;
extern char  **symbol_name;
extern short *symbol_value;
extern short *symbol_prec;
extern char  *symbol_assoc;

extern short *ritem;
extern short *rlhs;
extern short *rrhs;
extern short *rprec;
extern char  *rassoc;

extern short **derives;
extern char *nullable;

extern bucket *first_symbol;
extern bucket *last_symbol;

extern int nstates;
extern core *first_state;
extern shifts *first_shift;
extern reductions *first_reduction;
extern short *accessing_symbol;
extern core **state_table;
extern shifts **shift_table;
extern reductions **reduction_table;
extern unsigned *LA;
extern short *LAruleno;
extern short *lookaheads;
extern short *goto_map;
extern short *from_state;
extern short *to_state;

extern action **parser;
extern int SRtotal;
extern int RRtotal;
extern short *SRconflicts;
extern short *RRconflicts;
extern short *defred;
extern short *rules_used;
extern short nunused;
extern short final_state;

/* global functions */

extern char *   allocate _P_((unsigned n));
extern void     closure _P_((short *nucleus, int n));
extern void     create_symbol_table _P_((void));
extern void     default_action_warning _P_((void));
extern void     dollar_error _P_((int a_lineno, char *a_line, char *a_cptr));
extern void     dollar_warning _P_((int a_lineno, int i));
extern void     done _P_((int k));
extern void     fatal _P_((char *msg));
extern void     finalize_closure _P_((void));
extern void     free_derives _P_((void));
extern void     free_nullable _P_((void));
extern void     free_parser _P_((void));
extern void     free_symbol_table _P_((void));
extern void     free_symbols _P_((void));
extern void     illegal_character _P_((char *c_cptr));
extern void     illegal_tag _P_((int t_lineno, char *t_line, char *t_cptr));
extern void     lalr _P_((void));
extern bucket * lookup _P_((char *name));
extern void     lr0 _P_((void));
extern bucket * make_bucket _P_((char *name));
extern void     make_parser _P_((void));
extern char *   my_calloc _P_((unsigned k, unsigned n));
extern char *   my_malloc _P_((unsigned n));
extern char *   my_realloc _P_((char *p, unsigned n));
extern void     no_grammar _P_((void));
extern void     no_space _P_((void));
extern void     open_error _P_((char *filename));
extern void     output _P_((void));
extern void     over_unionized _P_((char *u_cptr));
extern void     prec_redeclared _P_((void));
extern void     print_pos _P_((char *st_line, char *st_cptr));
extern void     reader _P_((void));
extern void     reflexive_transitive_closure _P_((unsigned *R, int n));
extern void     reprec_warning _P_((char *s));
extern void     restarted_warning _P_((void));
extern void     retyped_warning _P_((char *s));
extern void     revalued_warning _P_((char *s));
extern void     set_first_derives _P_((void));
extern void     syntax_error _P_((int st_lineno, char *st_line, char *st_cptr));
extern void     terminal_lhs _P_((int s_lineno));
extern void     terminal_start _P_((char *s));
extern void     tokenized_start _P_((char *s));
extern void     undefined_goal _P_((char *s));
extern void     undefined_symbol_warning _P_((char *s));
extern void     unexpected_EOF _P_((void));
extern void     unknown_rhs _P_((int i));
extern void     unterminated_action _P_((int a_lineno, char *a_line, char *a_cptr));
extern void     unterminated_comment _P_((int c_lineno, char *c_line, char *c_cptr));
extern void     unterminated_string _P_((int s_lineno, char *s_line, char *s_cptr));
extern void     unterminated_text _P_((int t_lineno, char *t_line, char *t_cptr));
extern void     unterminated_union _P_((int u_lineno, char *u_line, char *u_cptr));
extern void     untyped_lhs _P_((void));
extern void     untyped_rhs _P_((int i, char *s));
extern void     used_reserved _P_((char *s));
extern void     verbose _P_((void));
extern void     write_section _P_((char **section[]));

/* system variables */

extern int errno;


/* system functions */

#if __STDC__ != 1
extern void free();
extern char *strcpy();
extern char *strrchr();
#endif
