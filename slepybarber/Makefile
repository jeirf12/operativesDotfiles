ifeq ($(OS),Windows_NT)
	remove := del
	archives := test.exe
else
	remove := rm
	archives := test
endif

all:
	@gcc sleepy_barber.c -lpthread -o test

clean:
	@$(remove) $(archives)
