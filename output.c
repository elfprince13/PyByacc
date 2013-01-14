#include "defs.h"

static int nvectors;
static int nentries;
static short **froms;
static short **tos;
static short *tally;
static short *width;
static short *state_count;
static short *order;
static short *base;
static short *pos;
static int maxtable;
static short *table;
static short *check;
static int lowzero;
static int high;


static void free_itemsets _P_((void));
static void free_shifts _P_((void));
static void free_reductions _P_((void));
static void output_stored_text _P_((void));
static void output_defines _P_((void));
static void write_num _P_((int value));
static void start_num_array _P_((char *name, int indent, int first));
static void start_string_array _P_((char *name, int nl));
static void end_num_array _P_((void));
static void end_string_array _P_((int nl));
static void start_define _P_((FILE *file));
static void end_define _P_((FILE *file, int value));
static void write_define _P_((char *name, int value));
static void write_null _P_((void));
static void output_rule_data _P_((void));
static void output_yydefred _P_((void));
static void output_actions _P_((void));
static void token_actions _P_((void));
static void goto_actions _P_((void));
static int default_goto _P_((int symbol));
static void save_column _P_((int symbol, int default_state));
static void sort_actions _P_((void));
static void pack_table _P_((void));
static int matching_vector _P_((int vector));
static int pack_vector _P_((int vector));
static void output_base _P_((void));
static void output_table _P_((void));
static void output_check _P_((void));
static int is_C_identifier _P_((char *name));
static void output_debug _P_((void));
static void output_stype _P_((void));
static void output_trailing_text _P_((void));
static void output_semantic_actions _P_((void));


#if __STDC__
void output(void)
#else
void output()
#endif
{
    free_itemsets();
    free_shifts();
    free_reductions();
    output_stored_text();
    output_defines();
    output_rule_data();
    output_yydefred();
    output_actions();
    free_parser();
    output_debug();
    output_stype();
    if (rflag) write_section(tables);
    write_section(header);
    if (language == C)
	output_trailing_text();
    write_section(body);
    output_semantic_actions();
    write_section(trailer);
    if ((language == PERL) || (language == PYTHON))
	output_trailing_text();
    free_derives();
    free_nullable();
}


#if __STDC__
static void write_num(int value)
#else
static void write_num(value)
int value;
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(output_file, "%5d,", value);
	break;
    case PERL:
	fprintf(output_file, "%5d,", value);
	break;
    case C:
	fprintf(output_file, "%5d,", value);
	break;
    }
}

#if __STDC__
static void start_num_array(char *name, int indent, int first)
#else
static void start_num_array(name, indent, first)
char *name;
int indent, first;
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(output_file, "%s%s = [%*d,",
		symbol_prefix, name, indent+7, first);
	break;
    case PERL:
	fprintf(output_file, "@%s%s = (%*d,",
		symbol_prefix, name, indent+7, first);
	break;
    case C:
	fprintf(output_file, "short %s%s[] = {%*d,",
		symbol_prefix, name, indent, first);
	break;
    }
}

#if __STDC__
static void start_string_array(char *name, int nl)
#else
static void start_string_array(name, nl)
char *name;
int nl;
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(output_file, "%s%s = [%s",
		symbol_prefix, name, nl ? "\n" : "");
	break;
    case PERL:
	fprintf(output_file, "@%s%s = (%s",
		symbol_prefix, name, nl ? "\n" : "");
	break;
    case C:
	fprintf(output_file, "char *%s%s[] = {%s",
		symbol_prefix, name, nl ? "\n": "");
	break;
    }
}

#if __STDC_
static void end_num_array(void)
#else
static void end_num_array()
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(output_file, "\n]\n");
	break;
    case PERL:
	fprintf(output_file, "\n);\n");
	break;
    case C:
	fprintf(output_file, "\n};\n");
	break;
    }
}

#if __STDC__
static void end_string_array(int nl)
#else
static void end_string_array(nl)
int nl;
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(output_file, "%s]\n", nl ? "\n" : "");
	break;
    case PERL:
	fprintf(output_file, "%s);\n", nl ? "\n" : "");
	break;
    case C:
	fprintf(output_file, "%s};\n", nl ? "\n" : "");
	break;
    }
}

#if __STDC__
static void start_define(FILE *file)
#else
static void start_define(file)
FILE *file;
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(file, "");
	break;
    case PERL:
	fprintf(file, "$");
	break;
    case C:
	fprintf(file, "#define ");
	break;
    }
}

#if __STDC__
static void end_define(FILE *file, int value)
#else
static void end_define(file, value)
FILE* file;
int value;
#endif
{
    if (language == PYTHON)
	fprintf(file, "=%d\n", value);
    else if (language == PERL)
	fprintf(file, "=%d;\n", value);
    else
	fprintf(file, " %d\n", value);
}

#if __STDC_
static void write_define(char *name, int value)
#else
static void write_define(name, value)
char* name;
int value;
#endif
{
    start_define(code_file);
    fprintf(code_file, "%s%s", define_prefix, name);
    end_define(code_file, value);
}

#if __STDC_
static void write_null(void)
#else
static void write_null()
#endif
{
    switch (language)
    {
    case PYTHON:
	fprintf(output_file, "0,");
	break;
    case PERL:
	fprintf(output_file, "'',");
	break;
    case C:
	fprintf(output_file, "0,");
	break;
    }
}

#if __STDC__
static void output_rule_data(void)
#else
static void output_rule_data()
#endif
{
    register int i;
    register int j;

  
    start_num_array("lhs", 42, symbol_value[start_symbol]);

    j = 10;
    for (i = 3; i < nrules; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	write_num(symbol_value[rlhs[i]]);
    }
    if (!rflag) outline += 2;
    end_num_array();
  
    start_num_array("len", 42, 2);

    j = 10;
    for (i = 3; i < nrules; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	  j++;

	write_num(rrhs[i + 1] - rrhs[i] - 1);
    }
    if (!rflag) outline += 2;
    end_num_array();
}


#if __STDC__
static void output_yydefred(void)
#else
static void output_yydefred()
#endif
{
    register int i, j;

    start_num_array("defred", 39,
		    (defred[0] ? defred[0] - 2 : 0));

    j = 10;
    for (i = 1; i < nstates; i++)
    {
	if (j < 10)
	    ++j;
	else
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}

	write_num(defred[i] ? defred[i] - 2 : 0);
    }

    if (!rflag) outline += 2;
    end_num_array();
}


#if __STDC__
static void output_actions(void)
#else
static void output_actions()
#endif
{
    nvectors = 2*nstates + nvars;

    froms = NEW2(nvectors, short *);
    tos = NEW2(nvectors, short *);
    tally = NEW2(nvectors, short);
    width = NEW2(nvectors, short);

    token_actions();
    FREE(lookaheads);
    FREE(LA);
    FREE(LAruleno);
    FREE(accessing_symbol);

    goto_actions();
    FREE(goto_map + ntokens);
    FREE(from_state);
    FREE(to_state);

    sort_actions();
    pack_table();
    output_base();
    output_table();
    output_check();
}


#if __STDC__
static void token_actions(void)
#else
static void token_actions()
#endif
{
    register int i, j;
    register int shiftcount, reducecount;
    register int max, min;
    register short *actionrow, *r, *s;
    register action *p;

    actionrow = NEW2(2*ntokens, short);
    for (i = 0; i < nstates; ++i)
    {
	if (parser[i])
	{
	    for (j = 0; j < 2*ntokens; ++j)
	    actionrow[j] = 0;

	    shiftcount = 0;
	    reducecount = 0;
	    for (p = parser[i]; p; p = p->next)
	    {
		if (p->suppressed == 0)
		{
		    if (p->action_code == SHIFT)
		    {
			++shiftcount;
			actionrow[p->symbol] = p->number;
		    }
		    else if (p->action_code == REDUCE && p->number != defred[i])
		    {
			++reducecount;
			actionrow[p->symbol + ntokens] = p->number;
		    }
		}
	    }

	    tally[i] = shiftcount;
	    tally[nstates+i] = reducecount;
	    width[i] = 0;
	    width[nstates+i] = 0;
	    if (shiftcount > 0)
	    {
		froms[i] = r = NEW2(shiftcount, short);
		tos[i] = s = NEW2(shiftcount, short);
		min = MAXSHORT;
		max = 0;
		for (j = 0; j < ntokens; ++j)
		{
		    if (actionrow[j])
		    {
			if (min > symbol_value[j])
			    min = symbol_value[j];
			if (max < symbol_value[j])
			    max = symbol_value[j];
			*r++ = symbol_value[j];
			*s++ = actionrow[j];
		    }
		}
		width[i] = max - min + 1;
	    }
	    if (reducecount > 0)
	    {
		froms[nstates+i] = r = NEW2(reducecount, short);
		tos[nstates+i] = s = NEW2(reducecount, short);
		min = MAXSHORT;
		max = 0;
		for (j = 0; j < ntokens; ++j)
		{
		    if (actionrow[ntokens+j])
		    {
			if (min > symbol_value[j])
			    min = symbol_value[j];
			if (max < symbol_value[j])
			    max = symbol_value[j];
			*r++ = symbol_value[j];
			*s++ = actionrow[ntokens+j] - 2;
		    }
		}
		width[nstates+i] = max - min + 1;
	    }
	}
    }
    FREE(actionrow);
}

#if __STDC__
static void goto_actions(void)
#else
static void goto_actions()
#endif
{
    register int i, j, k;

    state_count = NEW2(nstates, short);

    k = default_goto(start_symbol + 1);
    start_num_array("dgoto", 40, k);
    save_column(start_symbol + 1, k);

    j = 10;
    for (i = start_symbol + 2; i < nsyms; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	k = default_goto(i);
	write_num(k);
	save_column(i, k);
    }

    if (!rflag) outline += 2;
    end_num_array();
    FREE(state_count);
}

#if __STDC__
static int default_goto(int symbol)
#else
static int default_goto(symbol)
int symbol;
#endif
{
    register int i;
    register int m;
    register int n;
    register int default_state;
    register int max;

    m = goto_map[symbol];
    n = goto_map[symbol + 1];

    if (m == n) return (0);

    for (i = 0; i < nstates; i++)
	state_count[i] = 0;

    for (i = m; i < n; i++)
	state_count[to_state[i]]++;

    max = 0;
    default_state = 0;
    for (i = 0; i < nstates; i++)
    {
	if (state_count[i] > max)
	{
	    max = state_count[i];
	    default_state = i;
	}
    }

    return (default_state);
}


#if __STDC__
static void save_column(int symbol, int default_state)
#else
static void save_column(symbol, default_state)
int symbol;
int default_state;
#endif
{
    register int i;
    register int m;
    register int n;
    register short *sp;
    register short *sp1;
    register short *sp2;
    register int count;
    register int symno;

    m = goto_map[symbol];
    n = goto_map[symbol + 1];

    count = 0;
    for (i = m; i < n; i++)
    {
	if (to_state[i] != default_state)
	    ++count;
    }
    if (count == 0) return;

    symno = symbol_value[symbol] + 2*nstates;

    froms[symno] = sp1 = sp = NEW2(count, short);
    tos[symno] = sp2 = NEW2(count, short);

    for (i = m; i < n; i++)
    {
	if (to_state[i] != default_state)
	{
	    *sp1++ = from_state[i];
	    *sp2++ = to_state[i];
	}
    }

    tally[symno] = count;
    width[symno] = sp1[-1] - sp[0] + 1;
}

#if __STDC__
static void sort_actions(void)
#else
static void sort_actions()
#endif
{
  register int i;
  register int j;
  register int k;
  register int t;
  register int w;

  order = NEW2(nvectors, short);
  nentries = 0;

  for (i = 0; i < nvectors; i++)
    {
      if (tally[i] > 0)
	{
	  t = tally[i];
	  w = width[i];
	  j = nentries - 1;

	  while (j >= 0 && (width[order[j]] < w))
	    j--;

	  while (j >= 0 && (width[order[j]] == w) && (tally[order[j]] < t))
	    j--;

	  for (k = nentries - 1; k > j; k--)
	    order[k + 1] = order[k];

	  order[j + 1] = i;
	  nentries++;
	}
    }
}


#if __STDC__
static void pack_table(void)
#else
static void pack_table()
#endif
{
    register int i;
    register int place;
    register int state;

    base = NEW2(nvectors, short);
    pos = NEW2(nentries, short);

    maxtable = 1000;
    table = NEW2(maxtable, short);
    check = NEW2(maxtable, short);

    lowzero = 0;
    high = 0;

    for (i = 0; i < maxtable; i++)
	check[i] = -1;

    for (i = 0; i < nentries; i++)
    {
	state = matching_vector(i);

	if (state < 0)
	    place = pack_vector(i);
	else
	    place = base[state];

	pos[i] = place;
	base[order[i]] = place;
    }

    for (i = 0; i < nvectors; i++)
    {
	if (froms[i])
	    FREE(froms[i]);
	if (tos[i])
	    FREE(tos[i]);
    }

    FREE(froms);
    FREE(tos);
    FREE(pos);
}


/*  The function matching_vector determines if the vector specified by	*/
/*  the input parameter matches a previously considered	vector.	 The	*/
/*  test at the start of the function checks if the vector represents	*/
/*  a row of shifts over terminal symbols or a row of reductions, or a	*/
/*  column of shifts over a nonterminal symbol.	 Berkeley Yacc does not	*/
/*  check if a column of shifts over a nonterminal symbols matches a	*/
/*  previously considered vector.  Because of the nature of LR parsing	*/
/*  tables, no two columns can match.  Therefore, the only possible	*/
/*  match would be between a row and a column.	Such matches are	*/
/*  unlikely.  Therefore, to save time, no attempt is made to see if a	*/
/*  column matches a previously considered vector.			*/
/*									*/
/*  Matching_vector is poorly designed.	 The test could easily be made	*/
/*  faster.  Also, it depends on the vectors being in a specific	*/
/*  order.								*/

#if __STDC__
static int matching_vector(int vector)
#else
static int matching_vector(vector)
int vector;
#endif
{
    register int i;
    register int j;
    register int k;
    register int t;
    register int w;
    register int match;
    register int prev;

    i = order[vector];
    if (i >= 2*nstates)
	return (-1);

    t = tally[i];
    w = width[i];

    for (prev = vector - 1; prev >= 0; prev--)
    {
	j = order[prev];
	if (width[j] != w || tally[j] != t)
	    return (-1);

	match = 1;
	for (k = 0; match && k < t; k++)
	{
	    if (tos[j][k] != tos[i][k] || froms[j][k] != froms[i][k])
		match = 0;
	}

	if (match)
	    return (j);
    }

    return (-1);
}



#if __STDC__
static int pack_vector(int vector)
#else
static int pack_vector(vector)
int vector;
#endif
{
    register int i, j, k, l;
    register int t;
    register int loc;
    register int ok;
    register short *from;
    register short *to;
    int newmax;

    i = order[vector];
    t = tally[i];
    assert(t);

    from = froms[i];
    to = tos[i];

    j = lowzero - from[0];
    for (k = 1; k < t; ++k)
	if (lowzero - from[k] > j)
	    j = lowzero - from[k];
    for (;; ++j)
    {
	if (j == 0)
	    continue;
	ok = 1;
	for (k = 0; ok && k < t; k++)
	{
	    loc = j + from[k];
	    if (loc >= maxtable)
	    {
		if (loc >= MAXTABLE)
		    fatal("maximum table size exceeded");

		newmax = maxtable;
		do { newmax += 200; } while (newmax <= loc);
		table = (short *) REALLOC(table, newmax*sizeof(short));
		check = (short *) REALLOC(check, newmax*sizeof(short));
		for (l	= maxtable; l < newmax; ++l)
		{
		    table[l] = 0;
		    check[l] = -1;
		}
		maxtable = newmax;
	    }

	    if (check[loc] != -1)
		ok = 0;
	}
	for (k = 0; ok && k < vector; k++)
	{
	    if (pos[k] == j)
		ok = 0;
	}
	if (ok)
	{
	    for (k = 0; k < t; k++)
	    {
		loc = j + from[k];
		table[loc] = to[k];
		check[loc] = from[k];
		if (loc > high) high = loc;
	    }

	    while (check[lowzero] != -1)
		++lowzero;

	    return (j);
	}
    }
}



#if __STDC__
static void output_base(void)
#else
static void output_base()
#endif
{
    register int i, j;

    start_num_array("sindex", 39, base[0]);

    j = 10;
    for (i = 1; i < nstates; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	write_num(base[i]);
    }

    if (!rflag) outline += 2;
    end_num_array();

    start_num_array("rindex", 39, base[nstates]);

    j = 10;
    for (i = nstates + 1; i < 2*nstates; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	write_num(base[i]);
    }

    if (!rflag) outline += 2;
    end_num_array();
  
    start_num_array("gindex", 39, base[2*nstates]);

    j = 10;
    for (i = 2*nstates + 1; i < nvectors - 1; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	write_num(base[i]);
    }

    if (!rflag) outline += 2;
    end_num_array();
    FREE(base);
}



#if __STDC__
static void output_table(void)
#else
static void output_table()
#endif
{
    register int i;
    register int j;

    ++outline;
    write_define("TABLESIZE", high);
    start_num_array("table", 40, table[0]);

    j = 10;
    for (i = 1; i <= high; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	write_num(table[i]);
    }

    if (!rflag) outline += 2;
    end_num_array();
    FREE(table);
}



#if __STDC__
static void output_check(void)
#else
static void output_check()
#endif
{
    register int i;
    register int j;

    start_num_array("check", 40, check[0]);

    j = 10;
    for (i = 1; i <= high; i++)
    {
	if (j >= 10)
	{
	    if (!rflag) ++outline;
	    putc('\n', output_file);
	    j = 1;
	}
	else
	    ++j;

	write_num(check[i]);
    }

    if (!rflag) outline += 2;
    end_num_array();
    FREE(check);
}


#if __STDC__
static int is_C_identifier(char *name)
#else
static int is_C_identifier(name)
char *name;
#endif
{
    register char *s;
    register int c;

    s = name;
    c = *s;
    if (c == '"')
    {
	c = *++s;
	if (!isalpha(c) && c != '_' && c != '$')
	    return (0);
	else if (language==PERL && c == '$')
	    return (0);
	while ((c = *++s) != '"')
	{
	    if (!isalnum(c) && c != '_' && c != '$')
		return (0);
	    else if (language==PERL && c == '$')
		return (0);
	}
	return (1);
    }

    if (!isalpha(c) && c != '_' && c != '$')
	return (0);
    else if (language==PERL && c == '$')
	return (0);
    while (c = *++s)
    {
	if (!isalnum(c) && c != '_' && c != '$')
	    return (0);
	else if (language==PERL && c == '$')
	    return (0);
    }
    return (1);
}


#if __STDC__
static void output_defines(void)
#else
static void output_defines()
#endif
{
    register int c, i;
    register char *s;

    for (i = 2; i < ntokens; ++i)
    {
	s = symbol_name[i];
	if (is_C_identifier(s))
	{
	    start_define(code_file);
	    if (dflag)
		start_define(defines_file);
	    c = *s;
	    if (c == '"')
	    {
		while ((c = *++s) != '"')
		{
		    putc(c, code_file);
		    if (dflag) putc(c, defines_file);
		}
	    }
	    else
	    {
		do
		{
		    putc(c, code_file);
		    if (dflag) putc(c, defines_file);
		}
		while (c = *++s);
	    }
	    ++outline;
	    end_define(code_file, symbol_value[i]);
	    if (dflag)
		end_define(defines_file, symbol_value[i]);
	}
    }

    ++outline;
    write_define("ERRCODE", symbol_value[1]);

    if (dflag && unionized && language == C)
    {
	fclose(union_file);
	union_file = fopen(union_file_name, "r");
	if (union_file == NULL) open_error(union_file_name);
	while ((c = getc(union_file)) != EOF)
	    putc(c, defines_file);
	fprintf(defines_file, " %sSTYPE;\nextern %sSTYPE %slval;\n",
		define_prefix, define_prefix, symbol_prefix);
    }
}


#if __STDC__
static void output_stored_text(void)
#else
static void output_stored_text()
#endif
{
    register int c;
    register FILE *in, *out;

    fclose(text_file);
    text_file = fopen(text_file_name, "r");
    if (text_file == NULL)
	open_error(text_file_name);
    in = text_file;
    if ((c = getc(in)) == EOF)
	return;
    out = code_file;
    if (c ==  '\n')
	++outline;
    putc(c, out);
    while ((c = getc(in)) != EOF)
    {
	if (c == '\n')
	    ++outline;
	putc(c, out);
    }
    if (!lflag)
	fprintf(out, line_format, ++outline + 1, code_file_name);
}


#if __STDC__
static void output_debug(void)
#else
static void output_debug()
#endif
{
    register int i, j, k, max;
    char **symnam, *s;

    ++outline;
    write_define("FINAL", final_state);
    outline += 3;
    fprintf(code_file, "#ifndef %sDEBUG\n#define %sDEBUG %d\n#endif\n",
	    define_prefix, define_prefix, tflag);
    if (rflag)
	fprintf(output_file, "#ifndef %sDEBUG\n#define %sDEBUG %d\n#endif\n",
		define_prefix, define_prefix, tflag);

    max = 0;
    for (i = 2; i < ntokens; ++i)
	if (symbol_value[i] > max)
	    max = symbol_value[i];
    ++outline;
    write_define("MAXTOKEN", max);

    symnam = (char **) MALLOC((max+1)*sizeof(char *));

    /* Note that it is	not necessary to initialize the element		*/
    /* symnam[max].							*/
    for (i = 0; i < max; ++i)
	symnam[i] = 0;
    for (i = ntokens - 1; i >= 2; --i)
	symnam[symbol_value[i]] = symbol_name[i];
    symnam[0] = "end-of-file";

    if (!rflag) ++outline;
    fprintf(output_file, "#if %sDEBUG\n", define_prefix);
    start_string_array("name", 0);
    j = 80;
    for (i = 0; i <= max; ++i)
    {
	if (s = symnam[i])
	{
	    if (s[0] == '"')
	    {
		k = 7;
		while (*++s != '"')
		{
		    ++k;
		    if (*s == '\\')
		    {
			k += 2;
			if (*++s == '\\')
			    ++k;
		    }
		}
		j += k;
		if (j > 80)
		{
		    if (!rflag) ++outline;
		    putc('\n', output_file);
		    j = k;
		}
		fprintf(output_file, "\"\\\"");
		s = symnam[i];
		while (*++s != '"')
		{
		    if (*s == '\\')
		    {
			fprintf(output_file, "\\\\");
			if (*++s == '\\')
			    fprintf(output_file, "\\\\");
			else
			    putc(*s, output_file);
		    }
		    else
			putc(*s, output_file);
		}
		fprintf(output_file, "\\\"\",");
	    }
	    else if (s[0] == '\'')
	    {
		if (s[1] == '"')
		{
		    j += 7;
		    if (j > 80)
		    {
			if (!rflag) ++outline;
			putc('\n', output_file);
			j = 7;
		    }
		    fprintf(output_file, "\"'\\\"'\",");
		}
		else
		{
		    k = 5;
		    while (*++s != '\'')
		    {
			++k;
			if (*s == '\\')
			{
			    k += 2;
			    if (*++s == '\\')
				++k;
			}
		    }
		    j += k;
		    if (j > 80)
		    {
			if (!rflag) ++outline;
			putc('\n', output_file);
			j = k;
		    }
		    fprintf(output_file, "\"'");
		    s = symnam[i];
		    while (*++s != '\'')
		    {
			if (*s == '\\')
			{
			    fprintf(output_file, "\\\\");
			    if (*++s == '\\')
				fprintf(output_file, "\\\\");
			    else
				putc(*s, output_file);
			}
			else
			    putc(*s, output_file);
		    }
		    fprintf(output_file, "'\",");
		}
	    }
	    else
	    {
		k = strlen(s) + 3;
		j += k;
		if (j > 80)
		{
		    if (!rflag) ++outline;
		    putc('\n', output_file);
		    j = k;
		}
		putc('"', output_file);
		do { putc(*s, output_file); } while (*++s);
		fprintf(output_file, "\",");
	    }
	}
	else
	{
	    j += 2;
	    if (j > 80)
	    {
		if (!rflag) ++outline;
		putc('\n', output_file);
		j = 2;
	    }
	    write_null();
	}
    }
    if (!rflag) outline += 2;
    end_string_array(1);
    FREE(symnam);

    if (!rflag) ++outline;
    start_string_array("rule", 1);
    for (i = 2; i < nrules; ++i)
    {
	if (language == PERL && symbol_name[rlhs[i]][0] == '$')
	    fprintf(output_file, "\"\\%s :", symbol_name[rlhs[i]]);
	else
	    fprintf(output_file, "\"%s :", symbol_name[rlhs[i]]);
	for (j = rrhs[i]; ritem[j] > 0; ++j)
	{
	    s = symbol_name[ritem[j]];
	    if (s[0] == '"')
	    {
		fprintf(output_file, " \\\"");
		while (*++s != '"')
		{
		    if (*s == '\\')
		    {
			if (s[1] == '\\')
			    fprintf(output_file, "\\\\\\\\");
			else
			    fprintf(output_file, "\\\\%c", s[1]);
			++s;
		    }
		    else
			putc(*s, output_file);
		}
		fprintf(output_file, "\\\"");
	    }
	    else if (s[0] == '\'')
	    {
		if (s[1] == '"')
		    fprintf(output_file, " '\\\"'");
		else if (s[1] == '\\')
		{
		    if (s[2] == '\\')
			fprintf(output_file, " '\\\\\\\\");
		    else
			fprintf(output_file, " '\\\\%c", s[2]);
		    s += 2;
		    while (*++s != '\'')
			putc(*s, output_file);
		    putc('\'', output_file);
		}
		else
		    fprintf(output_file, " '%c'", s[1]);
	    }
	    else
		fprintf(output_file, " %s", s);
	}
	if (!rflag) ++outline;
	fprintf(output_file, "\",\n");
    }

    if (!rflag) outline += 2;
    end_string_array(0);
    fprintf(output_file, "#endif\n");
}


#if __STDC__
static void output_stype(void)
#else
static void output_stype()
#endif
{
    if (!unionized && ntags == 0 && language == C)
    {
	outline += 3;
	fprintf(code_file, "#ifndef %sSTYPE\ntypedef int %sSTYPE;\n#endif\n",
		define_prefix, define_prefix);
    }
}


#if __STDC__
static void output_trailing_text(void)
#else
static void output_trailing_text()
#endif
{
    register int c, last;
    register FILE *in, *out;

    if (line == 0)
	return;

    in = input_file;
    out = code_file;
    c = *cptr;
    if (c == '\n')
    {
	++lineno;
	if ((c = getc(in)) == EOF)
	    return;
	if (!lflag)
	{
	    ++outline;
	    fprintf(out, line_format, lineno, input_file_name);
	}
	if (c == '\n')
	    ++outline;
	putc(c, out);
	last = c;
    }
    else
    {
	if (!lflag)
	{
	    ++outline;
	    fprintf(out, line_format, lineno, input_file_name);
	}
	do { putc(c, out); } while ((c = *++cptr) != '\n');
	++outline;
	putc('\n', out);
	last = '\n';
    }

    while ((c = getc(in)) != EOF)
    {
	if (c == '\n')
	    ++outline;
	putc(c, out);
	last = c;
    }

    if (last != '\n')
    {
	++outline;
	putc('\n', out);
    }
    if (!lflag)
	fprintf(out, line_format, ++outline + 1, code_file_name);
}


#if __STDC__
static void output_semantic_actions(void)
#else
static void output_semantic_actions()
#endif
{
    register int c, last;
    register FILE *out;

    fclose(action_file);
    action_file = fopen(action_file_name, "r");
    if (action_file == NULL)
	open_error(action_file_name);

    if ((c = getc(action_file)) == EOF)
	return;

    out = code_file;
    last = c;
    if (c == '\n')
	++outline;
    putc(c, out);
    while ((c = getc(action_file)) != EOF)
    {
	if (c == '\n')
	    ++outline;
	putc(c, out);
	last = c;
    }

    if (last != '\n')
    {
	++outline;
	putc('\n', out);
    }

    if (!lflag)
	fprintf(out, line_format, ++outline + 1, code_file_name);
}


#if __STDC__
static void free_itemsets(void)
#else
static void free_itemsets()
#endif
{
    register core *cp, *next;

    FREE(state_table);
    for (cp = first_state; cp; cp = next)
    {
	next = cp->next;
	FREE(cp);
    }
}


#if __STDC__
static void free_shifts(void)
#else
static void free_shifts()
#endif
{
    register shifts *sp, *next;

    FREE(shift_table);
    for (sp = first_shift; sp; sp = next)
    {
	next = sp->next;
	FREE(sp);
    }
}



#if __STDC__
static void free_reductions(void)
#else
static void free_reductions()
#endif
{
    register reductions *rp, *next;

    FREE(reduction_table);
    for (rp = first_reduction; rp; rp = next)
    {
	next = rp->next;
	FREE(rp);
    }
}
