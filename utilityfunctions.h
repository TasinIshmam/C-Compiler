
#ifndef UTILITYFUNCTIONS
#define UTILITYFUNCTIONS


#include <bits/stdc++.h>
#include "1605115_symboltable.h"
using namespace std;


extern int line_no;
extern ofstream errorfile;
extern ofstream logfile;
extern ofstream scratchfile;
extern SymbolTable symbolTable;



void addLineNoErr() {
	errorfile <<"At line No: " << line_no << " ";

}



void addLineNoLog() {
	logfile <<"At line no: " << line_no << " ";

}



SymbolInfo* deepCopySymbolInfo(SymbolInfo* oldCopy) {
	SymbolInfo* ret = new SymbolInfo(oldCopy->getName(), oldCopy->getType());
	return ret;
}

SymbolInfo* createSymbolInfoForArrayID(string name, string type, int arrSize) {
	SymbolInfo* ret = new SymbolInfo(name, "ID");
	ret->initializeArray(type, arrSize);

	return ret;
}

SymbolInfo* createSymbolInfoForVariableID(string name, string type) {
	SymbolInfo* ret = new SymbolInfo(name, "ID");
	ret->initializeVariable(type);


	return ret;
}


void symbolTableEntryForVarDeclaration (SymbolInfo* typeSpecifier, SymbolInfo* declarationList){

    string typeOfVariables = typeSpecifier->getName();
if(typeOfVariables == "void") {
        addLineNoErr();
        errorfile << "variable(s) declared as type 'void' " << endl << endl;
    }


    vector<SymbolInfo*> variableNames;
    vector<SymbolInfo*> arrayNames;
    SymbolInfo* tempDeclarationList = declarationList;

//	scratchfile << typeSpecifier->getName() << " " << declarationList->getName() << endl;

	// scratchfile << declarationList->getChildSymbols()[0]->getType() << endl;

	
    while(tempDeclarationList->getChildSymbols()[0]->getType() == "declaration_list"){
        if(tempDeclarationList->getChildSymbols().size() > 5) {
            //is an array
            string arrayName = tempDeclarationList->getChildSymbols()[2]->getName();
            string arrayLenString = tempDeclarationList->getChildSymbols()[4]->getName();
            int arrayLen = stoi(arrayLenString);

			
            scratchfile << arrayName << arrayLen << endl << endl;
			symbolTable.insert(createSymbolInfoForArrayID(arrayName, typeOfVariables, arrayLen));


        } else {
            //is a variable
			//scratchfile <<(*tempDeclarationList).childSymbols.size() ;




            string variableName = tempDeclarationList->getChildSymbols()[2]->getName();
            scratchfile << variableName << endl << endl;
			symbolTable.insert(createSymbolInfoForVariableID(variableName, typeOfVariables));


        }


        tempDeclarationList = tempDeclarationList->getChildSymbols()[0];

    }


    if(tempDeclarationList->getChildSymbols().size()> 3) {
        //is an array
        string arrayName = tempDeclarationList->getChildSymbols()[0]->getName();
        string arrayLenString = tempDeclarationList->getChildSymbols()[2]->getName();
        int arrayLen = stoi(arrayLenString);

        scratchfile << arrayName << arrayLen <<  endl << endl;
		symbolTable.insert(createSymbolInfoForArrayID(arrayName, typeOfVariables, arrayLen));



    } else {
        //is a variable
        string variableName = tempDeclarationList->getChildSymbols()[0]->getName();
        scratchfile << variableName << endl<< endl;
		symbolTable.insert(createSymbolInfoForVariableID(variableName, typeOfVariables));

    }

	scratchfile << "Ending" << endl;
}


void symbolTableEntryForFunctionDeclaration(SymbolInfo* typeSpecifier, SymbolInfo* functionID, SymbolInfo* parameterList) {
	string functionType = typeSpecifier->getName();
}

#endif