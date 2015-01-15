MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
SUBMAKE   = ${MAKE} --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MAKEDEPS  = cc -MM

CHEADER   = List.h hashtable.h
CSOURCE   = test.c ${CHEADER:.h=.c}
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = test
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}


%.o : %.c
	${GCC} -c $<


lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES} ${DEPSFILE}


deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MAKEDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${SUBMAKE} deps

again :
	${MAKE} --no-print-directory spotless deps ci all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif
