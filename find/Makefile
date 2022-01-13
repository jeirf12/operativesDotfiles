ifeq ($(OS),Windows_NT)
	remove := del
	archives := find.exe
else
	remove := rm
	archives := find
endif

all: 
	@gcc -o find find.c

clean:
	@$(remove) $(archives)
