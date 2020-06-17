 TARGET = lab2
 
 OBJECTS = point.o vector.o matrix.o lab2.o
 
 CFLAGS = -Wall

 .SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) $(INCLUDE_DIRS) $(CFLAGS) -c $*.cpp

# target to compile the application
all:    $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)
clean:
	rm $(TARGET)
	rm $(OBJECTS)