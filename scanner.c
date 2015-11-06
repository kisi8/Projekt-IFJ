 /**
  * Par obecnych zasad pro vsechny co budou na lex. analyzatoru 
  * 1. Piste prosim slusne
  * 2. Piste prosim kod anglicky a kometare cesky/slovensky
  * 3. Komentujete kod!
  * 4. Nepouzivejte diakritiku v komentarich ani v nazvech souboru
  * 5. jmena souboru prosim oznacujte pokud mozno jednoslovne a bez mezer
  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"

tToken get_token()
{
  // tato funkce bude vracet nacetny strukturu TOKEN (ukazatel na jeji zacatek)

  
  tToken token;

  return token;


}


//--------------------------------------- FCE ---------------------------




/*tToken posli_token(FILE *zdrojak)
  {  
   tToken token;
   
    
    
    int znak;
     do
       {
        znak = fgetc(zdrojak);
        
        if(znak==EOF){ token.lexem = EOF_tk; }                   // pokud najdeme EOF, vrátíme token EOF_tk
        
        if(isalpha(znak) || znak=='_')                           // nedokoncena fce na nacitani identifikatoru
          {
           while(1)
             {
              if(isalnum(znak) || znak=='_')
             }     
          }
        
        
        
       } while(znak != EOF);

  
   return token;
  }

 */

