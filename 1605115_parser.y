%{
#include <bits/stdc++.h>
#define YYSTYPE SymbolInfo*
#include "1605115_symboltable.h"
#include "utilityfunctions.h"

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;

int line_no = 1;
int errorCount = 0;

FILE *fp;
ofstream logfile;
ofstream errorfile;
ofstream scratchfile;

SymbolTable symbolTable(10);




void yyerror(char *s) 
{
	string syntaxerror(s);
	errorfile << "Error at line " << line_no <<" :" << syntaxerror << endl << endl ;
	errorCount++;
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

start : program	{
		 $$ = new SymbolInfo($1->getName() , "start");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "start : program\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	;

program : program unit	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() , "program");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "program : program unit\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	| unit	{
		 $$ = new SymbolInfo($1->getName() , "program");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "program : unit\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	;

unit : var_declaration {
		 $$ = new SymbolInfo($1->getName() , "unit");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "unit : var_declaration\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
     | func_declaration {
		 $$ = new SymbolInfo($1->getName() , "unit");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "unit : func_declaration\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
     | func_definition {
		 $$ = new SymbolInfo($1->getName() , "unit");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "unit : func_definition\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
     ;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() +
		 $6->getName(), "func_declaration");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($6);
		 addLineNoLog();
		 logfile << "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON \n\n";
		 logfile << $$->getName() <<endl << endl;
		
		symbolTableEntryForFunctionDeclaration($1, $2, $4);

	 	}
		| type_specifier ID LPAREN RPAREN SEMICOLON		{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "func_declaration");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON	\n\n";
		 logfile << $$->getName() <<endl << endl;
		 		symbolTableEntryForFunctionDeclaration($1, $2);

	 	}
		;

func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() +
		 $6->getName(), "func_definition");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($6);
		 addLineNoLog();
		 logfile << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		| type_specifier ID LPAREN RPAREN compound_statement	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "func_definition");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		;


parameter_list  : parameter_list COMMA type_specifier ID	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName(), "parameter_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "parameter_list : parameter_list COMMA type_specifier ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		| parameter_list COMMA type_specifier	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "parameter_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "parameter_list : parameter_list COMMA type_specifier\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		| type_specifier ID	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() , "parameter_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "parameter_list : type_specifier ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		| type_specifier	{
		 $$ = new SymbolInfo($1->getName() , "parameter_list");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "parameter_list : type_specifier\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		;


compound_statement : LCURL statements RCURL 	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "compound_statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "compound_statement : LCURL statements RCURL\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		| LCURL RCURL	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() , "compound_statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "compound_statement : LCURL RCURL\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		    ;

var_declaration : type_specifier declaration_list SEMICOLON	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "var_declaration");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);

		 
		 addLineNoLog();
		 logfile << "var_declaration : type_specifier declaration_list SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;
		
		 symbolTableEntryForVarDeclaration($1, $2);
	 	}
 		 ;

type_specifier  : INT 	{
		 $$ = new SymbolInfo($1->getName() , "type_specifier");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "type_specifier : INT\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		| FLOAT {
		 $$ = new SymbolInfo($1->getName() , "type_specifier");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "type_specifier : FLOAT\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		| VOID {
		 $$ = new SymbolInfo($1->getName() , "type_specifier");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "type_specifier : VOID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		;


declaration_list : declaration_list COMMA ID	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "declaration_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "declaration_list : declaration_list COMMA ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() +
		 $6->getName(), "declaration_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($6);
		 addLineNoLog();
		 logfile << "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		  | ID	{
		 $$ = new SymbolInfo($1->getName() , "declaration_list");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "declaration_list : ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		  | ID LTHIRD CONST_INT RTHIRD	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName(), "declaration_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		  ;

statements : statement	{
		 $$ = new SymbolInfo($1->getName() , "statements");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "statements : statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	   | statements statement	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() , "statements");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "statements : statements statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	   ;

statement : var_declaration	{
		 $$ = new SymbolInfo($1->getName() , "statement");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "statement : var_declaration\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | expression_statement {
		 $$ = new SymbolInfo($1->getName() , "statement");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "statement : expression_statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | compound_statement {
		 $$ = new SymbolInfo($1->getName() , "statement");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "statement : compound_statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement  {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() + $6->getName() + $7->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($6);
		 $$->addChildSymbol($7);
		 addLineNoLog();
		 logfile << "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "statement : IF LPAREN expression RPAREN statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | IF LPAREN expression RPAREN statement ELSE statement {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() + $6->getName() + $7->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($6);
		 $$->addChildSymbol($7);
		 addLineNoLog();
		 logfile << "statement : IF LPAREN expression RPAREN statement ELSE statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | WHILE LPAREN expression RPAREN statement	 {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "statement : WHILE LPAREN expression RPAREN statement\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON	 {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  | RETURN expression SEMICOLON {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "statement : RETURN expression SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	  ;

expression_statement : SEMICOLON	{
		 $$ = new SymbolInfo($1->getName() , "expression_statement");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "expression_statement : SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
			| expression SEMICOLON  {
		 $$ = new SymbolInfo($1->getName() + $2->getName() , "expression_statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "expression_statement : expression SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
			;

variable : ID	{
				$$ = new SymbolInfo($1->getName(), "variable");

				$$->addChildSymbol($1);
				addLineNoLog();
				 logfile << "variable : ID" << endl << endl;
				 logfile << $1->getName() << endl << endl;
				}
	 | ID LTHIRD expression RTHIRD {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName(), "variable");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "variable : ID LTHIRD expression RTHIRD\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	 ;

expression : logic_expression	{
		 $$ = new SymbolInfo($1->getName() , "expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "expression : logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	   | variable ASSIGNOP logic_expression {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "expression : variable ASSIGNOP logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	   ;

logic_expression : rel_expression 	{
		 $$ = new SymbolInfo($1->getName() , "logic_expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "logic_expression : rel_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		 | rel_expression LOGICOP rel_expression {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "logic_expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "logic_expression : rel_expression LOGICOP rel_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		 ;

rel_expression	: simple_expression {
		 $$ = new SymbolInfo($1->getName() , "rel_expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "rel_expression : simple_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		| simple_expression RELOP simple_expression	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "rel_expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "rel_expression : simple_expression RELOP simple_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		;

simple_expression : term {
		 $$ = new SymbolInfo($1->getName() , "simple_expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "simple_expression : term\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		  | simple_expression ADDOP term {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "simple_expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "simple_expression : simple_expression ADDOP term\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		  ;

term :	unary_expression {
						$$ = new SymbolInfo($1->getName(), "term");
						$$->addChildSymbol($1);
						addLineNoLog();
						logfile << "term : unary_expression\n\n";
						logfile << $$->getName() << endl << endl;
	}
     |  term MULOP unary_expression {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "term");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "term : term MULOP unary_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	}
     ;

unary_expression : ADDOP unary_expression  {
						$$ = new SymbolInfo($1->getName() + $2->getName(), "unary_expression");
						$$->addChildSymbol($1); $$->addChildSymbol($2);
						addLineNoLog();
						logfile << "unary_expression : ADDOP unary_expression\n\n";
						logfile << $$->getName() << endl << endl;
	}
		 | NOT unary_expression		{
						$$ = new SymbolInfo($1->getName() + $2->getName(), "unary_expression");
						$$->addChildSymbol($1); $$->addChildSymbol($2);
						addLineNoLog();
						logfile << "unary_expression : NOT unary_expression\n\n";
						logfile << $$->getName() << endl << endl;
	}
		 | factor	{
						$$ = new SymbolInfo($1->getName(), "unary_expression");
						$$->addChildSymbol($1);
						addLineNoLog();
						logfile << "unary_expression : factor\n\n";
						logfile << $$->getName() << endl << endl;
	}
		 ;

factor	: variable  {
						$$ = new SymbolInfo($1->getName(), "factor");
						$$->addChildSymbol($1);
						addLineNoLog();
						logfile << "factor : variable\n\n";
						logfile << $$->getName() << endl << endl;
	}
	| ID LPAREN argument_list RPAREN	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName(), "factor");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "factor : ID LPAREN argument_list RPAREN\n\n";
		 logfile << $$->getName() <<endl << endl;
	}
	| LPAREN expression RPAREN	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "factor");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "factor : LPAREN expression RPAREN\n\n";
		 logfile << $$->getName() <<endl << endl;
	}
	| CONST_INT  {
			$$ = new SymbolInfo($1->getName(), "factor");
			$$->addChildSymbol($1);
			addLineNoLog();
			logfile << "factor : CONST_INT\n\n";
			logfile << $$->getName() << endl << endl;
	 }
	| CONST_FLOAT	{
			$$ = new SymbolInfo($1->getName(), "factor");
			$$->addChildSymbol($1);
			addLineNoLog();
			logfile << "factor : CONST_FLOAT\n\n";
			logfile << $$->getName() << endl << endl;
	 }
	| variable INCOP {
			$$ = new SymbolInfo($1->getName() + $2->getName(), "factor");
			$$->addChildSymbol($1); $$->addChildSymbol($2);
			addLineNoLog();
			logfile << "factor : variable INCOP\n\n";
			logfile << $$->getName() << endl << endl;
	}
	| variable DECOP	{
			$$ = new SymbolInfo($1->getName() + $2->getName(), "factor");
			$$->addChildSymbol($1); $$->addChildSymbol($2);
			addLineNoLog();
			logfile << "factor : variable DECOP\n\n";
			logfile << $$->getName() << endl << endl;
	}
	;

argument_list : arguments {
		 $$ = new SymbolInfo($1->getName() , "argument_list");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "argument_list : arguments\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
			  |
			  ;

arguments : arguments COMMA logic_expression {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "arguments");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "arguments : arguments COMMA logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	      | logic_expression {
		 $$ = new SymbolInfo($1->getName() , "arguments");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "arguments : logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
	      ;


%%
int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

 	errorfile.open("1605115_error.txt");
	   logfile.open("1605115_log.txt");
	   scratchfile.open("scratch.txt");

		


	yyin=fp;
	yyparse();


	symbolTable.printAllScopeTable(logfile);


	logfile << "Total Lines: " << line_no << endl;
	logfile << "Total Errors: " << errorCount << endl;
	errorfile << "Total Errors: " << errorCount << endl;


    errorfile.close();
	logfile.close();
	scratchfile.close();


	return 0;
}
