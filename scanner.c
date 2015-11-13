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
#include <string.h>
#include "scanner.h"

tToken get_token(FILE *source)
{
  // tato funkce bude vracet nacetnou strukturu TOKEN
  tToken token;
  int znak;
  
  do
    {
     znak = fgetc(source);
     token.lexeme = -1;                                                                                        // výchozí hodnota porovnávání
     
     if(znak==EOF){ token.lexeme = EOF_tk; break;}                                                             // pokud najdeme EOF, vrátíme token EOF_tk
     if(isspace(znak)!=0){ continue;}                                                                          // bílé znaky
     if(znak=='('){ token.lexeme = LR_BRACKET_tk; break;}                                                      // (
     if(znak==')'){ token.lexeme = RR_BRACKET_tk; break;}                                                      // )    
     if(znak=='{'){ token.lexeme = LC_BRACKET_tk; break;}                                                      // {
     if(znak=='}'){ token.lexeme = RC_BRACKET_tk; break;}                                                      // } 
     if(znak=='*'){ token.lexeme = MUL_tk; break;}                                                             // *
     if(znak==';'){ token.lexeme = SEMICOLON_tk; break;}                                                       // ;
     
     
     
     if(znak=='|')
       {
        znak = fgetc(source);
        if(znak=='|')
          { token.lexeme = OR_tk; break; }                                                                     // ||
        else
          { token.lexeme = ERROR_tk; break; }
       }            
     
     
     
     if(znak=='&')
       {
        znak = fgetc(source);
        if(znak=='&')
          { token.lexeme = AND_tk; break; }                                                                    // &&
        else
          { token.lexeme = ERROR_tk; break; }
       }            
     
     
     
     if(znak=='+')
       {
        znak = fgetc(source);
        if(znak=='+')
          { token.lexeme = INC_tk; break; }                                                                    // ++
        else
          { ungetc(znak, source); token.lexeme = ADD_tk; break; }                                              // +
       }         
     
     
     
     if(znak=='-')
       {
        znak = fgetc(source);
        if(znak=='-')
          { token.lexeme = DEC_tk; break; }                                                                    // --
        else
          { ungetc(znak, source); token.lexeme = SUB_tk; break; }                                              // -
       }  
       
       
       
     if(znak=='!')
       {
        znak = fgetc(source);
        if(znak=='=')
          { token.lexeme = NOTEQUAL_tk; break; }                                                               // !=
        else
          { ungetc(znak, source); token.lexeme = NOT_tk; break; }                                              // !
       }         
       
       
       
     if(znak=='=')
       {
        znak = fgetc(source);
        if(znak=='=')
          { token.lexeme = EQUAL_tk; break; }                                                                  // ==
        else
          { ungetc(znak, source); token.lexeme = ASSIGN_tk; break; }                                           // =
       }         
       
       
       
     if(znak=='<')
       {
        znak = fgetc(source);
        if(znak=='<')
          { token.lexeme = INPUT_tk; break; }                                                                  //  <<
        else if(znak=='=')
          { token.lexeme = LESSEQUAL_tk; break; }                                                              // <=  
        else
          { ungetc(znak, source); token.lexeme = LESS_tk; break; }                                             // <
       }             
       
       
       
     if(znak=='>')
       {
        znak = fgetc(source);
        if(znak=='>')
          { token.lexeme = OUTPUT_tk; break; }                                                                 //  >>
        else if(znak=='=')
          { token.lexeme = GREATEREQUAL_tk; break; }                                                           // >=  
        else
          { ungetc(znak, source); token.lexeme = GREATER_tk; break; }                                          // >
       }       
       
       
       
     if(znak=='/')
       {
        znak = fgetc(source);
        if(znak=='/')
          { do{ znak = fgetc(source);} while(znak != 10 || znak != 13 || znak != EOF); }                       // jednoradkova poznamka // ... , ukonceno CR nebo LF
        else if(znak=='*')
          {  
           while(1)
             {                                                                                                 // viceradkovy komentar /* ... */
              znak = fgetc(source);                                                              
              if(znak==EOF){ token.lexeme = ERROR_tk; break;}                                                  // neukončený víceřádkový komentář
              if(znak=='*')
                {
                 znak = fgetc(source);
                 if(znak=='/'){break;}
                 else {ungetc(znak, source);}
                }
             }
          if(token.lexeme==EOF_tk){break;}    
          }                                                                          
        else                                                                                     
          { ungetc(znak, source); token.lexeme = DIV_tk; break; }                                              // operator /
       }         
       
       
       
     if( isdigit(znak) != 0 )                                                                                  // načítání INT
       {                                                                                                       // jak řešit dlouhá čísla, třeba o 50 cifrách?
        
        tNumber value_int;
        value_int.num = znak-48;     
        
        while(1)
          {
           znak = fgetc(source);
           if( isdigit(znak) != 0)
             {
              value_int.num *= 10;
              value_int.num += (znak-48);
             }
           else
             {
              ungetc(znak, source);
              token.lexeme = NUM_tk;
              token.token_num = value_int;
              break;
             }  
          }
        if(token.lexeme==NUM_tk){break;}
       }         
       
       
       
     if( isalpha(znak) != 0 || znak=='_')                                                                      // načítání ID, FCE a klíčových slov
       {                                                                                                       
        
        int alloc_counter = 10;
        
        tNumber value;
        value.string = (char *)malloc(alloc_counter*sizeof(char));
        if(value.string == NULL){ token.lexeme=FAILURE_tk; break; }                                            // chyba malloc
        int lenght = 1;
        
        *(value.string) = (char)znak;
        
        while(1)
          {
           znak = fgetc(source);
           if( isalnum(znak) != 0 || znak=='_')
             {
              if(lenght == alloc_counter-1 )
                {
                 alloc_counter *=2;
                 value.string = (char *)realloc(value.string, alloc_counter*sizeof(char));
                 if(value.string == NULL){ token.lexeme=FAILURE_tk; break; }
                }
              *(value.string + lenght*sizeof(char)) = (char)znak;
              lenght++;
             }
           else
             {
              ungetc(znak, source);
              token.lexeme = ID_tk;
              token.token_num = value;
              break;
             }  
          }
        // printf( "%s\n", value.string);   // for debugging only
        if(strcmp(value.string, "auto") == 0){ token.lexeme = AUTO_tk; free(value.string); break; }            // detekce klíčových slov
        if(strcmp(value.string, "cin") == 0){ token.lexeme = CIN_tk; free(value.string); break; }
        if(strcmp(value.string, "cout") == 0){ token.lexeme = COUT_tk; free(value.string); break; }
        if(strcmp(value.string, "if") == 0){ token.lexeme = IF_tk; free(value.string); break; }
        if(strcmp(value.string, "else") == 0){ token.lexeme = ELSE_tk; free(value.string); break; }
        if(strcmp(value.string, "for") == 0){ token.lexeme = FOR_tk; free(value.string); break; }
        if(strcmp(value.string, "bool") == 0){ token.lexeme = BOOL_tk; free(value.string); break; }
        if(strcmp(value.string, "while") == 0){ token.lexeme = WHILE_tk; free(value.string); break; }
        if(strcmp(value.string, "do") == 0){ token.lexeme = DO_tk; free(value.string); break; }
        if(strcmp(value.string, "double") == 0){ token.lexeme = DOUBLE_tk; free(value.string); break; }
        if(strcmp(value.string, "int") == 0){ token.lexeme = INT_tk; free(value.string); break; }
        if(strcmp(value.string, "string") == 0){ token.lexeme = STRING_tk; free(value.string); break; }
        if(strcmp(value.string, "true") == 0){ token.lexeme = TRUE_tk; free(value.string); break; }
        if(strcmp(value.string, "false") == 0){ token.lexeme = FALSE_tk; free(value.string); break; }
        if(strcmp(value.string, "break") == 0){ token.lexeme = BREAK_tk; free(value.string); break; }
        if(strcmp(value.string, "continue") == 0){ token.lexeme = CONTINUE_tk; free(value.string); break; }
        if(strcmp(value.string, "return") == 0){ token.lexeme = RETURN_tk; free(value.string); break; }

        break;
       }        
       
       
       
       
     if( znak == '"' )                                                                                         // načítání  řetězců
       {                                                                                                       
        
        int alloc_counter = 10;
        
        tNumber value;
        value.string = (char *)malloc(alloc_counter*sizeof(char));
        if(value.string == NULL){ token.lexeme=FAILURE_tk; break; }                                            // chyba malloc
        int lenght = 0;
        
        
        while(1)
          {
           znak = fgetc(source);
           if( znak != '"')
             {
              if(lenght == alloc_counter-1 )
                {
                 alloc_counter *=2;
                 value.string = (char *)realloc(value.string, alloc_counter*sizeof(char));
                 if(value.string == NULL){ token.lexeme=FAILURE_tk; break; }
                }
              *(value.string + lenght*sizeof(char)) = (char)znak;
              lenght++;
             }
           else
             {
              token.lexeme = STRING_tk;
              token.token_num = value;
              break;
             }  
          }
        break;
       }               
       
            
      
    } while(znak != EOF);  

  

  return token;
}
