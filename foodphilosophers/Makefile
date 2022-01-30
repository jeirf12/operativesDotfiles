compiler := gcc
remove := rm -f
archives := test
ifeq ($(OS), Windows_NT)
	remove := del /q
	archives := test.exe
endif

all:
	@$(compiler) -o $(archives) foodphilosopher.c -pthread

run:
	@./$(archives)

clean:
	@$(remove) $(archives)
