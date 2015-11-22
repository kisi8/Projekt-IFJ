/*
 * Syntakticky analyzator - hlavni program
 * 
 * @author Karel Jiranek
 * @date 21. listopadu 2015
 * @breif Syntakticky analyzator vytvoreny v ramci projektu do predmetu IFJ, 
 *        na VUT FIT. Program ridi a provadi syntaktickou kontorlu a vola 
          prislusne funkce k overeni semanticke spravnosti. Dale zarucuje spravne
          volani intepretacnich funkci
*/ 

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

// Definice chyb
#define LEX_ERR        1 // chyba struktury tokenu
#define SYN_ERR        2 // chybna struktury programu
#define SEM_DEF_ERR    3 // nedefinovana funkce(promena), pokus o redefinici funkce(promene)
#define SEM_TYP_ERR    4 // chyba typove kontroly v aritmetickych retezcich, retezcovych  a relacnich vyrazech (+chybny pocet parametru pri volani funkce)
// #define
#define SEM_OTHER_ERR  5 // ostani sematicke chyby
#define RUN_IN_ERR     6 // behova chyba pri nacitani hodnotuy ze vstupu
#define RUN_UNDEF_ERR  7 // behova chyba pri praci s neinicializovanou promenou
#define RUN_DIV_ERR    8 // behova chyba deleni nulou
#define RUN_OTHER_ERR  9 // ostatni behove chyby
#define INTER_ERR      99 // interní chyba nevolivna vstup (chyba alokace, chyba otevirani souboru, spatne parametry prikaz. radky)

#define STACKMAX 100

// Precedencni tabulka (Pozn.: R..Relacni operator, I..Identifikator, O..||(or), A..&&(and))
const char precTable[10][10] = {//   +-   */     (     )    R      I    O     A    !     $  // tokeny
                     /*  +-  */ {  '>',  '<',  '<',  '>',  '>',  '<',  '>',  '>',  '>',  '>' }, 
                     /* * /  */ {  '>',  '>',  '<',  '>',  '>',  '<' , '>',  '>',  '>',  '>' },
                     /*  (   */ {  '>',  '>',  '>',  '=',  '>',  '>',  '>',  '>',  '>',  '!' },
                     /*  )   */ {  '>',  '>',  '!',  '>',  '>',  '!',  '>',  '>',  '!',  '>' },
                     /*  R   */ {  '>',  '>',  '>',  '<',  '<',  '>',  '>',  '>',  '<',  '>' },
                     /*  I   */ {  '>',  '>',  '!',  '>',  '>',  '!',  '>',  '>',  '>',  '!' },
                     /*  O   */ {  '<',  '<',  '<',  '>',  '<',  '<',  '>',  '<',  '<',  '>' },
                     /*  A   */ {  '<',  '<',  '<',  '>',  '<',  '<',  '>',  '>',  '<',  '>' },
                     /*  !   */ {  '<',  '<',  '<',  '!',  '<',  '<',  '>',  '>',  '>',  '>' },
                     /*  $   */ {  '<',  '<',  '<',  '!',  '<',  '<',  '<',  '<',  '<',  '!' }
                     /*  terminal
                      na zasobniku  */ };  

/* zasobnik pro prec. analyzu */
typedef struct {  
    int array[STACKMAX]; // zaobnik
    int top; // pocet prvku na zasobniku
} tStack;

 
int topStack(tStack *stack){
  return stack->array[stack->top];
}

void pushStack(tStack *stack, int inChar){
  if(stack->top == STACKMAX)
    printf("%s\n", "Doslo k pretecei zasobniku" );
  else{
    stack->top++;
    stack->array[stack->top] = inChar;
  }
}


/** tokenToIndex - prevede prijaty token na index do tabulky
 * @return Kladne hodnoty = indexy do tabulky | zaporne hodnoty jakozto errory
 */
int tokenToIndex(tToken token){
  if(token.lexeme == ERROR_tk) // chybna struktura tokenu
    return (-LEX_ERR);
  else if(token.lexeme == FAILURE_tk) // chyba neovlivnena vstupem
    return (-INTER_ERR);
  else{
    switch(token.lexeme){
    case ADD_tk: case SUB_tk: return 0; 
    case MUL_tk: case DIV_tk: return 1;
    case LR_BRACKET_tk:  return 2;
    case RR_BRACKET_tk:  return 3;
    case NOTEQUAL_tk: case EQUAL_tk: case LESS_tk: case GREATER_tk: case GREATEREQUAL_tk: case LESSEQUAL_tk: return 4;
    case ID_tk: return 5;
    case OR_tk: return 6;
    case AND_tk: return 7;
    case NOT_tk: return 8;
    case SEMICOLON_tk: return 9; // ukoncovaci znak prec analyzy (neco jako dolar)
    default: return (-SYN_ERR);
    }
  }
}

/** topToIndex - prevede vrchol zasobniku na index do tabulky
 * @return Kladne hodnoty = indexy do tabulky | zaporne hodnoty jakozto errory
 */
int topToIndex(tStack *stack){
  int topChar = topStack(stack);
  switch(topChar){
    case '+' : case '-': return 0;
    case '*' : case '/': return 1;
    case '(' : return 2;
    case ')' : return 3;
    case 'R' : return 4;
    case 'I' : return 5;
    case 'O' : return 6;
    case 'A' : return 7;
    case '!' : return 8;
    case '$' : return 9;
    default : return (-SYN_ERR);
  }
}


/** precAnalysis - funkce provede precedencni analyzu a vraci uspech nebo neupech
  * @return 
  */
int precAnalysis(tToken token){
  char rule; /**< vybrane pravidlo z tabulky, ktere se ma pouzit pri prec. analyze */
  int j; /**< index do tabulky ziskany prevodem tokenu na index */
  int i; /**< index do tabuly ziskany z nejvysiho terminalu na zasobniku */
  tStack stack; /**< zasobnik pro terminaly*/

  stack.top = 0; // inicializace zasobniku

  pushStack(&stack, '$'); // vlozeni ukoncovaciho terminalu na zasobnik

  while(1)
    if((i = topToIndex(&stack)) < 0)  // prepocet vrcholu zasobniku na idnex do tabulky
      return (-i);                    // nastala chyba, vratim kladny chyb kod (funkce vraci zaporny aby se odlisil index a chyba)
    if((j = tokenToIndex(token)) < 0) // prepocet tokenu na index do tabulky
      return (-j);                    // nastala chyba, vratim chyb. kod (fuknce vraci zaporny kod aby se odlisil index a chyba)

    rule = precTable[i][j]; // urceni pravidla podle ktereho se budeme nadale ridit
    if(rule == '<'){
    } 
    else if(rule == '>'){
      
    }
    else if(rule == '='){

    }
    else{

    }
  return 0;
}




int main(int argc, char **argv){
  FILE * sourceFIle; /**< cteny zdrojovy soubor */
  //tToken * token;  /**< nacteny token od lex. analyzatoru */

  if(argc != 2){ // overeni poctu parametru
    return INTER_ERR;
  }
  
  if((sourceFIle = fopen(*argv, "r")) == NULL){ // Soubor se nepodarilo otevrit
    return INTER_ERR;
  }

  // printf("%c\n", precTable[2][3]  ); // vytiskne rovnitko


}