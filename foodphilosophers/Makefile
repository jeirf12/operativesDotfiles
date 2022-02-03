compiler := gcc
remove := rm
archives := test

ifeq ($(OS), Windows_NT)
	remove := del
	archives := test.exe
endif

all:
	@$(compiler) foodphilosopher.c -pthread -o $(archives)

run:
	@./$(archives)

clean:
	@$(remove) $(archives)
