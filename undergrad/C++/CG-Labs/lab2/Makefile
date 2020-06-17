 TARGET = lab2
 
 OBJECTS = colour.o image.o imageio.o point.o vector.o raster.o lab2.o
 
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