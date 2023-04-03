all: clean compile run

compile: main.c part1.c  part2.c util.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test main.c part1.c part2.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "================================================================================="
	./test
	@echo "================================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.o
	@rm -f test