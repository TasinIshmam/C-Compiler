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

string main_code = "\nMAIN PROC\n\nMOV AX, @DATA\nMOV DS, AX\n\n";

//todo consider modifying this function. Might hit copychecker.
//todo source: Marut pg 169, PDf pg 180

string outdecProcCode = " \nOUTDEC PROC  \n    PUSH AX \n    PUSH BX \n    PUSH CX \n    PUSH DX  \n    CMP AX,0 \n    JGE BEGIN \n    PUSH AX \n    MOV DL,'-' \n    MOV AH,2 \n    INT 21H \n    POP AX \n    NEG AX \n    \n    BEGIN: \n    XOR CX,CX \n    MOV BX,10 \n    \n    REPEAT: \n    XOR DX,DX \n    DIV BX \n    PUSH DX \n    INC CX \n    OR AX,AX \n    JNE REPEAT \n    MOV AH,2 \n    \n    PRINT_LOOP: \n    POP DX \n    ADD DL,30H \n    INT 21H \n    LOOP PRINT_LOOP \n    \n    MOV AH,2\n    MOV DL,10\n    INT 21H\n    \n    MOV DL,13\n    INT 21H\n	\n    POP DX \n    POP CX \n    POP BX \n    POP AX \n    ret \nOUTDEC ENDP\nEND MAIN\n";


bool functionScopeBeginFlag = false;

FILE *fp;
ofstream logfile;
ofstream scratchfile;
ofstream asmCodeFile;
SymbolTable symbolTable(10);
string curfunction;


// vector<SymbolInfo*>para_list;
// vector<SymbolInfo*>arg_list;
// vector<SymbolInfo*>dec_list;



vector<string> variableDeclarationList;
vector<string> functionVariableDelcarationList;
vector<pair<string,string> >arrayDeclarationList;

	vector<SymbolInfo *> paramterListSymbolInfoVector;  //int func( int a, float b) a,b are parameters
	vector<SymbolInfo *> declarationListSymbolInfoVector; //variables declared inside the function
	vector<SymbolInfo *> ArgumentListSymbolInfoVector; //func (5,2.523) 5 and 2.523 are arguments

//our code makes no distinction between argument and parameter while bhaia's does.


void yyerror(string s) 
{
	string syntaxerror(s);
	logfile << "Error at line " << line_no <<" :" << syntaxerror << endl << endl ;
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

%left RELOP LOGICOP BITOP
%left ADDOP
%left MULOP

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE



%%

start : program	{
		 $$ = new SymbolInfo($1->getName()  + "\n", "start");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "start : program\n\n";
		 logfile << $$->getName() <<endl << endl;


		 string finalCode = ".MODEL SMALL\n.STACK 100H\n.DATA \n";

		 for(int i = 0 ; i < variableDeclarationList.size() ; i++) {
			 finalCode += variableDeclarationList[i] + " dw ?\n";
		 }

		 	for(int i=0;i<arrayDeclarationList.size();i++){
		finalCode+=arrayDeclarationList[i].first+" dw "+arrayDeclarationList[i].second+" dup(?)\n";
	}

		
		finalCode += ".CODE\n";
		
		//todo modify completely. Bangla bhabe kore for main to work
		//finalCode += main_code;

		//finalCode += "RETURNMAIN:\nMOV AH, 4CH \nINT 21H\n";
		finalCode += $1->getCode();
		finalCode += outdecProcCode;

		//$1->setCode(finalCode);

  	   asmCodeFile << finalCode;


	//todo Optimization;
	


	 	}
	;

program : program unit	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + "\n" , "program");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "program : program unit\n\n";
		 logfile << $$->getName() <<endl << endl;
		 	$$->setCode($1->getCode() + $2->getCode());
	 	}
	| unit	{
		 $$ = new SymbolInfo($1->getName() + "\n" , "program");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "program : unit\n\n";
		 logfile << $$->getName() <<endl << endl;
		 	$$->setCode($1->getCode());

	 	}
	;

unit : var_declaration {
		 $$ = new SymbolInfo($1->getName() + "\n" , "unit");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 
		 logfile << "unit : var_declaration\n\n";
		 logfile << $$->getName() <<endl << endl;

		 	$$->setCode($1->getCode());

	 	}
     | func_declaration {
		 $$ = new SymbolInfo($1->getName() + "\n" , "unit");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "unit : func_declaration\n\n";
		 logfile << $$->getName() <<endl << endl;
		 	$$->setCode($1->getCode());

	 	}
     | func_definition {
		 $$ = new SymbolInfo($1->getName() + "\n", "unit");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "unit : func_definition\n\n";
		 logfile << $$->getName() <<endl << endl;
		 	$$->setCode($1->getCode());

	 	}
     ;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 	{
	
	
		 $$ = new SymbolInfo($1->getName() + " " +  $2->getName() + " " + $3->getName() + $4->getName() +
		 $5->getName() +
		 $6->getName() + "\n" , "func_declaration");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($6);
		 addLineNoLog();
		 logfile << "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON \n\n";
		 logfile << $$->getName() <<endl << endl;
		
		createSymbolTableEntryForFunctionID($1, $2, $4);

	 	}
		| type_specifier ID LPAREN RPAREN SEMICOLON		{
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() + "\n" , "func_declaration");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON	\n\n";
		 logfile << $$->getName() <<endl << endl;
		createSymbolTableEntryForFunctionID($1, $2);

	 	}
		;

// Exit function scope after compound statement execution complete.
func_definition : type_specifier ID LPAREN parameter_list RPAREN {
	string functionName = $2->getName();
	SymbolInfo* generateEntry = createSymbolInfoForFunctionID($1, $2, $4);

	SymbolInfo *tableEntry = symbolTable.lookup(functionName);
	if (tableEntry == nullptr) { //function did not have a declaration. So do it now.
	   insertIDToSymbolTable(generateEntry);
		//symbolTable.printAllScopeTable(scratchfile);

	} else {
		if (!checkFunctionSymbolInfoEquality(generateEntry, tableEntry)) {
			addLineNoErr();
			logfile << "Function declaration does not match function definition\n\n";
		};
	}


	symbolTable.enterScope();

	functionScopeBeginFlag = true;
	
	SymbolInfo* functionSymbolInfoEntry = symbolTable.lookup(functionName);


	

	for (int i = 0; i < generateEntry->getFunctionInfoDataPtr()->getArgumentsNumber(); i++) {
		
		ArgumentInfo arg = generateEntry->getFunctionInfoDataPtr()->getArguments()[i];


		SymbolInfo* argIDEntry = new SymbolInfo(arg.getArgumentName(), "ID");

		string assemblyID = generateAssemblyIdVariable(arg.getArgumentName(), symbolTable.getCurrentScope()->getUniqueTableNumber() );

		arg.setArgumentAssemblyVariableName(assemblyID);

		functionSymbolInfoEntry->getFunctionInfoDataPtr()->getArguments()[i] = arg;


		argIDEntry->initializeVariable(arg.getArgumentName());
		argIDEntry->setAssemblyID(assemblyID);



		insertIDToSymbolTable(argIDEntry);
		variableDeclarationList.push_back(assemblyID);
		
	}
	//for all parameters inside the function now
	//symbol table entries as ID types are inserted inside the function scopetable along with assemblyId's
	//the symbolinfo object for the function itself (which is also in the symbol table) has the assemblyId's of each parameter inside the arguments vector.


	


	variableDeclarationList.push_back($2->getName() + "_return");
	curfunction = $2->getName();

	
	


	//todo change name from _return to something less obviously ripped off

	//todo -> Add arguments to the new scope in symboltable

  } compound_statement	{
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName() + "\n" +  $7->getName(), "func_definition");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 $$->addChildSymbol($7);
		 addLineNoLog();
		 logfile << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n";
		 logfile << $$->getName() <<endl << endl;


		$$->setCode($2->getName() + " PROC\n");


		if ($2->getName() == "main") {
		$$->setCode($$->getCode() + "    MOV AX,@DATA\nMOV DS,AX \n" + $7->getCode() + "LReturn" + "main" + ":\nMOV AH,4CH\nINT 21H\n");
		} else {
			SymbolInfo* functionTableEntry = symbolTable.lookup($2->getName());


			string code = $$->getCode() +
					  "PUSH AX\nPUSH BX \nPUSH CX \nPUSH DX\n";


			vector<ArgumentInfo> arguments = functionTableEntry->getFunctionInfoDataPtr()->getArguments();
			
			//todo arguments order in arguments vector is opposite of real order. So just reverse here and during pop. Different from bhaias.
			for(int i = 0; i < arguments.size() ;i++) {
				code += "PUSH " + arguments[i].getArgumentAssemblyVariableName() + "\n";
			}

			code += $7->getCode() +
				"LReturn" + $2->getName() + ":\n";	

			for(int i = arguments.size() - 1; i >= 0; i--) {
					code += "POP " + arguments[i].getArgumentAssemblyVariableName() + "\n";
			} 

				code += "POP DX\nPOP CX\nPOP BX\nPOP AX\nret\n"; 

			$$->setCode(code + $2->getName() + " ENDP\n");
		}

		scratchfile << "\n\n" + $$->getCode() << "\n\n";

	 	} 
		 // FINISH FIRST RULE

		 //STARTING SECOND RULE
		| type_specifier ID LPAREN RPAREN {
	
	string functionName = $2->getName();
	SymbolInfo *tableEntry = symbolTable.lookup(functionName);
	if (tableEntry == nullptr) { //function did not have a declaration. So do it now.
	createSymbolTableEntryForFunctionID($1, $2);

	} else {
		SymbolInfo* generateEntry = createSymbolInfoForFunctionID($1, $2);
		if (!checkFunctionSymbolInfoEquality(generateEntry, tableEntry)) {
			addLineNoErr();
			logfile << "Function declaration does not match function definition\n\n";
		};
	}

	symbolTable.enterScope();

	curfunction = $2->getName();
	variableDeclarationList.push_back(curfunction + "_return");

	functionScopeBeginFlag = true;
	
  } compound_statement	{
		 $$ = new SymbolInfo($1->getName() + " " +  $2->getName() + $3->getName() + $4->getName() + "\n " + 
		 $6->getName(), "func_definition");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($6);
		 addLineNoLog();
		 logfile << "func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n";
		 logfile << $$->getName() <<endl << endl;

		$$->setCode($2->getName() + " PROC\n");


		if ($2->getName() == "main") {
		$$->setCode($$->getCode() + "    MOV AX,@DATA\nMOV DS,AX \n" + $6->getCode() + "LReturn" + "main" + ":\nMOV AH,4CH\nINT 21H\n");
		} else {
			SymbolInfo* functionTableEntry = symbolTable.lookup($2->getName());


			string code = $$->getCode() +
					  "PUSH AX\nPUSH BX \nPUSH CX \nPUSH DX\n";


		

			code += $6->getCode() +
				"LReturn" + $2->getName() + ":\n";	

				code += "POP DX\nPOP CX\nPOP BX\nPOP AX\nret\n"; 

			$$->setCode(code + $2->getName() + " ENDP\n");
		}

				scratchfile << "\n\n" + $$->getCode() << "\n\n";

	 	}
 		;


parameter_list  : parameter_list COMMA type_specifier ID	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + " " + $3->getName() + " " + $4->getName(), "parameter_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "parameter_list : parameter_list COMMA type_specifier ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		| parameter_list COMMA type_specifier	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + " " + $3->getName(), "parameter_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "parameter_list : parameter_list COMMA type_specifier\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		| type_specifier ID	{
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() , "parameter_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "parameter_list : type_specifier ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
		| type_specifier	{
		 $$ = new SymbolInfo($1->getName()  + " " , "parameter_list");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "parameter_list : type_specifier\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		;


compound_statement : LCURL {
	if(functionScopeBeginFlag) {
		functionScopeBeginFlag = false;
	} else {
		symbolTable.enterScope();
	}
} statements RCURL 	{
	//todo finish for function
		 $$ = new SymbolInfo($1->getName() + $3->getName() + $4->getName(), "compound_statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "compound_statement : LCURL statements RCURL\n\n";
		 logfile << $$->getName() <<endl << endl;
		
		 //symbolTable.printAllScopeTable(logfile);
		 symbolTable.exitScope();

		 $$->setCode($3->getCode());
	 	}
 		| LCURL { 
			if(functionScopeBeginFlag) {
				functionScopeBeginFlag = false;
			} else {
				symbolTable.enterScope();
			}		 	
		 } RCURL	{
		 $$ = new SymbolInfo($1->getName() + $3->getName() , "compound_statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "compound_statement : LCURL RCURL\n\n";
		 logfile << $$->getName() <<endl << endl;

		 symbolTable.printAllScopeTable(logfile);
		 symbolTable.exitScope();
	 	}
 		    ;

var_declaration : type_specifier declaration_list SEMICOLON	{
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() + $3->getName() + "\n" , "var_declaration");
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
		 $$ = new SymbolInfo($1->getName() + $2->getName() + " " +  $3->getName(), "declaration_list");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "declaration_list : declaration_list COMMA ID\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + " " +  $3->getName() + $4->getName() +
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

			$$->setCode($1->getCode());
	 	}
	   | statements statement	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() , "statements");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "statements : statements statement\n\n";
		 logfile << $$->getName() <<endl << endl;

		 	$$->setCode($1->getCode() + $2->getCode());
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
		$$->setName($1->getName());
		$$->setCode($1->getCode());
	 	}
	  | compound_statement {
		 $$ = new SymbolInfo($1->getName() , "statement");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "statement : compound_statement\n\n";
		 logfile << $$->getName() <<endl << endl;
		 $$->setName($1->getName());
		$$->setCode($1->getCode());
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

		string code = $3->getCode();
		string label1 = newLabel();
		string label2 = newLabel();
		code += ";Loop Begin\n";
		code += label1 + ":\n";
		code += ";$4 code Begin\n";
		code += $4->getCode();
		code += ";$4 code End\n";

		code += "MOV AX," + $4->getAssemblyID() + "\n";
		code += "CMP AX,0\n";
		code += "JE " + label2 + "\n";
		code += ";$7 code Begin\n";
		code += $7->getCode();
		code += ";$5 code Begin\n";
		code += $5->getCode();
		code += "JMP " + label1 + "\n";
		code += label2 + ":\n";
		code += ";Loop END\n";
		$$->setCode(code);

		//todo change arouond logic for copychecker mara prevention

	 	}
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "statement : IF LPAREN expression RPAREN statement\n\n";
		 logfile << $$->getName() <<endl << endl;

		string code = $3->getCode();
		string label1 = newLabel();
		code += "MOV AX," + $3->getAssemblyID() + "\n";
		code += "CMP AX,0\n";
		code += "JE " + label1 + "\n";
		code += $5->getCode();
		code += label1 + ":\n";
		$$->setCode(code);

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

		 string code = $3->getCode();
		string label1 = newLabel();
		string label2 = newLabel();
		code += "MOV AX," + $3->getAssemblyID() + "\n";
		code += "CMP AX,0\n";
		code += "JE " +label1 + "\n";
		code += $5->getCode();
		code += "JMP " + label2 + "\n";
		code += label1 + ":\n";
		code += $7->getCode();
		code += label2 + ":\n";
		 $$-> setCode(code);

	 	}
	  | WHILE LPAREN expression RPAREN statement	 {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "statement : WHILE LPAREN expression RPAREN statement\n\n";
		 logfile << $$->getName() <<endl << endl;

		string code = "";
		string label1 = newLabel();
		string label2 = newLabel();
		code += label1 + ":\n";
		code += $3->getCode();
		code += "MOV AX," + $3->getAssemblyID() + "\n";
		code += "CMP AX,0\n";
		code += "JE " + label2 + "\n";
		code += $5->getCode();
		code += "JMP " + label1 + "\n";
		code += label2 + ":\n";
		$$->setCode(code);

	 	}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON	 {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName() +
		 $5->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 $$->addChildSymbol($5);
		 addLineNoLog();
		 logfile << "statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;

		 SymbolInfo* symbolTableEntry = symbolTable.lookup($3->getName());

		 if (symbolTableEntry == nullptr) {
			 addLineNoErr();
			 logfile << "Undeclared variable";
		 }

		 string code = "MOV AX," + symbolTableEntry->getAssemblyID();
		 code += "\nCALL OUTDEC\n";
		 $$->setCode(code);


	 	}
	  | RETURN expression SEMICOLON {
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() + $3->getName(), "statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "statement : RETURN expression SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;

		 		string code = $2->getCode();
		code += "MOV AX," + $2->getAssemblyID() + "\n";
		code += "MOV " + curfunction + "_return,AX\n";
		code += "JMP LReturn" + curfunction + "\n";

		//todo hardcoded to return from main. If you want to support all functions then modify
		$$->setCode(code);

		//  string code = $2->getCode();
		// code += "MOV AX," + $2->getAssemblyID() + "\n";
		// code += "MOV " + currentFunctionGlobalString + "_return,AX\n";
		// code += "JMP LReturn" + currentFunctionGlobalString + "\n";
		// $$->setCode(code);

		//todo understand/uncomment function code. (USED FOR FUNCTIONS. SO NA USE KORTE PARLE BAAD DIO.)
	 	}


	  ;

expression_statement : SEMICOLON	{
		 $$ = new SymbolInfo($1->getName()  + "\n" , "expression_statement");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "expression_statement : SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;
	 	}
			| expression SEMICOLON  {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + "\n"  , "expression_statement");
		 $$->addChildSymbol($1); $$->addChildSymbol($2);
		 addLineNoLog();
		 logfile << "expression_statement : expression SEMICOLON\n\n";
		 logfile << $$->getName() <<endl << endl;

		 $$->setCode($1->getCode());
		$$->setAssemblyID($1->getAssemblyID());
	 	}
			;

variable : ID	{
				$$ = new SymbolInfo($1->getName(), "variable");

				$$->addChildSymbol($1);
				addLineNoLog();
				 logfile << "variable : ID" << endl << endl;
				 logfile << $1->getName() << endl << endl;

				verifyVariableIDIsDeclared($1);
				$$->setReturnType(getReturnTypeOfSymbolTableEntry($1->getName()));	
				string assemblyName = symbolTable.lookup($1->getName())->getAssemblyID();
						$$->setAssemblyID(assemblyName);



				$$->setCode("");




		}
	 | ID LTHIRD expression RTHIRD {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName(), "variable");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "variable : ID LTHIRD expression RTHIRD\n\n";
		 logfile << $$->getName() <<endl << endl;

		verifyArrayIDIsDeclared($1);
		if( $3->getReturnType() != "int"){
			addLineNoErr();
			logfile << "Non Integer Array index\n\n";
		}
		$$->setReturnType(getReturnTypeOfSymbolTableEntry($1->getName()));		

		string codes = "";
		codes += $3->getCode();
		codes += "MOV BX," + $3->getAssemblyID() + "\n";
		codes+="ADD BX,BX\n"; 
		$$->setAssemblyArrayMember(true);


	
		string assemblyName = symbolTable.lookup($1->getName())->getAssemblyID();


		$$->setCode(codes);
		$$->setAssemblyID(assemblyName);

		scratchfile << "variable with code created. CODE: \n" << codes;

	 }
	 ;

expression : logic_expression	{
		 $$ = new SymbolInfo($1->getName() , "expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "expression : logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		 $$->setReturnType($1->getReturnType());

		 	$$->setCode($1->getCode());
			$$->setAssemblyID($1->getAssemblyID());

		//  if($$->getReturnType() == "" || $$->getReturnType() == "void") {
		// 	cerr<< ($$->getName() << "Expression with return type: " << $$->getReturnType() << " - in line " << line_no << endl << endl;
		//  }

	 	}
	   | variable ASSIGNOP logic_expression {
		 $$ = new SymbolInfo($1->getName() + " " +  $2->getName() + " " + $3->getName(), "expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "expression : variable ASSIGNOP logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		evaluateTypeConversionForASSIGNOP($1, $3);
		 $$->setReturnType($1->getReturnType());

		string code = $1->getCode() + $3->getCode();
		code += "MOV AX," + $3->getAssemblyID() + "\n";

		if($1->isAssemblyArrayMember()) {
			code += "MOV " + $1->getAssemblyID() + "[BX],AX\n";
		} else {
			code += "MOV " + $1->getAssemblyID() + ",AX\n";
		}
		
		$$->setCode(code);
		$$->setAssemblyID($1->getAssemblyID());

	 	}
	   ;

logic_expression : rel_expression 	{
		 $$ = new SymbolInfo($1->getName() , "logic_expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "logic_expression : rel_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		 $$->setReturnType($1->getReturnType());
		 $$->setCode($1->getCode());
		 $$->setAssemblyID($1->getAssemblyID());

		//  if($1->getAssemblyID() == "t5") {
		// 	 cout << "\n\n";
		// 	 cout << $$->getCode();
		//  }
	
		  	}
		 | rel_expression LOGICOP rel_expression {
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " +  $3->getName(), "logic_expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "logic_expression : rel_expression LOGICOP rel_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		 $$->setReturnType("int");
		 
		 evaluateTypeConsistencyForOperands($1,$3);

		 string code = $1->getCode() + $3->getCode();

		 		 //scratchfile << "\n\nCODE TEST\n\n" << code << "\n";

		 string tempVar = generateNewTempVariable();
		 $$->setAssemblyID(tempVar);
		
		code += generateCodeForLogicOp($1->getAssemblyID(), $2->getName(), $3->getAssemblyID(), $$->getAssemblyID());

		$$->setCode(code);



		 //scratchfile << "\n\nCODE TEST\n\n" << code << "\n";
	 	}
		 ;

rel_expression	: simple_expression {
		 $$ = new SymbolInfo($1->getName() , "rel_expression");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "rel_expression : simple_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		 $$->setReturnType($1->getReturnType());

		 $$->setCode($1->getCode());
		$$->setAssemblyID($1->getAssemblyID());
	 	}
		| simple_expression RELOP simple_expression	{
		 $$ = new SymbolInfo($1->getName() + " " + $2->getName() + " " +  $3->getName(), "rel_expression");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "rel_expression : simple_expression RELOP simple_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		 $$->setReturnType("int");

		 evaluateTypeConsistencyForOperands($1,$3);


		 string tempVar = generateNewTempVariable();
		 $$->setAssemblyID(tempVar);

		 string code = $1->getCode() + $3->getCode();
				 		 scratchfile << "\n\nCODE TEST\n\n" << code << "\n";

		 code += generateCodeForRelop($1->getAssemblyID(), $2->getName(), $3->getAssemblyID(), $$->getAssemblyID());

		 $$->setCode(code);
		 		 scratchfile << "\n\nCODE TEST\n\n" << code << "\n";

	 	}
		;

simple_expression : term {
		$$ = new SymbolInfo($1->getName() , "simple_expression");
		$$->addChildSymbol($1);
		addLineNoLog();
		logfile << "simple_expression : term\n\n";
		logfile << $$->getName() <<endl << endl;
		$$->setReturnType($1->getReturnType());
		$$->setCode($1->getCode());
		$$->setAssemblyID($1->getAssemblyID());


	}
		| simple_expression ADDOP term {
		$$ = new SymbolInfo($1->getName() + " " +  $2->getName() + " " +  $3->getName(), "simple_expression");
		$$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		addLineNoLog();
		logfile << "simple_expression : simple_expression ADDOP term\n\n";
		logfile << $$->getName() <<endl << endl;
		$$->setReturnType(evaluateReturnTypeForADDOP($1,$3));

		string code = $1->getCode() + $3->getCode();

		code += "MOV AX," + $1->getAssemblyID() + "\n";
		string tempVariable = generateNewTempVariable();
		if ($2->getName() == "+")
		{
			code += "ADD AX," + $3->getAssemblyID() + "\n";
		}
		else
		{
			code += "SUB AX," + $3->getAssemblyID() + "\n";
		}
		code += "MOV " + tempVariable + ",AX\n";
		$$->setCode(code);
		$$->setAssemblyID(tempVariable);
	}
		;

term :	unary_expression {
						$$ = new SymbolInfo($1->getName(), "term");
						$$->addChildSymbol($1);
						addLineNoLog();
						logfile << "term : unary_expression\n\n";
						logfile << $$->getName() << endl << endl;
						$$->setReturnType($1->getReturnType());
						$$->setCode($1->getCode());
						$$->setAssemblyID($1->getAssemblyID());
	}
     |  term MULOP unary_expression {
		 $$ = new SymbolInfo($1->getName() + " " +   $2->getName() + " " + $3->getName(), "term");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "term : term MULOP unary_expression\n\n";
		 logfile << $$->getName() <<endl << endl;

		 $$->setReturnType(evaluateReturnTypeForMULOP($1, $2, $3));

		 if($2->getName()=="%") {
			 string code = $1->getCode() + $3->getCode();
			 string temp = generateNewTempVariable();

			 code+="MOV AX,"+$1->getAssemblyID()+"\n";
				code+="MOV BX,"+$3->getAssemblyID()+"\n";
				code+="MOV DX,0\n";
				code+="DIV BX\n";
				code+="MOV "+temp +", DX\n";
				$$->setCode(code);
				$$->setAssemblyID(temp);
		 } else if ($2->getName()=="/") {
			 
			 string code=$1->getCode()+$3->getCode();
				string temp =generateNewTempVariable();
				code+="MOV AX,"+$1->getAssemblyID()+"\n";
				code+="MOV BX,"+$3->getAssemblyID()+"\n";
				code+="DIV BX\n";
				code+="MOV "+temp+", AX\n";
				$$->setCode(code);
				$$->setAssemblyID(temp);


		 } else if ($2->getName() =="*") {

			 string code=$1->getCode()+$3->getCode();
					string temp=generateNewTempVariable();
					code+="MOV AX,"+$1->getAssemblyID()+"\n";
					code+="MOV BX,"+$3->getAssemblyID()+"\n";
					code+="MUL BX\n";
					code+="MOV "+ temp +", AX\n";
					$$->setCode(code);
					$$->setAssemblyID(temp);

		 }



	}
     ;

unary_expression : ADDOP unary_expression  {
						$$ = new SymbolInfo($1->getName() + " " +  $2->getName(), "unary_expression");
						$$->addChildSymbol($1); $$->addChildSymbol($2);
						addLineNoLog();
						logfile << "unary_expression : ADDOP unary_expression\n\n";
						logfile << $$->getName() << endl << endl;
						if( checkIfValidFunctionReturnTypeInExpression($2) ) {
							string retType = $2->getReturnType();
							$$->setReturnType(retType);

							string code = $2->getCode();

							if($1->getName() == "-") {
								code+="MOV AX,"+$2->getAssemblyID()+"\n";
								code+="NEG AX\n";
								code+="MOV "+$2->getAssemblyID()+",AX\n";
							} 

							$$->setCode(code);
							$$->setAssemblyID($2->getAssemblyID());

						} else {
						$$->setReturnType("invalid");		
						//todo verify if setting this to invalid is the right thing.
						//we've already given an error if the return type is invalid. 
						//so this is going to propogate the error further up the gramar.
						}
					

	}
		 | NOT unary_expression		{
						$$ = new SymbolInfo($1->getName() + $2->getName(), "unary_expression");
						$$->addChildSymbol($1); $$->addChildSymbol($2);
						addLineNoLog();
						logfile << "unary_expression : NOT unary_expression\n\n";
						logfile << $$->getName() << endl << endl;
						checkIfValidFunctionReturnTypeInExpression($2);
						$$->setReturnType("int");
						
						string code = $2->getCode();
						code+="MOV AX,"+$2->getAssemblyID()+"\n";
						code+="NOT AX\n";
						code+="MOV "+$2->getAssemblyID()+",AX\n";

						$$->setCode(code);
						$$->setAssemblyID($2->getAssemblyID());
						

	}
		 | factor	{
						$$ = new SymbolInfo($1->getName(), "unary_expression");
						$$->addChildSymbol($1);
						addLineNoLog();
						logfile << "unary_expression : factor\n\n";
						logfile << $$->getName() << endl << endl;
						$$->setReturnType($1->getReturnType());
						$$->setCode($1->getCode());
						$$->setAssemblyID($1->getAssemblyID());

	}
		 ;

factor	: variable  {
						$$ = new SymbolInfo($1->getName(), "factor");
						$$->addChildSymbol($1);

						addLineNoLog();
						logfile << "factor : variable\n\n";
						logfile << $$->getName() << endl << endl;
						$$->setReturnType($1->getReturnType());
						string currentCode = $1->getCode();
						if($1->isAssemblyArrayMember()) {
							string tempVar = generateNewTempVariable();
							currentCode += "MOV AX, " + $1->getAssemblyID() + "[BX]\n";
							currentCode += "MOV " + tempVar + ",AX\n";
							$$->setAssemblyID(tempVar);
						} else {
							$$->setAssemblyID($1->getAssemblyID());
						}

						$$->setCode(currentCode);
						
	}
	| ID LPAREN argument_list RPAREN	{
		//todo Function call. Handle Later.

		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName() + $4->getName(), "factor");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3); $$->addChildSymbol($4);
		 addLineNoLog();
		 logfile << "factor : ID LPAREN argument_list RPAREN\n\n";
		 logfile << $$->getName() <<endl << endl;

		 //todo Evaluate function called with appropriate number of variables etc etc
		functionCallValidationWithArgumentTypeCheck($1, $3);
		 $$->setReturnType(getReturnTypeOfSymbolTableEntry($1->getName()));	

		string code = $3->getCode();

		// cout << "arguments list code ---- \n";
		// cout << code << "\n";

		SymbolInfo* functionSymbolInfoEntry = symbolTable.lookup($1->getName());

		vector<ArgumentInfo> parameters = functionSymbolInfoEntry->getFunctionInfoDataPtr()->getArgumentsCopy();

		reverse(parameters.begin(), parameters.end());



		for(int i = 0 ; i < parameters.size(); i++) {

			code += "MOV AX," + ArgumentListSymbolInfoVector[i]->getAssemblyID() + "\n";

			code += "MOV " + parameters[i].getArgumentAssemblyVariableName() + ",AX\n";

		}

		code += "CALL " + $1->getName() + "\n";
		code += "MOV AX," + $1->getName() + "_return\n";

		string temp = generateNewTempVariable();
		code += "MOV " + temp + ",AX\n";
		$$->setCode(code);
		$$->setAssemblyID(temp);
		ArgumentListSymbolInfoVector.clear();

		 
	}
	| LPAREN expression RPAREN	{
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "factor");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "factor : LPAREN expression RPAREN\n\n";
		 logfile << $$->getName() <<endl << endl;

		 $$->setReturnType($2->getReturnType());
		 $$->setCode($2->getCode());
		 $$->setAssemblyID($2->getAssemblyID());
	}
	| CONST_INT  {
			$$ = new SymbolInfo($1->getName(), "factor");
			$$->addChildSymbol($1);
			addLineNoLog();
			logfile << "factor : CONST_INT\n\n";
			logfile << $$->getName() << endl << endl;
			$$->setReturnType("int");

			string temp = generateNewTempVariable();
			string code = "MOV " + temp + "," + $1->getName() + "\n";
			$$->setAssemblyID(temp);
			$$->setCode(code);

		//	cout << code;

	 }
	| CONST_FLOAT	{
			$$ = new SymbolInfo($1->getName(), "factor");
			$$->addChildSymbol($1);
			addLineNoLog();
			logfile << "factor : CONST_FLOAT\n\n";
			logfile << $$->getName() << endl << endl;
			$$->setReturnType("float");

			string temp = generateNewTempVariable();
			string code = "MOV " + temp + "," + $1->getName() + "\n";
			$$->setAssemblyID(temp);
			$$->setCode(code);
	 }
	| variable INCOP {
			$$ = new SymbolInfo($1->getName() + $2->getName(), "factor");
			$$->addChildSymbol($1); $$->addChildSymbol($2);
			addLineNoLog();
			logfile << "factor : variable INCOP\n\n";
			logfile << $$->getName() << endl << endl;

			$$->setReturnType($1->getReturnType());

			string tempVar = generateNewTempVariable();
			string codes = "";


			if($$->isAssemblyArrayMember()) {
				codes+="MOV AX,"+$1->getAssemblyID()+"[BX]\n";	
				codes+="MOV "+ tempVar +",AX\n";
				codes+="MOV AX,"+$1->getAssemblyID()+"[BX]\n";
				codes+="INC AX\n";
				codes+="MOV "+$1->getAssemblyID()+"[BX],AX\n";


			} else {
			codes+="MOV AX,"+$1->getAssemblyID()+"\n";	
			codes+="MOV "+ tempVar +",AX\n";
			codes+="INC "+$1->getAssemblyID()+"\n";

			}


			$$->setCode(codes);
			$$->setAssemblyID(tempVar);



			
	}
	| variable DECOP	{
			$$ = new SymbolInfo($1->getName() + $2->getName(), "factor");
			$$->addChildSymbol($1); $$->addChildSymbol($2);
			addLineNoLog();
			logfile << "factor : variable DECOP\n\n";
			logfile << $$->getName() << endl << endl;

			$$->setReturnType($1->getReturnType());

			string tempVar = generateNewTempVariable();
			string codes = "";


			if($$->isAssemblyArrayMember()) {
				codes+="MOV AX,"+$1->getAssemblyID()+"[BX]\n";	
				codes+="MOV "+ tempVar +",AX\n";
				codes+="MOV AX,"+$1->getAssemblyID()+"[BX]\n";
				codes+="DEC AX\n";
				codes+="MOV "+$1->getAssemblyID()+"[BX],AX\n";


			} else {
			codes+="MOV AX,"+$1->getAssemblyID()+"\n";	
			codes+="MOV "+ tempVar +",AX\n";
			codes+="DEC "+$1->getAssemblyID()+"\n";

			}


			$$->setCode(codes);
			$$->setAssemblyID(tempVar);
	}
	;

argument_list : arguments { 
		 $$ = new SymbolInfo($1->getName() , "argument_list");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "argument_list : arguments\n\n";
		 logfile << $$->getName() <<endl << endl;
		$$->setCode($1->getCode());

	 	}
			  |  {
				  $$ = new SymbolInfo("", "argument_list");
		 		 
				 addLineNoLog();
		 		logfile << "argument_list : \n\n";
		 		logfile << $$->getName() <<endl << endl;
			  }
			  ;

arguments : arguments COMMA logic_expression {
		 $$ = new SymbolInfo($1->getName() + $2->getName() + $3->getName(), "arguments");
		 $$->addChildSymbol($1); $$->addChildSymbol($2); $$->addChildSymbol($3);
		 addLineNoLog();
		 logfile << "arguments : arguments COMMA logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;
		 	 ArgumentListSymbolInfoVector.push_back($3);
			$$->setCode($1->getCode() + $3->getCode());



	 	}
	      | logic_expression {
		 $$ = new SymbolInfo($1->getName() , "arguments");
		 $$->addChildSymbol($1);
		 addLineNoLog();
		 logfile << "arguments : logic_expression\n\n";
		 logfile << $$->getName() <<endl << endl;

		 ArgumentListSymbolInfoVector.push_back($1);
		 	$$->setCode($1->getCode());

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

	   logfile.open("1605115_log.txt");
	   scratchfile.open("scratch.txt");
	   asmCodeFile.open("code.asm");

		


	yyin=fp;
	yyparse();


	symbolTable.printAllScopeTable(logfile);


	logfile << "Total Lines: " << line_no << endl;
	logfile << "Total Errors: " << errorCount << endl;
	logfile << "Total Errors: " << errorCount << endl;


	logfile.close();
	scratchfile.close();
	asmCodeFile.close();

	optimizeCode();
	return 0;
}
