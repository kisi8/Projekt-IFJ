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
  int znak;  /**< cteny znak */
  

     token.lexeme = -1;                                                                                        // výchozí hodnota porovnávání


    // Deleni | Preskoceni komentare | Preskoceni bilych znaku
    while(1){

      znak = fgetc(source);

      // Preskoceni bilych znaku
      while(isspace(znak) && znak != EOF)
        znak = fgetc(source);

      // Znak neni lomitko => nemuze to byt deleno ani komentar
      if(znak != '/') 
        break; 

      // Nalezeno lomitko
      else{
        znak = fgetc(source); // znak za lomitkem

        // Jednoradkovy komentar 
        if(znak == '/'){
          while (znak != '\n' && znak != EOF) // preskoceni jednoradkoveho komentare    
            znak = fgetc(source); 
          ungetc(znak, source); // vraceni znaku ktery nepatri do komentare
        }        
        // Viceradkovy komentar               
        else if(znak == '*'){  
          while(1){ // nacitam znaky dokud nenarazim na ukoncovaci sekvenci "*/" nebo EOF                                                                                               
            znak = fgetc(source);                                                              
            if(znak == EOF){ // dosel jsem nakonec souboru aniz byzch nasel "*/" => CHYBA
              token.lexeme = ERROR_tk;  
              return token;
            }   
            if(znak == '*'){ // nalezena hvezdicka (je to uk. sek?)
              znak = fgetc(source);
              if (znak == '/') // ukoncovaci sekvence vicerakoveho komentare
                break;
              if(znak == EOF){ // dosel jsem nakonec souboru aniz byzch nasel "*/" => CHYBA
                token.lexeme = ERROR_tk;  
                return token;
              }   
            }                                                 
          }
        } 
        // Znak deleno
        else { 
          ungetc(znak, source); 
          token.lexeme = DIV_tk; 
          return token; 
        }                                              
      } 
    }       

     // Test na zavorky
     if(znak=='('){ token.lexeme = LR_BRACKET_tk;  }                                                       // (
     else if(znak==')'){ token.lexeme = RR_BRACKET_tk;  }                                                      // )    
     else if(znak=='{'){ token.lexeme = LC_BRACKET_tk;  }                                                      // {
     else if(znak=='}'){ token.lexeme = RC_BRACKET_tk;  }                                                      // } 
     

     else if(znak=='*'){ token.lexeme = MUL_tk;  }                                                             // *
     else if(znak==';'){ token.lexeme = SEMICOLON_tk;  }                                                       // ;
     
     
    // Operator "or"
    else if(znak=='|')
       {
        znak = fgetc(source);
        if(znak=='|')
          { token.lexeme = OR_tk;   }                                                                     // ||
        else
          { token.lexeme = ERROR_tk;   }
       }            
     
     
     // Operator "and"
     else if(znak=='&')
       {
        znak = fgetc(source);
        if(znak=='&')
          { token.lexeme = AND_tk;   }                                                                    // &&
        else
          { token.lexeme = ERROR_tk;   }
       }            
     
     
     // Plus | PlusPlus
     else if(znak=='+')
       {
        znak = fgetc(source);
        if(znak=='+')
          { token.lexeme = INC_tk;   }                                                                    // ++
        else
          { ungetc(znak, source); token.lexeme = ADD_tk;   }                                              // +
       }         
     
     
     // Minus | MinusMinus
     else if(znak=='-')
       {
        znak = fgetc(source);
        if(znak=='-')
          { token.lexeme = DEC_tk;   }                                                                    // --
        else
          { ungetc(znak, source); token.lexeme = SUB_tk;   }                                              // -
       }  
       
       
     // Nerova se  
     else if(znak=='!')
       {
        znak = fgetc(source);
        if(znak=='=')
          { token.lexeme = NOTEQUAL_tk;   }                                                               // !=
        else
          { ungetc(znak, source); token.lexeme = NOT_tk;   }                                              // !
       }         
       
       
     // Rovno | Prirazeni   
     else if(znak=='=')
       {
        znak = fgetc(source);
        if(znak=='=')
          { token.lexeme = EQUAL_tk;   }                                                                  // ==
        else
          { ungetc(znak, source); token.lexeme = ASSIGN_tk;   }                                           // =
       }         
       
       
     // Nacitani vstupu | Mensi nebo rovno | Mensi 
     else if(znak=='<')
       {
        znak = fgetc(source);
        if(znak=='<')
          { token.lexeme = INPUT_tk;   }                                                                  //  <<
        else if(znak=='=')
          { token.lexeme = LESSEQUAL_tk;   }                                                              // <=  
        else
          { ungetc(znak, source); token.lexeme = LESS_tk;   }                                             // <
       }             
       
       
     // Vystup | Vetsi nebo rovno | Vetsi 
     else if(znak=='>')
       {
        znak = fgetc(source);
        if(znak=='>')
          { token.lexeme = OUTPUT_tk;   }                                                                 //  >>
        else if(znak=='=')
          { token.lexeme = GREATEREQUAL_tk;   }                                                           // >=  
        else
          { ungetc(znak, source); token.lexeme = GREATER_tk;   }                                          // >
       }       
       
       
       
   
       
       
     // Nacitani cisla
     else if( isdigit(znak) != 0 )                                                                                  // načítání INT
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
        if(token.lexeme==NUM_tk){ }
       }         
       
       
     // Nacitani retezce
     else if( isalpha(znak) != 0 || znak=='_')                                                                      // načítání ID, FCE a klíčových slov
       {                                                                                                       
        
        int alloc_counter = 10;
        
        tNumber value;
        value.string = (char *)malloc(alloc_counter*sizeof(char));
        if(value.string == NULL){ token.lexeme=FAILURE_tk;   }                                            // chyba malloc
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
                 if(value.string == NULL){ token.lexeme=FAILURE_tk;   }
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

        // Test na klicova slova  
          printf( "%s\n", value.string);   // for debugging only
         if(strcmp(value.string, "auto") == 0){ token.lexeme = AUTO_tk; free(value.string);   }            // detekce klíčových slov
        else if(strcmp(value.string, "cin") == 0){ token.lexeme = CIN_tk; free(value.string);   }
        else if(strcmp(value.string, "cout") == 0){ token.lexeme = COUT_tk; free(value.string);   }
        else if(strcmp(value.string, "if") == 0){ token.lexeme = IF_tk; free(value.string);   }
        else if(strcmp(value.string, "else") == 0){ token.lexeme = ELSE_tk; free(value.string);   }
        else if(strcmp(value.string, "for") == 0){ token.lexeme = FOR_tk; free(value.string);   }
        else if(strcmp(value.string, "bool") == 0){ token.lexeme = BOOL_tk; free(value.string);   }
        else if(strcmp(value.string, "while") == 0){ token.lexeme = WHILE_tk; free(value.string);   }
        else if(strcmp(value.string, "do") == 0){ token.lexeme = DO_tk; free(value.string);   }
        else if(strcmp(value.string, "double") == 0){ token.lexeme = DOUBLE_tk; free(value.string);   }
        else if(strcmp(value.string, "int") == 0){ token.lexeme = INT_tk; free(value.string);   }
        else if(strcmp(value.string, "string") == 0){ token.lexeme = STRING_tk; free(value.string);   }
        else if(strcmp(value.string, "true") == 0){ token.lexeme = TRUE_tk; free(value.string);   }
        else if(strcmp(value.string, "false") == 0){ token.lexeme = FALSE_tk; free(value.string);   }
        else if(strcmp(value.string, "break") == 0){ token.lexeme = BREAK_tk; free(value.string);   }
        else if(strcmp(value.string, "continue") == 0){ token.lexeme = CONTINUE_tk; free(value.string);   }
        else if(strcmp(value.string, "return") == 0){ token.lexeme = RETURN_tk; free(value.string);   } 

         
       }        
       
       
       
     // Retezcovy literal  
     else if( znak == '"' )                                                                                         // načítání  řetězců
       {                                                                                                       
        
        int alloc_counter = 10;
        
        tNumber value;
        value.string = (char *)malloc(alloc_counter*sizeof(char));
        if(value.string == NULL){ token.lexeme=FAILURE_tk;   }                                            // chyba malloc
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
                 if(value.string == NULL){ token.lexeme=FAILURE_tk;  break; }
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
         
       }               
       
      else  if(znak==EOF){ token.lexeme = EOF_tk; }             
      

  

  return token; 
}
