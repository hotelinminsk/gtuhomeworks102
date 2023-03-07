all: clean compile run

compile: main.c
		@echo "Compiling"
		@gcc -o test main.c
run:
	@echo "Running the program"
	./test
	@echo "Completed the program.."
clean: 
	@echo "Removing compiled files...."
	@rm -f *.o
	@rm -f test
	