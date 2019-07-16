%option noyywrap
%option yylineno

%{
#define YYSTYPE SymbolInfo*

#include<bits/stdc++.h>
#include "1605115_symboltable.cpp"
#include "y.tab.h"

using namespace std;

int word_count=0;
int err_count = 0;

extern ofstream logfile;
extern ofstream errorfile;
extern int line_no;
//log and error file defined in parser. 


extern YYSTYPE yylval;


void updateLineNo(int line) {
	line_no = line;
}

void startLogLine(int line_no) {
	cout<< "\nLine No. " << line_no << ": ";
	
}

string getUpper(string input) {
	string yytextString(input);
	 transform(yytextString.begin(), yytextString.end(),yytextString.begin(), ::toupper);
	 return yytextString;
}

void updateLogFile(string tokenType, string symbolName, int line_no ) {
 startLogLine(line_no);
 cout << "Token <" << tokenType << "> lexeme " << symbolName << " Found" << endl;
}

void updateLogWithError(string errorType, string symbolName, int line_no) {
	cout << "\nError at line " << line_no << ": " << errorType << " " << symbolName << endl;
}


void updateTokenFile(string tokenType, string symbolName) {
	
	cout << "<" << tokenType << ", " << symbolName << "> ";
}

void IncWc(){
	word_count++;
}

SymbolInfo* getSymbolInfo(string name, string type) {
	SymbolInfo* ret = new SymbolInfo(name, type);

	return ret; 
}

string stringFormatter(string input) {

    string str = input, temp, res = "";
    int s = 0, l = str.length();
    for(int i=0; i<(l-1); i++) {
        if(str[i]=='\\') {
            temp = str.substr(s,i-s);
            char c = str[i+1];
            if(c=='a') temp.push_back('\a');
            else if(c=='b') temp.push_back('\b');
            else if(c=='n') temp.push_back('\n');
            else if(c=='t') temp.push_back('\t');
            else if(c=='f') temp.push_back('\f');
            else if(c=='v') temp.push_back('\v');
            else if(c=='r') temp.push_back('\r');
            else if(c=='0') temp.push_back('\0');
            else if(c=='\"') temp.push_back('\"');
            else if(c=='\\') temp.push_back('\\');
            res = res + temp;
            s = i+2;
        }
    }
    res = res + str.substr(s,l-s);
		

	return res;
}

%}

Letter [a-zA-Z]
keyword if|for|do|int|float|void|switch|else|default|while|break|char|double|return|case|continue
EXP ([Ee][-+]?[0-9]+)
UCN (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})
ADDOP \+|-
INCOP \+\+|-- 
MULOP \*|%|\/
RELOP <|<=|>|>=|==|!=
ASSIGNOP =
LOGICOP &&|\|\|
BITOP &|\||\^|<<|>>
NOT !
LPAREN \(
RPAREN \)
LCURL \{
RCURL \}
LTHIRD \[
RTHIRD \]
COMMA ,
SEMICOLON ;
IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]{0,30}  
COMMENT_SINGLE_LINE \/\/[^\n\r]+?(?:\*\)|[\n\r])
COMMENT_MULTI_LINE [/][*][^*]*[*]+([^/*][^*]*[*]+)*[/]
ESCAPE_CHAR \\[abfnrtv0\']
UNFINISHED_COMMENT "/*"([^*]|("*"[^/]))*[^"*/"]



%%


[ \t\v]+ {}
[\n] {}




<<EOF>> {
	return 0;
	//todo might need to change. Not sure if we need to return.
	}

([1-9][0-9]*|0) {string symbol(yytext);
	updateLineNo(yylineno);
 	yylval = getSymbolInfo(symbol, "CONST_INT");
	return CONST_INT; 
 }

([0-9]*\.[0-9]+|[0-9]+\.|[0-9]+){EXP}? {string symbol(yytext);
 	yylval = getSymbolInfo(symbol, "CONST_FLOAT");
	updateLineNo(yylineno);
 	return CONST_FLOAT; 	
 }


\'({ESCAPE_CHAR}|[a-zA-Z0-9])\' {string symbol(yytext);
 //updateLogFile("CHAR_CONST", symbol, yylineno);
 symbol = stringFormatter(symbol);
 updateLineNo(yylineno);
 	
 symbol = symbol.substr(1, symbol.size() - 2);
	//yylval = getSymbolInfo(symbol, "CONST_CHAR");
	//return CONST_CHAR;
//todo probably remove this because does not match to any grammar in the parser.??
 	}




{ADDOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "ADDOP");
	return ADDOP;
}

{INCOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "INCOP");
	return INCOP;
}

{MULOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "MULOP");
	return MULOP;
}

{RELOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "RELOP");
	return RELOP;
}

{ASSIGNOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "ASSIGNOP");
	return ASSIGNOP;
}

{LOGICOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "LOGICOP");
	return LOGICOP;
}

{BITOP} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "BITOP");
	return BITOP;
}

{NOT} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "NOT");
	return NOT;
}

{LPAREN} {updateLineNo(yylineno);
 	
	string symbol(yytext);
		yylval = getSymbolInfo(symbol, "LPAREN");

	return LPAREN; 
}

{RPAREN} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "RPAREN");
	return RPAREN; 
}

{LCURL} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "LCURL");
	return LCURL; 
}

{RCURL} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "RCURL");
	return RCURL;
}

{LTHIRD} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "LTHIRD");
	return LTHIRD;
}

{RTHIRD} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "RTHIRD");
	return RTHIRD; 
}

{COMMA} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "COMMA");
	return COMMA; 
}

{SEMICOLON} {updateLineNo(yylineno);
 	
	string symbol(yytext);
	yylval = getSymbolInfo(symbol, "SEMICOLON");
	return SEMICOLON;
}

{keyword} { updateLineNo(yylineno);
 	
	string yyString(yytext); string yytextString = getUpper(yyString);
	//startLogLine(yylineno); logstream << "Token <" << yytextString << "> Lexeme " << yytext << " found" << endl;
	//tokenstream << "<" << yytextString << "> ";
	//if|for|do|int|float|void|switch|else|default|while|break|char|double|return|case|continue
	
		yylval = getSymbolInfo(yytextString, "KEYWORD");

	if(yytextString == "IF") {
		return IF;
	} else if (yytextString == "FOR") {
		return FOR;
	} else if (yytextString == "DO" ) {
		return DO;
	} else if (yytextString == "INT") {
		return INT;
	} else if (yytextString == "FLOAT") {
		return FLOAT;
	} else if (yytextString == "VOID") {
		return VOID;
	} else if (yytextString == "SWITCH") {
		return SWITCH;
	} else if (yytextString == "ELSE") {
		return ELSE;
	} else if (yytextString == "DEFAULT") {
		return DEFAULT;
	} else if (yytextString == "WHILE") {
		return WHILE;
	} else if (yytextString == "BREAK") {
		return BREAK;
	} else if (yytextString == "CHAR") {
		return CHAR;
	} else if (yytextString == "DOUBLE") {
		return DOUBLE;
	} else if (yytextString == "RETURN") {
		return RETURN;
	} else if (yytextString == "CASE") {
		return CASE;
	} else if (yytextString == "CONTINUE") {
		return CONTINUE;
	}
	
}

{COMMENT_SINGLE_LINE} {updateLineNo(yylineno);
 	
	string symbol(yytext);

}
{COMMENT_MULTI_LINE} {updateLineNo(yylineno);
 	string symbol(yytext); }



\"(([^\"\n]|\\\n)*[^\\\n])?\" {updateLineNo(yylineno);
 	
	
 }


{IDENTIFIER} {updateLineNo(yylineno);
 	 string symbol(yytext);  
yylval = getSymbolInfo(symbol, "ID");
return ID; 
}





[0-9]{1,30}{IDENTIFIER} {updateLineNo(yylineno);
 	
	//INVALID PREFIX ON ID OR INVALID SUFFIX ON NUMBER
}

([0-9]*\.[0-9]*){2,} {updateLineNo(yylineno);
 	
	//TOO MANY DECILMAL POINT ERROR 
}

\'({ESCAPE_CHAR}|[a-zA-Z0-9]|[ \t]){2,}\' {updateLineNo(yylineno);
 	
	//MULTI CHARACTER COUNT ERROR 
}

\'\' {updateLineNo(yylineno);
 	
	//EMPTY CHARACTER CONSTANT ERROR 
}

\'([a-zA-Z0-9]*|\\\') {updateLineNo(yylineno);
 	
	//UNTERMINATE CAHRACTER ERROR 
}

\"(([^\"\n]|\\\n)*[^\\\n])? {updateLineNo(yylineno);
 	
	//UNTERMINATED STRING ERROR 

}


([0-9]*\.[0-9]+|[0-9]+\.|[0-9]+){EXP}([0-9]*\.[0-9]*)+ {updateLineNo(yylineno);
 	
	//ILL FORMED NUMBER 
}

{UNFINISHED_COMMENT} {updateLineNo(yylineno);
 	
	//UNFINISHED COMMENT 
}



. { updateLineNo(yylineno);
 	
	//UNRECOGNIZED CHARACTER
}

%%

