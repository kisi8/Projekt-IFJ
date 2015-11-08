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

tToken get_token(FILE *source)
{
  // tato funkce bude vracet nacetny strukturu TOKEN (ukazatel na jeji zacatek)
  tToken token;
  int znak;
  
  do
    {
     znak = fgetc(source);
     
     if(znak==EOF){ token.lexeme = EOF_tk; break;}                     // pokud najdeme EOF, vrátíme token EOF_tk
     if(znak=='('){ token.lexeme = LR_BRACKET_tk; break;}              // (
     if(znak==')'){ token.lexeme = RR_BRACKET_tk; break;}              // )    
     if(znak=='{'){ token.lexeme = LC_BRACKET_tk; break;}              // {
     if(znak=='}'){ token.lexeme = RC_BRACKET_tk; break;}              // } 
     if(znak=='*'){ token.lexeme = MUL_tk,; break;}                    // *
     if(znak==';'){ token.lexeme = SEMICOLON_tk; break;}               // ;
     
     
     
     if(znak=='|')
       {
        znak = fgetc(source);
        if(znak=='|')
          { token.lexeme = OR_tk; break; }                             // dodefinovat operátor ||
        else
          { token.lexeme = ERROR_tk; break; }
       }            
     
     
     
     if(znak=='&')
       {
        znak = fgetc(source);
        if(znak=='&')
          { token.lexeme = AND_tk; break; }                            // dodefinovat operátor &&
        else
          { token.lexeme = ERROR_tk; break; }
       }            
     
     
     
     if(znak=='+')
       {
        znak = fgetc(source);
        if(znak=='+')
          { token.lexeme = INC_tk; break; }                            // ++
        else
          { ungetc(znak, source); token.lexeme = ADD_tk; break; }      // +
       }         
     
     
     
     if(znak=='-')
       {
        znak = fgetc(source);
        if(znak=='-')
          { token.lexeme = DEC_tk; break; }                            // --
        else
          { ungetc(znak, source); token.lexeme = SUB_tk; break; }      // -
       }  
       
       
       
     if(znak=='!')
       {
        znak = fgetc(source);
        if(znak=='=')
          { token.lexeme = NOTEQUAL_tk; break; }                       // !=
        else
          { ungetc(znak, source); token.lexeme = NOT_tk; break; }      // dodefinovat operátor !
       }         
       
       
       
     if(znak=='=')
       {
        znak = fgetc(source);
        if(znak=='=')
          { token.lexeme = EQUAL_tk; break; }                          // ==
        else
          { ungetc(znak, source); token.lexeme = ASSIGN_tk; break; }   // =
       }         
       
       
       
     if(znak=='<')
       {
        znak = fgetc(source);
        if(znak=='<')
          { token.lexeme = INPUT_tk; break; }                          // dodefinovat operátor cin <<
        else if(znak=='=')
          { token.lexeme = LESSEQUAL_tk; break; }                      // <=  
        else
          { ungetc(znak, source); token.lexeme = LESS_tk; break; }     // <
       }             
       
       
       
     if(znak=='>')
       {
        znak = fgetc(source);
        if(znak=='>')
          { token.lexeme = OUTPUT_tk; break; }                         // dodefinovat operátor cin >>
        else if(znak=='=')
          { token.lexeme = GREATEREQUAL_tk; break; }                   // >=  
        else
          { ungetc(znak, source); token.lexeme = GREATER_tk; break; }  // >
       }       
       
       
       
     if(znak=='/')
       {
        znak = fgetc(source);
        if(znak=='/')
          { do{ znak = fgetc(source);} while(znak != 10 || znak != 13); }         // jednoradkova poznamka // ... , ukonceno CR nebo LF
        else if(znak=='*')
          {  
           while(1)
             { 
              znak = fgetc(source);
              if(znak=='*')
                {
                 znak = fgetc(source);
                 if(znak=='/'){break;}
                 else {ungetc(znak, source);}
                }
             } 
          }                                                                        // viceradkovy komentar /* ... */  
        else
          { ungetc(znak, source); token.lexeme = DIV_tk; break; }                  // operator /
       }         
       
       
       
       
       
       
       
       
       
       
       
            
      
    } while(znak != EOF);  

  

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
        
        if(znak==EOF){ token.lexeme = EOF_tk; }                   // pokud najdeme EOF, vrátíme token EOF_tk
        
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
