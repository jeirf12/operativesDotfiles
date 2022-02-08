compiler := gcc
remove := rm
archive1 := server
archive2 := client

ifeq ($OS, Windows_NT)
	remove := del
	archive1 := server.exe
	archive2 := client.exe
endif

all: 
	@$(compiler) -o $(archive1) server.c
	@$(compiler) -o $(archive2) client.c
run1:
	@./$(archive1)
run2:
	@./$(archive2)
clean:
	@$(remove) $(archive1) $(archive2)
