# Nate Oates's makefile
#
# This command will "clean" out the directory of any output files
clean:
	rm *.exe

# This command will compile the source code when you run
# the make compile command at the command line prompt
compile:
	g++ project-1.cpp -o p1.exe -Wall

# This command will run the Project 1 Program
run:
	./p1.exe
