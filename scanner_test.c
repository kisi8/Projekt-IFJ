/**
 * Test lexikalniho analyzatoru
 *
 * Test je zameren na to jestli byl rozpoznan spravny token
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"

#define numElem 42 // hh 42 btw. numElem = number of elemenets

int main()
{
  FILE *source;
  tToken token;

  source = fopen("scanner_zdrojak.txt","r");
  if (source==NULL){
    printf("%s\n", "Soubor neslo otevrit, pravdepodobne neexistuje" );
    return 1;
  }

  /*
  tLexeme table[numElem] = 
                    {// 0                                4                                 8
                     AUTO_tk, CIN_tk, COUT_tk, IF_tk, ELSE_tk, FOR_tk, BOOL_tk, WHILE_tk, DO_tk, 
                     // 9                                             14                                          18
                     DOUBLE_tk, INT_tk, STRING_tk, TRUE_tk, FALSE_tk, BREAK_tk, CONTINUE_tk, RETURN_tk,  AND_tk, OR_tk, 
                     // 19   20
                     ID_tk, ID_tk, 
                     // 21                                                          26
                     NOTEQUAL_tk, EQUAL_tk, LESS_tk, GREATER_tk, GREATEREQUAL_tk, LESSEQUAL_tk,
                     // 27                                                          34
                     ASSIGN_tk, ADD_tk, SUB_tk, MUL_tk,  DIV_tk, INC_tk, DEC_tk, SEMICOLON_tk, 
                     // 35                                        38
                     LR_BRACKET_tk, RR_BRACKET_tk, LC_BRACKET, RC_BRACKET,
                     // 39    40
                     NUM_tk, NUM_tk,
                     // 41
                     EOF_tk,
                    };

  for(int i=0; i < (numElem-1); i++){                                         // před použitím je třeba aktualizovat tabulku výše podle scanner.h
    token = get_token(source);                                                // 
    if(table[i] != token.lexeme)                                              // 
      printf("%s %d\n", "Chyba TOKENU na pozici", i );                        // 
  */
  
  do
    {    
     token = get_token(source);
     printf("%d\n", token.lexeme);
    } while(token.lexeme != EOF_tk ) ;


  
  
  printf("%s\n", "KONEC TESTU");

  fclose(source);
  return 0;
}
