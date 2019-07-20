
#ifndef UTILITYFUNCTIONS
#define UTILITYFUNCTIONS


#include <bits/stdc++.h>
#include "1605115_symboltable.h"

using namespace std;


extern int line_no;
extern int errorCount;
extern ofstream errorfile;
extern ofstream logfile;
extern ofstream scratchfile;
extern SymbolTable symbolTable;


void addLineNoErr() {
    errorfile << "At line No: " << line_no << " ";
    errorCount++;

}


void addLineNoLog() {
    logfile << "At line no: " << line_no << " ";

}


bool insertIDToSymbolTable(SymbolInfo* ID) {
    if( symbolTable.insert(ID)) {
        return true;
    } else {
        addLineNoErr();
        errorfile << "Multiple declarations of ID " << ID->getName() << " in the same scope" << endl << endl;
        return false;
    }
}

bool verifyIDIsDeclared(SymbolInfo* ID) {
   if(symbolTable.lookup(ID->getName()) != nullptr )  {
       return true;
   } else {
       addLineNoErr();
       errorfile << "Variable " << ID->getName() << " used without declaration";
       return false;
   }
}

bool verifyVariableIDIsDeclared(SymbolInfo* ID) {

    SymbolInfo* tableEntry = symbolTable.lookup(ID->getName());

    if( tableEntry == nullptr )  {
        addLineNoErr();
        errorfile << "Variable " << ID->getName() << " used without declaration\n\n";
        return false;
    } else if( tableEntry->isArray() )  {
        addLineNoErr();
        errorfile << "Array " << ID->getName() << " used without index\n\n";
        return false;
    } else if( tableEntry->isFunction()) {
        addLineNoErr();
        errorfile << "Function " << ID->getName() << " called without brackets and arguments\n\n";
        return false;
    } else if ( tableEntry->isVariable()) {
        return true;
    } else {
        addLineNoErr();
        errorfile << "ID " << ID->getName() << " is of unknown type\n\n";
        return false;
    }


}

bool checkIfValidFunctionReturnTypeInExpression(SymbolInfo* token) {

    //todo cal in parser. Will basically just check if token has return type void or not. Will have to be called in every grammar rule which isn't
    //of the form A -> B   in the chain from factor all the way up to expression.

    if(token->getReturnType() == "void") {
        addLineNoErr();
        errorfile << "Void function cannot be called as a part of an expression\n\n";
        return false;

    } else return true;
}


//handles MOD er dui side e int thakte hobe error
string evaluateReturnTypeForMULOP(SymbolInfo* term, SymbolInfo* MULOP, SymbolInfo* unaryExpression) {
    string termRetType = term->getReturnType();
    string expressionRetType = unaryExpression->getReturnType();
    string mulOp = MULOP->getName();

    string retType = "";  //defaults to int. Not sure how else to handle this.

    if(termRetType == "int" && expressionRetType == "int") {
        return "int";
    }

        if(mulOp == "%" ) {
            addLineNoErr();
            errorfile << "Both operand of modulus operator should be integer\n\n";
            return "int";
        }


        if(termRetType == "" || expressionRetType == "") {
            addLineNoErr();
            errorfile << "Expression return type not set/undefined \n\n";

            return "";
        }

        if(termRetType == "void" || expressionRetType == "void") {
            addLineNoErr();
            errorfile << "Void function cannot be called as a part of an expression \n\n";

            return "void";
        }

        return "float";
        //one or both are float






}




bool verifyArrayIDIsDeclared(SymbolInfo* ID) {

    SymbolInfo* tableEntry = symbolTable.lookup(ID->getName());

    if( tableEntry == nullptr )  {
        addLineNoErr();
        errorfile << "Array " << ID->getName() << " used without declaration\n\n";
        return false;
    } else if( tableEntry->isVariable() )  {
        addLineNoErr();
        errorfile << "Variable " << ID->getName() << " used with index. It is not an array\n\n";
        return false;
    } else if( tableEntry->isFunction()) {
        addLineNoErr();
        errorfile << "Function " << ID->getName() << " called with array index\n\n";
        return false;
    } else if ( tableEntry->isArray()) {
        return true;
    } else {
        addLineNoErr();
        errorfile << "ID " << ID->getName() << " is of unknown type\n\n";
        return false;
    }


}

string getReturnTypeOfSymbolTableEntry(string idName) {
    SymbolInfo* entry = symbolTable.lookup(idName);

    if(entry == nullptr) {
        return "";
    } else {
        return entry->getReturnType();
    }
}




SymbolInfo *deepCopySymbolInfo(SymbolInfo *oldCopy) {

    SymbolInfo* ret;

    if(oldCopy->isReturnTypeSet()) {
        ret = new SymbolInfo(oldCopy->getName(), oldCopy->getType(), oldCopy->getReturnType());

    } else {
       ret = new SymbolInfo(oldCopy->getName(), oldCopy->getType());

    }

    return ret;
}

SymbolInfo *createSymbolInfoForArrayID(string name, string type, int arrSize) {
    SymbolInfo *ret = new SymbolInfo(name, "ID");
    ret->initializeArray(type, arrSize);

    return ret;
}

SymbolInfo *createSymbolInfoForVariableID(string name, string type) {
    SymbolInfo *ret = new SymbolInfo(name, "ID");
    ret->initializeVariable(type);


    return ret;
}


void symbolTableEntryForVarDeclaration(SymbolInfo *typeSpecifier, SymbolInfo *declarationList) {

    string typeOfVariables = typeSpecifier->getName();
    if (typeOfVariables == "void") {
        addLineNoErr();
        errorfile << "variable(s) declared as type 'void' " << endl << endl;

    }


    vector<SymbolInfo *> variableNames;
    vector<SymbolInfo *> arrayNames;
    SymbolInfo *tempDeclarationList = declarationList;

//	scratchfile << typeSpecifier->getName() << " " << declarationList->getName() << endl;

    // scratchfile << declarationList->getChildSymbols()[0]->getType() << endl;


    while (tempDeclarationList->getChildSymbols()[0]->getType() == "declaration_list") {
        if (tempDeclarationList->getChildSymbols().size() > 5) {
            //is an array
            string arrayName = tempDeclarationList->getChildSymbols()[2]->getName();
            string arrayLenString = tempDeclarationList->getChildSymbols()[4]->getName();
            int arrayLen = stoi(arrayLenString);


           // scratchfile << arrayName << arrayLen << endl << endl;
            insertIDToSymbolTable(createSymbolInfoForArrayID(arrayName, typeOfVariables, arrayLen));


        } else {
            //is a variable
            //scratchfile <<(*tempDeclarationList).childSymbols.size() ;




            string variableName = tempDeclarationList->getChildSymbols()[2]->getName();
            //scratchfile << variableName << endl << endl;
            insertIDToSymbolTable(createSymbolInfoForVariableID(variableName, typeOfVariables));


        }


        tempDeclarationList = tempDeclarationList->getChildSymbols()[0];

    }


    if (tempDeclarationList->getChildSymbols().size() > 3) {
        //is an array
        string arrayName = tempDeclarationList->getChildSymbols()[0]->getName();
        string arrayLenString = tempDeclarationList->getChildSymbols()[2]->getName();
        int arrayLen = stoi(arrayLenString);

       // scratchfile << arrayName << arrayLen << endl << endl;
        insertIDToSymbolTable(createSymbolInfoForArrayID(arrayName, typeOfVariables, arrayLen));


    } else {
        //is a variable
        string variableName = tempDeclarationList->getChildSymbols()[0]->getName();
       // scratchfile << variableName << endl << endl;
        insertIDToSymbolTable(createSymbolInfoForVariableID(variableName, typeOfVariables));

    }

    //scratchfile << "Ending" << endl;
}


SymbolInfo*   createSymbolInfoForFunctionID(SymbolInfo *typeSpecifier, SymbolInfo *functionID, SymbolInfo *parameterList) {

    string functionRetType = typeSpecifier->getName();
    string functionName = functionID->getName();

    SymbolInfo *functionSymbolInfo = new SymbolInfo(functionName, "ID");
    functionSymbolInfo->initializeAsFunction(functionRetType);

    SymbolInfo *tempParameterList = parameterList;


    while (tempParameterList->getChildSymbols()[0]->getType() == "parameter_list") {
        if (tempParameterList->getChildSymbols().size() == 4) {
            //ID included
            string argType = tempParameterList->getChildSymbols()[2]->getName();
            string argName = tempParameterList->getChildSymbols()[3]->getName();

            if(argType == "void") {
                    addLineNoErr();
                    errorfile << "Function argument declared as type 'void' " << endl << endl;

            } else {
                functionSymbolInfo->getFunctionInfoDataPtr()->addArguments(argType, argName);
            }


        } else {
            //ID not included
            string argType = tempParameterList->getChildSymbols()[2]->getName();

            if(argType == "void") {
                addLineNoErr();
                errorfile << "Function argument declared as type 'void' " << endl << endl;

            } else {
                functionSymbolInfo->getFunctionInfoDataPtr()->addArguments(argType);
            }



        }
        tempParameterList = tempParameterList->getChildSymbols()[0];
    }

    if (tempParameterList->getChildSymbols().size() == 2) {
        //ID included
        string argType = tempParameterList->getChildSymbols()[0]->getName();
        string argName = tempParameterList->getChildSymbols()[1]->getName();

        if(argType == "void") {
            addLineNoErr();
            errorfile << "Function argument declared as type 'void' " << endl << endl;

        } else {
            functionSymbolInfo->getFunctionInfoDataPtr()->addArguments(argType, argName);
        }


    } else {
        //ID not included
        string argType = tempParameterList->getChildSymbols()[0]->getName();

        if(argType == "void") {
            addLineNoErr();
            errorfile << "Function argument declared as type 'void' " << endl << endl;

        } else {
            functionSymbolInfo->getFunctionInfoDataPtr()->addArguments(argType);
        }

    }

    return functionSymbolInfo; 
    
}




SymbolInfo*  createSymbolInfoForFunctionID(SymbolInfo *typeSpecifier, SymbolInfo *functionID) {

    string functionRetType = typeSpecifier->getName();
    string functionName = functionID->getName();

    SymbolInfo *functionSymbolInfo = new SymbolInfo(functionName, "ID");
    functionSymbolInfo->initializeAsFunction(functionRetType);




    return functionSymbolInfo;

}


void createSymbolTableEntryForFunctionID (SymbolInfo *typeSpecifier, SymbolInfo *functionID) {
    SymbolInfo* functionSymbolInfo = createSymbolInfoForFunctionID(typeSpecifier,functionID);
    insertIDToSymbolTable(functionSymbolInfo);
    symbolTable.printAllScopeTable(scratchfile);
    functionSymbolInfo->getFunctionInfoDataPtr()->print(scratchfile);
}



void createSymbolTableEntryForFunctionID (SymbolInfo *typeSpecifier, SymbolInfo *functionID, SymbolInfo *parameterList) {
    SymbolInfo* functionSymbolInfo = createSymbolInfoForFunctionID(typeSpecifier,functionID, parameterList);
    insertIDToSymbolTable(functionSymbolInfo);
    symbolTable.printAllScopeTable(scratchfile);
    functionSymbolInfo->getFunctionInfoDataPtr()->print(scratchfile);
}





bool checkFunctionSymbolInfoEquality(SymbolInfo* functionDefinitionSymbolInfo, SymbolInfo* functionDeclarationSymbolInfo) {

    if(!functionDeclarationSymbolInfo->isFunction() || !functionDefinitionSymbolInfo->isFunction()) {
        return false;
    }

    FunctionInfo* definitionFunctionInfo = functionDefinitionSymbolInfo->getFunctionInfoDataPtr();
    FunctionInfo* declarationFunctionInfo = functionDeclarationSymbolInfo->getFunctionInfoDataPtr();
    
    
    

    if(functionDefinitionSymbolInfo->getReturnType() != functionDeclarationSymbolInfo->getReturnType()) {
        return false;
    }

    if(declarationFunctionInfo->getArgumentsNumber() != definitionFunctionInfo->getArgumentsNumber()) {
        return false;
    }

    for(int i = 0; i < declarationFunctionInfo->getArgumentsNumber() ; i++) {
        if(declarationFunctionInfo->getArguments()[i].getArgumentType() != definitionFunctionInfo->getArguments()[i].getArgumentType() ) {
            return false;
        }
    }

    return true;
}

#endif