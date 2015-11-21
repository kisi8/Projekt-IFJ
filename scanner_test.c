/**
 * Test lexikalniho analyzatoru
 *
 * Test je zameren na to jestli byl rozpoznan spravny token
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"


int main()
{
  FILE *source;
  tToken token;

  source = fopen("scanner_zdrojak.txt","r");
  if (source==NULL){
    printf("%s\n", "Soubor neslo otevrit, pravdepodobne neexistuje" );
    return 1;
  }

  
  do
    {    
     token = get_token(source);
     
     if(token.lexeme==NUM_tk)
       {
        printf("%d\t%d\n", token.lexeme, token.token_num.num); 
       }
     else if( token.lexeme == STRING_tk || token.lexeme == ID_tk )
       {
        printf("%d\t%s\n", token.lexeme, token.token_num.string);
       }  
    else if (token.lexeme == ERROR_tk){
         printf("%s\n", "Spatny token");
         return 1;
      }  
    else
       {
        printf("%d\n", token.lexeme);
       }
    } while(token.lexeme != EOF_tk ) ;


  
  
  printf("%s\n", "KONEC TESTU");

  fclose(source);
  return 0;
}
