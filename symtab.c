#include "defs.h"


/* TABLE_SIZE is the number of entries in the symbol table. */
/* TABLE_SIZE must be a power of two.			    */

#define	TABLE_SIZE 1024


bucket **symbol_table;
bucket *first_symbol;
bucket *last_symbol;


#if __STDC__
static int hash(char *name)
#else
static int hash(name)
char *name;
#endif
{
    register char *s;
    register int c, k;

    assert(name != (char *) NULL && *name);
    s = name;
    k = *s;
    while (c = *++s)
	k = (31*k + c) & (TABLE_SIZE - 1);

    return (k);
}


#if __STDC__
bucket *make_bucket(char *name)
#else
bucket *make_bucket(name)
char *name;
#endif
{
    register bucket *bp;

    assert(name != (char *) NULL);
    bp = (bucket *) MALLOC(sizeof(bucket));
    bp->link = 0;
    bp->next = 0;
    bp->name = MALLOC(strlen(name) + 1);
    bp->tag = 0;
    bp->value = UNDEFINED;
    bp->index = 0;
    bp->prec = 0;
    bp-> class = UNKNOWN;
    bp->assoc = TOKEN;

    strcpy(bp->name, name);

    return (bp);
}


#if __STDC__
bucket *lookup(char *name)
#else
bucket *lookup(name)
char *name;
#endif
{
    register bucket *bp, **bpp;

    bpp = symbol_table + hash(name);
    bp = *bpp;

    while (bp)
    {
	if (strcmp(name, bp->name) == 0) return (bp);
	bpp = &bp->link;
	bp = *bpp;
    }

    *bpp = bp = make_bucket(name);
    last_symbol->next = bp;
    last_symbol = bp;

    return (bp);
}


#if __STDC__
void create_symbol_table(void)
#else
void create_symbol_table()
#endif
{
    register int i;
    register bucket *bp;

    symbol_table = (bucket **) MALLOC(TABLE_SIZE*sizeof(bucket *));
    for (i = 0; i < TABLE_SIZE; i++)
	symbol_table[i] = 0;

    bp = make_bucket("error");
    bp->index = 1;
    bp->class = TERM;

    first_symbol = bp;
    last_symbol = bp;
    symbol_table[hash("error")] = bp;
}


#if __STDC__
void free_symbol_table(void)
#else
void free_symbol_table()
#endif
{
    FREE(symbol_table);
    symbol_table = 0;
}


#if __STDC__
void free_symbols(void)
#else
void free_symbols()
#endif
{
    register bucket *p, *q;

    for (p = first_symbol; p; p = q)
    {
	q = p->next;
	FREE(p);
    }
}
