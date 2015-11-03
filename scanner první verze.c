#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum
  {
   AUTO_tk,          // oznaceni 0;
   CIN_tk,
   COUT_tk,
   DOUBLE_tk,
   ELSE_tk,
   FOR_tk,
   IF_tk,
   INT_tk,
   RETURN_tk,
   WHILE_tk,
   DO_tk,
   BOOL_tk,
   TRUE_tk,
   FALSE_tk,
   BREAK_tk,
   CONTINUE_tk,
   
   STRING_tk,
   
   OR_tk,
   AND_tk,
   PLUS_tk,
   INKREMENT_tk,
   MINUS_tk,
   DEKREMENT_tk,
   NOT_tk,
   NEROVNASE_tk,
   PRIRAZENI_tk,
   ROVNASE_tk,
   MENSI_tk,
   MENSIROVNO_tk,
   VYSTUP_tk,
   VETSI_tk,
   VETIROVNO_tk,
   VSTUP_tk,
   
   STREDNIK_tk,
   KRAT_tk,
   L_K_ZAVORKA_tk,
   R_K_ZAVORKA_tk,
   L_S_ZAVORKA_tk,
   R_S_ZAVORKA_tk,
   
   EOF_tk,
   ERROR_tk           // oznaceni 41;
   
  } tLexem;

typedef union
  {
   char id[50];
   int cislo;
   float des_cislo;
   char * ptr_retezec;
  } tHodnota;

typedef struct
  {
   tLexem lexem;
   tHodnota hodnota;
  } tToken;

tToken posli_token();

//--------------------------------------- MAIN ---------------------------

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



