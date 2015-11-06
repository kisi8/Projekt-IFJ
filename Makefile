TESTSCANNER = scanner_test
SCANNER = scanner
FLAGS = -std=c99 -Wall -Werror -pedantic 
all: 
	@gcc $(FLAGS) $(TESTSCANNER).c $(SCANNER).c -o scanner_test
clean: 
	@rm $(TESTSCANNER)
	
