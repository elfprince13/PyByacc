#include <exec/types.h>
#include <exec/tasks.h>
#include <dos/dos.h>
#include <proto/dos.h>
#include <proto/exec.h>

char *mktemp(char *	template)
{
    char		letter = 'A';
    BPTR		lock;
    unsigned long	mytask;
    char *		xptr;


    if (template == (char *) NULL || *template == '\0')
	return (char *) NULL;

    for (xptr = template; *xptr != '\0'; xptr++)
	/* void */ ;
    if (*--xptr != 'X')
	return (char *) NULL;

    mytask = (unsigned long) FindTask((STRPTR) NULL);

    do {
	*xptr = (mytask % 10) + '0';
	mytask /= 10;
    } while (xptr != template && *--xptr == 'X');

    if (*xptr == 'X') {
	while (xptr != template && *xptr == 'X')
	    xptr--;
	if (*xptr != 'X')
	    xptr++;
	*xptr = letter;
    }
    else {
	xptr++;
	letter--;
    }

    for (;;) {
	lock = Lock(template, SHARED_LOCK);

	if (lock == (BPTR) NULL) {
	    if (IoErr() == ERROR_OBJECT_NOT_FOUND)
		return template;
	}
	UnLock(lock);

	if (letter < 'Z')
	    letter++;
	else {
	    if (*++xptr == '\0')
		return (char *) NULL;
	    letter = 'A';
	}
	*xptr = letter;
    }

    /*NOTREACHED*/
}
