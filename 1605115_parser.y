%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include <bits/stdc++.h>
#define YYSTYPE SymbolInfo*
#include "1605115_symboltable.cpp"


using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;

int line_no = 1; 

FILE *fp;
ofstream logfile;
ofstream errorfile;

SymbolTable symbolTable(10);


void yyerror(char *s)
{
	//write your code
}

void addLineNoLog() {
	logfile <<"At line no: " << line_no << " ";
	
}

SymbolInfo* deepCopySymbolInfo(SymbolInfo* oldCopy) {
	SymbolInfo* ret = new SymbolInfo(oldCopy->getName(), oldCopy->getType());
	return ret; 
}

%}

%token IF ELSE FOR WHILE DO BREAK
%token INT FLOAT CHAR DOUBLE VOID
%token RETURN SWITCH CASE DEFAULT CONTINUE
%token CONST_INT CONST_FLOAT CONST_CHAR
%token ADDOP MULOP INCOP RELOP ASSIGNOP LOGICOP BITOP NOT DECOP
%token LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token STRING ID PRINTLN
//todo Ensure this stuff has right associativity. Or atleast that you can explain its associativity. 
%left RELOP LOGICOP BITOP 
%left ADDOP 
%left MULOP

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE



%%

start : program
	{
		//write your code in this block in all the similar blocks below
	}
	;

program : program unit 
	| unit
	;
	
unit : var_declaration { addLineNoLog(); }
     | func_declaration { addLineNoLog(); }
     | func_definition { addLineNoLog(); }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON { addLineNoLog(); }
		| type_specifier ID LPAREN RPAREN SEMICOLON { addLineNoLog(); }
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
		| type_specifier ID LPAREN RPAREN compound_statement
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		| parameter_list COMMA type_specifier
 		| type_specifier ID
		| type_specifier
 		;

 		
compound_statement : LCURL statements RCURL
 		    | LCURL RCURL
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
 		 ;
 		 
type_specifier	: INT
 		| FLOAT
 		| VOID
 		;
 		
declaration_list : declaration_list COMMA ID
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
 		  | ID
 		  | ID LTHIRD CONST_INT RTHIRD
 		  ;
 		  
statements : statement
	   | statements statement
	   ;
	   
statement : var_declaration
	  | expression_statement
	  | compound_statement
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	  | IF LPAREN expression RPAREN statement ELSE statement
	  | WHILE LPAREN expression RPAREN statement
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  | RETURN expression SEMICOLON
	  ;
	  
expression_statement 	: SEMICOLON			
			| expression SEMICOLON 
			;
	  
variable : ID	{
				$$ = new SymbolInfo($1->getName(), "variable");
				$$->addChildSymbol($1);
				addLineNoLog();
				 logfile << "variable : ID" << endl << endl;
				 logfile << $1->getName() << endl << endl; 
				}

	 | ID LTHIRD expression RTHIRD {
		 
	 }
	 ;
	 
expression : logic_expression	
	   | variable ASSIGNOP logic_expression 	
	   ;
			
logic_expression : rel_expression 	
		 | rel_expression LOGICOP rel_expression 	
		 ;
			
rel_expression	: simple_expression 
		| simple_expression RELOP simple_expression	
		;
				
simple_expression : term 
		  | simple_expression ADDOP term 
		  ;
					
term :	unary_expression
     |  term MULOP unary_expression
     ;

unary_expression : ADDOP unary_expression  
		 | NOT unary_expression 
		 | factor { }
		 ;
	
factor	: variable 
	| ID LPAREN argument_list RPAREN
	| LPAREN expression RPAREN
	| CONST_INT  { }
	| CONST_FLOAT
	| variable INCOP 
	| variable DECOP
	;
	
argument_list : arguments
			  |
			  ;
	
arguments : arguments COMMA logic_expression
	      | logic_expression
	      ;
 

%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

 errorfile.open("1605115_token.txt");
	   logfile.open("1605115_log.txt");


	

	yyin=fp;
	yyparse();
	
	
    errorfile.close();
	logfile.close();

	
	return 0;
}

