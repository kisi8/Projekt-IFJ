 /**
  * Par obecnych zasad pro vsechny co budou na lex. analyzatoru 
  * pracovat. Prosim komentujte (primerene ale ne zas malo) at se v tom ostatni
  * vyznaji. Dale jsem bych rekl ze by bylo mozna lepsi to psat
  * v anglictine (kod) a komentare v cestine/slovenstine. Aby z 
  * z toho nevzniknul HONZIK CODE ("while not NASEL.POMLUKUK") :D
  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>




// Typy lexikalnich jednotek nacitanych lexikalnim analyzatorem
typedef enum
{
  // Klicova slova (auto, cin, cout, if, else, for, bool, while, do, 
  // double, int, string, true, false, break, continue, return, and, or )
  AUTO_tk, CIN_tk, COUT_tk, IF_tk, ELSE_tk, FOR_tk, BOOL_tk, WHILE_tk, DO_tk, 
  DOUBLE_tk, INT_tk, STRING_tk, TRUE_tk, FALSE_tk, BREAK_tk, CONTINUE_tk, RETURN_tk,  
  AND_tk, OR_tk,

  // Identifikator
  ID_tk
    
  // Cislesna sekvence
  NUM_tk,

  // Relacni operatory (  !=  ==  <  >  >=  <=  )
  NOTEQUAL_tk, EQUAL_tk, LESS_tk, GREATER_tk, GREATEREQUAL_tk, LESSEQUAL_tk

  // Ostatni operatory (  =  +  -  *  /  ++  --  ;   )
  ASSIGN_tk, ADD_tk, SUB_tk, MUL_tk,  DIV_tk INC_tk, DEC_tk, SEMICOLON_tk, 
   
  // Zavorky (  (  )  {  } ) .......  LeftRoundBracket, RightRoundBracket, LeftCurlyBracket, RightCurlyBracket
  LR_BRACKET_tk, RR_BRACKET_tk, LC_BRACKET, RC_BRACKET,

  // Konec souboru
  EOF_tk,

  // Chyba tokenu?
  ERROR_tk          
   
  } tLexeme;


// Unie na ulozeni potrebnych tagu k tokenu
typedef union
{ 
   int num; // integer
   float dec_num; // desetine cislo
   char *string;  // retezec
} tNumber;


// Token = lexem s potrebnymi atributy
typedef struct
{
  tLexeme lexeme; // typ lexemu
  tNumber token_num; // hodnota lexemu (cislo, posloupnost znaku, )
  int line_num; // cislo radku kde byl dany lexem nalezen (bude se hodit pro debug programu)

  //int str[50]; // nalezeny lexem v nezmene podobe (cislo, identifikator ...)
} tToken;



tToken posli_token();

//--------------------------------------- MAIN ---------------------------




/**
 * Lexikalni Analyzator
 */
int main()
{

 FILE *zdrojak;
 if ((zdrojak = fopen("ifj.c", "r")) == NULL){ return 2; } // ERROR
        
 tToken token;
 
  do
   {    
    token = posli_token(zdrojak);
    printf("%d\n", token.lexem);
   } while(token.lexem != EOF_tk ) ;

 fclose(zdrojak);

return 0;
}

//--------------------------------------- FCE ---------------------------



tToken posli_token(FILE *zdrojak)
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



