%option noyywrap
%option yylineno

%{
#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>

#include "1605115_symboltable.cpp"

using namespace std;

int word_count=0;
int line_count=1;
int err_count = 0;

ofstream tokenfile;
ofstream logfile;

SymbolTable symbolTable(3);



void startLogLine(int line_no) {
	logfile<< "\nLine No. " << line_no << ": ";
	
}

string getUpper(string input) {
	string yytextString(input);
	 transform(yytextString.begin(), yytextString.end(),yytextString.begin(), ::toupper);
	 return yytextString;
}

void updateLogFile(string tokenType, string symbolName, int line_no ) {
 startLogLine(line_no);
 logfile << "Token <" << tokenType << "> lexeme " << symbolName << " Found" << endl;
}

void updateLogWithError(string errorType, string symbolName, int line_no) {
	logfile << "\nError at line " << line_no << ": " << errorType << " " << symbolName << endl;
}

void updateSymbolTable(string tokenType, string symbolName) {
 SymbolInfo *symbolInfo = new SymbolInfo(symbolName , tokenType);
 symbolTable.insert(symbolInfo);
 symbolTable.printAllScopeTable(logfile);
}

void updateTokenFile(string tokenType, string symbolName) {
	
	tokenfile << "<" << tokenType << ", " << symbolName << "> ";
}

void IncWc(){
	word_count++;
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
ASSINOP =
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
[\n] {line_count++;}




<<EOF>> {logfile << "\nTotal Lines: " << yylineno << endl; logfile << "Total Errors: " << err_count << endl; return 0;}

([1-9][0-9]*|0) {string symbol(yytext);
 updateLogFile("CONST_INT", symbol, yylineno);
 updateSymbolTable("CONST_INT", symbol);
 updateTokenFile("CONST_INT", symbol);	
 }

([0-9]*\.[0-9]+|[0-9]+\.|[0-9]+){EXP}? {string symbol(yytext);
 updateLogFile("CONST_FLOAT", symbol, yylineno);
 updateSymbolTable("CONST_FLOAT", symbol);
 updateTokenFile("CONST_FLOAT", symbol);	
 }


\'({ESCAPE_CHAR}|[a-zA-Z0-9])\' {string symbol(yytext);
 updateLogFile("CHAR_CONST", symbol, yylineno);
 symbol = stringFormatter(symbol);
 
 symbol = symbol.substr(1, symbol.size() - 2);

 updateSymbolTable("CHAR_CONST", symbol);
 updateTokenFile("CHAR_CONST", symbol);	}




{ADDOP} {
	string symbol(yytext);
	updateLogFile("ADDOP", symbol, yylineno);
	updateTokenFile("ADDOP", symbol);
}

{INCOP} {
	string symbol(yytext);
	updateLogFile("INCOP", symbol, yylineno);
	updateTokenFile("INCOP", symbol);
}

{MULOP} {
	string symbol(yytext);
	updateLogFile("MULOP", symbol, yylineno);
	updateTokenFile("MULOP", symbol);
}

{RELOP} {
	string symbol(yytext);
	updateLogFile("RELOP", symbol, yylineno);
	updateTokenFile("RELOP", symbol);
}

{ASSINOP} {
	string symbol(yytext);
	updateLogFile("ASSINOP", symbol, yylineno);
	updateTokenFile("ASSINOP", symbol);
}

{LOGICOP} {
	string symbol(yytext);
	updateLogFile("LOGICOP", symbol, yylineno);
	updateTokenFile("LOGICOP", symbol);
}

{BITOP} {
	string symbol(yytext);
	updateLogFile("BITOP", symbol, yylineno);
	updateTokenFile("BITOP", symbol);
}

{NOT} {
	string symbol(yytext);
	updateLogFile("NOT", symbol, yylineno);
	updateTokenFile("NOT", symbol);
}

{LPAREN} {
	string symbol(yytext);
	updateLogFile("LPAREN", symbol, yylineno);
	updateTokenFile("LPAREN", symbol);
}

{RPAREN} {
	string symbol(yytext);
	updateLogFile("RPAREN", symbol, yylineno);
	updateTokenFile("RPAREN", symbol);
}

{LCURL} {
	string symbol(yytext);
	updateLogFile("LCURL", symbol, yylineno);
	updateTokenFile("LCURL", symbol);
}

{RCURL} {
	string symbol(yytext);
	updateLogFile("RCURL", symbol, yylineno);
	updateTokenFile("RCURL", symbol);
}

{LTHIRD} {
	string symbol(yytext);
	updateLogFile("LTHIRD", symbol, yylineno);
	updateTokenFile("LTHIRD", symbol);
}

{RTHIRD} {
	string symbol(yytext);
	updateLogFile("RTHIRD", symbol, yylineno);
	updateTokenFile("RTHIRD", symbol);
}

{COMMA} {
	string symbol(yytext);
	updateLogFile("COMMA", symbol, yylineno);
	updateTokenFile("COMMA", symbol);
}

{SEMICOLON} {
	string symbol(yytext);
	updateLogFile("SEMICOLON", symbol, yylineno);
	updateTokenFile("SEMICOLON", symbol);
}

{keyword} { string yyString(yytext); string yytextString = getUpper(yyString);
	startLogLine(yylineno); logfile << "Token <" << yytextString << "> Lexeme " << yytext << " found" << endl;
	tokenfile << "<" << yytextString << "> ";}

{COMMENT_SINGLE_LINE} {startLogLine(yylineno); logfile << "Token <COMMENT> Lexeme" << yytext << " found" << endl; line_count++;}
{COMMENT_MULTI_LINE} {startLogLine(yylineno); logfile << "Token <COMMENT> Lexeme" << yytext << " found" <<  endl; }



\"(([^\"\n]|\\\n)*[^\\\n])?\" {startLogLine(yylineno); logfile << "Token <STRING> Lexeme" << yytext << " found" << endl;
string yytextString(yytext);
string newstring = stringFormatter(yytextString);
tokenfile << "<STRING, " << newstring << "> "; }


{IDENTIFIER} { string symbol(yytext);  
 updateLogFile("ID", symbol, yylineno); updateSymbolTable("ID", symbol); updateTokenFile("ID", symbol);}





[0-9]{1,30}{IDENTIFIER} {string symbol(yytext); 
updateLogWithError("Invalid prefix on ID or invalid suffix on Number", symbol, yylineno);
err_count++;
}

([0-9]*\.[0-9]*){2,} {string symbol(yytext); 
updateLogWithError("Too many decimal point error", symbol, yylineno);
err_count++;
}

\'({ESCAPE_CHAR}|[a-zA-Z0-9]|[ \t]){2,}\' {string symbol(yytext); 
updateLogWithError("Multi Character constant error", symbol, yylineno);
err_count++;
}

\'\' {string symbol(yytext); 
updateLogWithError("Empty Character constant error", symbol, yylineno);
err_count++;
}

\'([a-zA-Z0-9]*|\\\') {string symbol(yytext); 
updateLogWithError("Unterminated Character", symbol, yylineno);
err_count++;
}

\"(([^\"\n]|\\\n)*[^\\\n])? {string symbol(yytext); 
updateLogWithError("Unterminated String", symbol, yylineno);
err_count++;

}


([0-9]*\.[0-9]+|[0-9]+\.|[0-9]+){EXP}([0-9]*\.[0-9]*)+ {string symbol(yytext); 
updateLogWithError("Ill formed number", symbol, yylineno);
err_count++;
}

{UNFINISHED_COMMENT} {
	string symbol(yytext); 
updateLogWithError("Unterminated comment", symbol, yylineno);
err_count++;
}



. { string symbol(yytext); 
updateLogWithError("Unrecognized character", symbol, yylineno);
err_count++;}

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
 	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

	   tokenfile.open("1605115_token.txt");
	   logfile.open("1605115_log.txt");


	

	yyin= fin;
	yylex();
	fclose(yyin);



	cout << "Finished" << endl;
    tokenfile.close();
	logfile.close();


	return 0;
}
