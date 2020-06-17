TARGET = lab06

CC = g++

DEBUG = -g 
CFLAGS = ${DEBUG} 
OBJS = main.o Ball.o BallAux.o BallMath.o objects.o render.o texturePPM.o vector.o point.o

# WHERE TO FIND CERTAIN HEADERS AND LIBS

# Linux
DIR_HEADERS = \
	-I/usr/X11R6/include
LINK_LIBRARIES = -L /usr/X11R6/lib -L/usr/lib \
	-lglut32 -lglu32 -lopengl32 
#Linux compile
linux:	${OBJS}
	$(CC) -o ${TARGET} $(CFLAGS) $(DIR_HEADERS) ${OBJS} ${LINK_LIBRARIES}

clean:
	- rm core  *.o ${TARGET}

#SUFFIX RULES:  any file with one of these suffixes is significant
.SUFFIXES: .o .c .cpp

# SUFFIX RULE:  how to turn a .c file into a .o file
.cpp.c.o:
	$(CC) -c $(CFLAGS) ${DIR_HEADERS} $*.c -o $*.o



