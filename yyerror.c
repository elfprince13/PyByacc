#include <stdio.h>

#if __STDC__
void yyerror(char *msg)
#else
void yyerror(msg)
char *msg;
#endif
{
    (void) fprintf(stderr, "%s\n", msg);
    return;
}
