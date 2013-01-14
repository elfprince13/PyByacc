# where to install program
DEST          = /usr/local/bin

# where to install library
LIB_DEST      = /usr/local/lib

HDRS          = defs.h

# uncomment the next line if your system does not have strrchr()
#RINDEX       = -Dstrrchr=rindex

# the name of the final executable
PROGRAM	      = byacc

LIBRARY       = libby.a

RANLIB        = ranlib
#RANLIB        = true

# set SIG_TYPE to the type of pointer signal() returns
SIG_TYPE      = void
#SIG_TYPE      = char

CPPFLAGS      = $(RINDEX) -DPROGRAM=\"$(PROGRAM)\" -DSIG_TYPE=$(SIG_TYPE)

CFLAGS	      = -g $(CPPFLAGS)

CC	      = gcc -Wall
CPP	      = /lib/cpp	      

LDFLAGS	      =

LIBS	      =

LINKER	      = $(CC)

MAKEFILE      = Makefile

OBJS	      =			\
		closure.o	\
		error.o		\
		lalr.o		\
		lr0.o		\
		main.o		\
		mkpar.o		\
		output.o	\
		reader.o	\
		skeleton.o	\
		symtab.o	\
		verbose.o	\
		warshall.o

LIB_OBJS      = yyerror.o	\
		yymain.o

PRINT	      = pr -f -l88

SRCS	      = closure.c	\
		error.c		\
		lalr.c		\
		lr0.c		\
		main.c		\
		mkpar.c		\
		output.c	\
		reader.c	\
		skeleton.c	\
		symtab.c	\
		verbose.c	\
		warshall.c

all:		$(PROGRAM) $(PROGRAM).man $(LIBRARY)

$(LIBRARY):	$(LIB_OBJS)
		ar rv $(LIBRARY) $(LIB_OBJS)
		$(RANLIB) $(LIBRARY)		

$(PROGRAM):     $(OBJS) $(LIBS)
		@echo -n "Loading $(PROGRAM) ... "
		@$(LINKER) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LIBS)
		@echo "done"

cc_src:
		#load $(RINDEX) -DPROGRAM="$(PROGRAM)" -DSIG_TYPE=$(SIG_TYPE) \
			$(SRCS)
		#link

clean:
		rm -f $(OBJS) $(LIB_OBJS) *~ core .purify* purify*
		rm -f $(MAKEFILE).bak

clobber:	clean
		rm -f $(PROGRAM) $(LIBRARY)

depend:		
		sed -n -e '1,/^### DO NOT DELETE THIS LINE/p' < $(MAKEFILE) \
		   | sed -e '/^### DO NOT DELETE THIS LINE/d' > $(MAKEFILE).new
		echo "### DO NOT DELETE THIS LINE - make depend needs it" >> $(MAKEFILE).new
		echo >> $(MAKEFILE).new
		for fl in $(SRCS) $(DEBUG_SRCS) ; \
		do \
		   $(CPP) $(CPPFLAGS) -M $$fl | grep -v ': /usr/include/' >> $(MAKEFILE).new ; \
		   echo >> $(MAKEFILE).new ; \
		done
		mv $(MAKEFILE) $(MAKEFILE).bak
		mv $(MAKEFILE).new $(MAKEFILE)

index:
		@ctags -wx $(HDRS) $(SRCS)

install:	$(PROGRAM) $(LIBRARY)
		@echo Installing $(PROGRAM) in $(DEST)
		@install -s $(PROGRAM) $(DEST)
		@echo Installing $(LIBRARY) in $(LIB_DEST)
		@cp $(LIBRARY) $(LIB_DEST)/$(LIBRARY)
		@$(RANLIB) $(LIB_DEST)/$(LIBRARY)

library:	$(LIBRARY)

listing:
		@$(PRINT) Makefile $(HDRS) $(SRCS) | lpr

lint:
		@lint $(CPPFLAGS) $(SRCS)

$(PROGRAM).man:	man.page $(MAKEFILE)
		sed -e "s/byacc/$(PROGRAM)/" \
		    -e "s/ BYACC/ `echo $(PROGRAM) | tr '[a-z]' '[A-Z]'`/" \
		    -e "s?LIB_DEST?$(LIB_DEST)?" \
		    -e "s/LIBRARY/$(LIBRARY)/" \
		    < man.page > $(PROGRAM).man

program:        $(PROGRAM)

purify:         $(OBJS) $(LIBS)
		@purify $(LINKER) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LIBS)

tags:           $(HDRS) $(SRCS)
		@ctags $(HDRS) $(SRCS)

tests:		$(PROGRAM)
		-mkdir t
		cp test/*.y test/Makefile t
		(cd t; $(MAKE) PROGRAM=$(PROGRAM))
		diff -r test t
		rm -fr t

### DO NOT DELETE THIS LINE - make depend needs it

closure.o: closure.c
closure.o: ./defs.h

error.o: error.c
error.o: ./defs.h

lalr.o: lalr.c
lalr.o: ./defs.h

lr0.o: lr0.c
lr0.o: ./defs.h

main.o: main.c
main.o: ./defs.h

mkpar.o: mkpar.c
mkpar.o: ./defs.h

output.o: output.c
output.o: ./defs.h

reader.o: reader.c
reader.o: ./defs.h

skeleton.o: skeleton.c
skeleton.o: ./defs.h

symtab.o: symtab.c
symtab.o: ./defs.h

verbose.o: verbose.c
verbose.o: ./defs.h

warshall.o: warshall.c
warshall.o: ./defs.h

