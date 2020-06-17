# This is a sample of a GNU make file, all the major components are 
# commented, some example dummy files that include libraries and headers
# are provided so you can see how it all works.

# These are some variables; using variables makes writing a make file easier
# because you don't have to repeat things, just use the variables

# This is what the output binary file will be called
TARGET = lab0_compiling_c	

# Variables that specify different flags, the debug flag sets the compiler to
# to put debug information in the output files
DEBUG = -g 
CFLAGS = ${DEBUG}

# Specify a compiler
CC = gcc
# These are rules, or what will be produced when you compile your project
# you need to have the corresponding source files in the directory
OBJS = main.o apple.o pear.o banana.o 

# WHERE TO FIND CERTAIN HEADERS AND LIBS

# Linux
DIR_HEADERS = -I/usr/local/Mesa-6.1/include

# The libraries listed here are the ones you will need to get Glut and OpenGL working
LINK_LIBRARIES = -L /usr/X11R6/lib \
		 -L/usr/local/Mesa-6.1/lib \
		 -lglut -lGLU -lGL -lXmu -lXt -lSM -lICE -lXext -lX11 -lXi -lm 

#Linux compile
linux:	${OBJS}
	$(CC) -o ${TARGET} $(CFLAGS) $(DIR_HEADERS) ${OBJS} ${LINK_LIBRARIES}

nodebug: ${OBJS}
	$(CC) -o ${TARGET} $(DIR_HEADERS) ${OBJS} ${LINK_LIBRARIES}

clean:
	- rm *.o ${TARGET}

#SUFFIX RULES:  any file with one of these suffixes is significant
.SUFFIXES: .o .c

# SUFFIX RULE:  how to turn a .c file into a .o file
.c.o:	$(CC) -c $(CFLAGS) ${DIR_HEADERS} $*.c -o $*.o



