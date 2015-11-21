TESTSCANNER = scanner_test
SCANNER = scanner
SYNTAX = syntax
FLAGS = -std=c99 -Wall -Werror -Wextra -pedantic 
all: 
	
test-scan:
	gcc $(FLAGS) $(TESTSCANNER).c $(SCANNER).c -o $(TESTSCANNER)
syntax: $(SYNTAX).c $(SCANNER).c
	gcc $(FLAGS) $(SYNTAX).c $(SCANNER).c -o $(SYNTAX)
clean: 
	-@rm $(TESTSCANNER) 2>/dev/null || true
	-@rm $(SYNTAX) 2>/dev/null || true
	
