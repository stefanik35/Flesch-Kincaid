#
# PROGRAM:    fleschKincaid
# PROGRAMMER: Andrew Stefanik
# LOGON ID:   z1753812
# DATE DUE:   10/18/2015
#

# Compiler variables
CCFLAGS = -ansi -Wall

# Rule to link object code files to create executable file
fleschKincaid.exe: fleschKincaid.o
	g++ $(CCFLAGS) -o fleschKincaid.exe fleschKincaid.o

# Rules to compile source code files to object code
fleschKincaid.o: fleschKincaid.cpp
	g++ $(CCFLAGS) -c fleschKincaid.cpp

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o *.exe
