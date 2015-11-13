#ifndef _scanner_h
#define _scanner_h
  // Typy lexikalnich jednotek nacitanych lexikalnim analyzatorem
typedef enum
{
  // Klicova slova (auto, cin, cout, if, else, for, bool, while, do, 
  // double, int, string, true, false, break, continue, return, and, or )
  AUTO_tk, CIN_tk, COUT_tk, IF_tk, ELSE_tk, FOR_tk, BOOL_tk, WHILE_tk, DO_tk, 
  DOUBLE_tk, INT_tk, STRING_tk, TRUE_tk, FALSE_tk, BREAK_tk, CONTINUE_tk, RETURN_tk,  

  // Identifikator (posloupnost znaku zacinajicih pismenem nebo podrzitekm)
  ID_tk,
    
  // Cislesna sekvence
  NUM_tk, DECIMAL_tk,

  // Relacni operatory (  !=  ==  <  >  >=  <=  )
  NOTEQUAL_tk, EQUAL_tk, LESS_tk, GREATER_tk, GREATEREQUAL_tk, LESSEQUAL_tk,

  // Ostatni operatory (  =  +  -  *  /  ++  --  ;   )
  ASSIGN_tk, ADD_tk, SUB_tk, MUL_tk,  DIV_tk, INC_tk, DEC_tk, SEMICOLON_tk, 
   
  // Zavorky (  (  )  {  } ) .......  LeftRoundBracket, RightRoundBracket, LeftCurlyBracket, RightCurlyBracket
  LR_BRACKET_tk, RR_BRACKET_tk, LC_BRACKET_tk, RC_BRACKET_tk,

  // !      ||     &&      <<         >>
  NOT_tk, OR_tk, AND_tk, INPUT_tk, OUTPUT_tk,

  // Konec souboru
  EOF_tk,

  // Chyba lexikální analýzy
  ERROR_tk,          

  // Chyba programu (neúspěch malloc (); atd )
  FAILURE_tk  
   
  } tLexeme;


// Unie na ulozeni potrebnych tagu k tokenu
typedef union
{ 
   int num;       // integer
   float dec_num; // desetine cislo
   char *string;  // retezec
} tNumber;


// Token = lexem s potrebnymi atributy
typedef struct
{
  tLexeme lexeme;     // typ lexemu
  tNumber token_num;  // hodnota lexemu (cislo, posloupnost znaku, )
  int line_num;       // cislo radku kde byl dany lexem nalezen (bude se hodit pro debug programu)
} tToken;


tToken get_token(FILE *source);

#endif
