all: clean compile run

compile: main.c util.c util.h
		@echo "Compiling"
		@gcc -o test main.c util.c -lm
run:
	@echo "Running the program"
	./test
	@echo "Completed the program.."
clean: 
	@echo "Removing compiled files...."
	@rm -f *.o
	@rm -f test
	