# COMP20007 Design of Algorithms
# 2019 Semester 1
#
# Assignment 1 Makefile
# Created by Tobias Edwards <tobias.edwards@unimelb.edu.au>

CC     = gcc
CFLAGS = -Wall
EXE    = a1
OBJ    = main.o point.o deque.o convex-hull.o

# Default Target, so "$ make" or "$ make all" will do this
all: $(EXE)

# Create the executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# Other Dependencies
point.o: point.h point.c
	$(CC) $(CFLAGS) -c point.c
deque.o: deque.h deque.c
	$(CC) $(CFLAGS) -c deque.c
convex-hull.o: convex-hull.h convex-hull.c
	$(CC) $(CFLAGS) -c convex-hull.c

# TODO: Add any other dependencies you may create

# "clean" and "all" don't actually create files called "clean" and "all"
# and are thus "Phony Targets"
.PHONY: clean submit all

# Run "$ make clean" to remove the object and executable files
clean:
	rm -f $(OBJ) $(EXE)

# Run "$ make submit" to create submission.zip
submit: clean
	zip -r submission.zip .
