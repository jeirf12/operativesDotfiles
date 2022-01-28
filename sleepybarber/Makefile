remove := rm
archives := test

ifeq ($(OS),Windows_NT)
	remove := del
	archives := test.exe
endif

all:
	@gcc sleepy_barber.c -pthread -o test

clean:
	@$(remove) $(archives)
