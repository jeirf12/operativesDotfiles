compiler := gcc
remove := rm
archives := find

ifeq ($(OS),Windows_NT)
	remove := del
	archives := find.exe
endif

all: 
	@$(compiler) -o $(archives) find.c

run:
	@./$(archives)

clean:
	@$(remove) $(archives)
