#if __STDC__
#include <stdlib.h>

int main(int argc, char *argv[])
#else
int main(argc, argv)
int argc;
char *argv[];
#endif
{
#if __STDC__
    extern int yyparse(void);
#else
    extern int yyparse();
#endif

    (void) yyparse();
    exit(0);
}
