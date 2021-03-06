
#ifndef UTILITYFUNCTIONS
#define UTILITYFUNCTIONS


#include <bits/stdc++.h>
#include <string>
#include "1605115_symboltable.h"

using namespace std;


extern int line_no;
extern int errorCount;
extern ofstream logfile;
extern ofstream scratchfile;
extern SymbolTable symbolTable;

int labelCount = 0;
int tempCount = 0;




extern vector<string> variableDeclarationList;
extern vector<pair<string,string> >arrayDeclarationList;


extern	vector<SymbolInfo *> ArgumentListSymbolInfoVector;



string newLabel()
{
	string lb= "Label" + to_string( labelCount);
	labelCount++;
	return lb;
}

string generateNewTempVariable()
{
	string temp = "temp" + to_string(tempCount);
    variableDeclarationList.push_back(temp);
	tempCount++;
	return temp;
}


string generateAssemblyIdVariable(string name, int tableId ) {
return name + to_string(tableId);
}





string generateCodeForRelop(string expressionAssemblyId1 ,string relOperator ,string expressionAssemblyId2, string tempVariableForParentExpression) {
    
        string code = "";
		string label1 = newLabel();
		string label2 = newLabel();
		code += "MOV AX," + expressionAssemblyId1 + "\n";
		code += "CMP AX," + expressionAssemblyId2 + "\n";
		
        if (relOperator == "<")
		{
			code += "JL " + label1 + "\n";
		}
		else if (relOperator == ">")
		{
			code += "JG " + label1 + "\n";
		}
		else if (relOperator == "<=")
		{
			code += "JLE " + label1 + "\n";
		}
		else if (relOperator == ">=")
		{
			code += "JGE " + label1 + "\n";
		}
		else if (relOperator == "==")
		{
			code += "JE " + label1 + "\n";
		}
		else if (relOperator == "!=")
		{
			code += "JNE " + label1 + "\n";
		}
		code += "MOV " + tempVariableForParentExpression + ",0\n";
		code += "JMP " + label2 + "\n";
		code += label1 + ":\n";
		code += "MOV " + tempVariableForParentExpression + ",1\n";
		code += label2 + ":\n";
		
        return code;


}


string generateCodeForLogicOp(string expressionAssemblyId1 ,string logicOperator ,string expressionAssemblyId2, string tempVariableForParentExpression) {
        
        string code = "";

        string label1 = newLabel();
		string label2 = newLabel();
		string label3 = newLabel();

        if (logicOperator == "||") {
			code += "MOV AX," +expressionAssemblyId1 + "\n";
			code += "CMP AX,0\n";
			code += "JNE " + string(label2) + "\n";
			code += "MOV AX," + expressionAssemblyId2 + "\n";
			code += "CMP AX,0\n";
			code += "JNE " + label2 + "\n";
			code += label1 + ":\n";
			code += "MOV " + tempVariableForParentExpression + ",0\n";
			code += "JMP " + label3 + "\n";
			code += label2 + ":\n";
			code += "MOV " + tempVariableForParentExpression + ",1\n";
			code += label3 + ":\n";
		} else if (logicOperator == "&&")
		{
			code += "MOV AX," + expressionAssemblyId1 + "\n";
			code += "CMP AX,0\n";
			code += "JE " + label2 + "\n";
			code += "MOV AX," + expressionAssemblyId2 + "\n";
			code += "CMP AX,0\n";
			code += "JE " + label2 + "\n";
			code += label1 + ":\n";
			code += "MOV " + tempVariableForParentExpression + ",1\n";
			code += "JMP " + label3 + "\n";
			code += label2 + ":\n";
			code += "MOV " + tempVariableForParentExpression + ",0\n";
			code += label3 + ":\n";
		}

        return code;

}


void addLineNoErr() {
    logfile << "Error At line No: " << line_no << " ";
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
        logfile << "Multiple declarations of ID " << ID->getName() << " in the same scope" << endl << endl;
        return false;
    }
}

bool verifyIDIsDeclared(SymbolInfo* ID) {
   if(symbolTable.lookup(ID->getName()) != nullptr )  {
       return true;
   } else {
       addLineNoErr();
       logfile << "Variable " << ID->getName() << " used without declaration";
       return false;
   }
}

bool verifyVariableIDIsDeclared(SymbolInfo* ID) {

    SymbolInfo* tableEntry = symbolTable.lookup(ID->getName());

    if( tableEntry == nullptr )  {
        addLineNoErr();
        logfile << "Variable " << ID->getName() << " used without declaration\n\n";
        return false;
    } else if( tableEntry->isArray() )  {
        addLineNoErr();
        logfile << "Array " << ID->getName() << " used without index\n\n";
        return false;
    } else if( tableEntry->isFunction()) {
        addLineNoErr();
        logfile << "Function " << ID->getName() << " called without brackets and parameters\n\n";
        return false;
    } else if ( tableEntry->isVariable()) {
        return true;
    } else {
        addLineNoErr();
        logfile << "ID " << ID->getName() << " is of unknown type\n\n";
        return false;
    }


}

bool functionCallValidationWithArgumentTypeCheck(SymbolInfo* id, SymbolInfo* argumentList) {

    SymbolInfo* tableEntry = symbolTable.lookup(id->getName());

    if(tableEntry == nullptr) {
        addLineNoErr();
        logfile << "Function called without declaration\n\n";
        return false;
    }

    if(!tableEntry->isFunction()) {
        addLineNoErr();
        logfile << "Function call made with non-function type identifer " << tableEntry->getName() << "\n\n";
    }

    vector<SymbolInfo *> functionCallArgumentExpressionVect;


    if(argumentList->getChildSymbols().size() > 0) {  //some arguments are present
        SymbolInfo* tempArguments = argumentList->getChildSymbols()[0];

        while(tempArguments->getChildSymbols()[0]->getType() == "arguments"){
            functionCallArgumentExpressionVect.push_back(tempArguments->getChildSymbols()[2]);

            tempArguments = tempArguments -> getChildSymbols()[0];
        }

        functionCallArgumentExpressionVect.push_back(tempArguments->getChildSymbols()[0]);



    }

    if(functionCallArgumentExpressionVect.size() != tableEntry->getFunctionInfoDataPtr()->getArguments().size()) {
        addLineNoErr();
        logfile << "Number of arguments in call do not match function definition\n\n";
        return false;
    }

    for(int i = 0; i < functionCallArgumentExpressionVect.size(); i++) {

        if(functionCallArgumentExpressionVect[i]->getReturnType() != tableEntry->getFunctionInfoDataPtr()->getArguments()[i].getArgumentType()) {
            addLineNoErr();
            logfile << "Type of argument(s) in function call do not match function definition\n\n";
            return false;
        }
    }

    return true;


    //  while(tempArguments->getChildSymbols()[0]->getType() == "declaration_list");



}

bool checkIfValidFunctionReturnTypeInExpression(SymbolInfo* token) {

    

    if(token->getReturnType() == "void") {
        addLineNoErr();
        logfile << "Void function cannot be called as a part of an expression\n\n";
        return false;

    } else if(  token->getReturnType() == "") {

        addLineNoErr();
        logfile << "Expression return type not set/undefined\n\n";
        return false;
    } else return true;
}


//handles MOD er dui side e int thakte hobe error
string evaluateReturnTypeForMULOP(SymbolInfo* term, SymbolInfo* MULOP, SymbolInfo* unaryExpression) {
    string termRetType = term->getReturnType();
    string expressionRetType = unaryExpression->getReturnType();
    string mulOp = MULOP->getName();

    string retType = "int";  //defaults to int. Not sure how else to handle this.

    if(termRetType == "int" && expressionRetType == "int") {
        return "int";
    }

        if(mulOp == "%" ) {
            addLineNoErr();
            logfile << "Both operand of modulus operator should be integer\n\n";
            return "int";
        }


        if(termRetType == "" || expressionRetType == "") {
            addLineNoErr();
            logfile << "Expression return type not set/undefined \n\n";

            return "invalid";
        }

        if(termRetType == "void" || expressionRetType == "void") {
            addLineNoErr();
            logfile << "Void function cannot be called as a part of an expression \n\n";

            return "invalid";
        }

        return "float";
        //one or both are float


}


string evaluateReturnTypeForADDOP(SymbolInfo* simpleExpression, SymbolInfo* term) {

    string termRetType = term->getReturnType();
    string expressionRetType = simpleExpression->getReturnType();

    string retType = "";  //defaults to int. Not sure how else to handle this.

    if(termRetType == "int" && expressionRetType == "int") {
        return "int";
    }



    if(termRetType == "" || expressionRetType == "") {
        addLineNoErr();
        logfile << "Expression return type not set/undefined \n\n";

        return "invalid";
    }

    if(termRetType == "void" || expressionRetType == "void") {
        addLineNoErr();
        logfile << "Void function cannot be called as a part of an expression \n\n";

        return "invalid";
    }

    return "float";
    //one or both are float


}

bool evaluateTypeConsistencyForOperands(SymbolInfo* operand1, SymbolInfo* operand2) {

    if(operand1->getReturnType() != "int" && operand1->getReturnType() != "float" ) {
        addLineNoErr();
        logfile << "Expression return type not set/undefined \n\n";
        return false;
    }

    if(operand2->getReturnType() != "int" && operand2->getReturnType() != "float" ) {
        addLineNoErr();
        logfile << "Expression return type not set/undefined \n\n";
        return false;
    }

    return true;
}

void evaluateTypeConversionForASSIGNOP(SymbolInfo* leftHandTerm, SymbolInfo* rightHandTerm ) {
    string leftType = leftHandTerm->getReturnType();
    string rightType = rightHandTerm->getReturnType();

   

  

    if(leftType == "int" && rightType == "float") {
        addLineNoErr();
        logfile << "Type mismatch. Floating point expression assigned to integer type variable\n\n";
        return;
    }

    if(leftType == "float" && rightType == "int") {
        return;
    }

    if(leftType == "void" || rightType == "void") {
        addLineNoErr();
        logfile << "Void function cannot be called as a part of an expression \n\n";
        return;
    }

    if(leftType == "" || rightType == "") {
        addLineNoErr();
        logfile << "Expression return type not set/undefined \n\n";
        return;
    }

//    if(leftType == "invalid" || rightType == "invalid") {
//        addLineNoErr();
//        logfile << "Expression return type not set/undefined \n\n";
//        return;
//    }


}



bool verifyArrayIDIsDeclared(SymbolInfo* ID) {

    SymbolInfo* tableEntry = symbolTable.lookup(ID->getName());

    if( tableEntry == nullptr )  {
        addLineNoErr();
        logfile << "Array " << ID->getName() << " used without declaration\n\n";
        return false;
    } else if( tableEntry->isVariable() )  {
        addLineNoErr();
        logfile << "Variable " << ID->getName() << " used with index. It is not an array\n\n";
        return false;
    } else if( tableEntry->isFunction()) {
        addLineNoErr();
        logfile << "Function " << ID->getName() << " called with array index\n\n";
        return false;
    } else if ( tableEntry->isArray()) {
        return true;
    } else {
        addLineNoErr();
        logfile << "ID " << ID->getName() << " is of unknown type\n\n";
        return false;
    }


}

string getReturnTypeOfSymbolTableEntry(string idName) {
    SymbolInfo* entry = symbolTable.lookup(idName);

    if(entry == nullptr) {
        return "invalid";
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
        logfile << "variable(s) declared as type 'void' " << endl << endl;

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
            SymbolInfo* arr = createSymbolInfoForArrayID(arrayName, typeOfVariables, arrayLen);
         insertIDToSymbolTable(arr);

        
            string assemblyID = generateAssemblyIdVariable(arr->getName(), symbolTable.getCurrentScope()->getUniqueTableNumber());

            arr->setAssemblyID(assemblyID);
            arrayDeclarationList.push_back(make_pair(assemblyID,  arrayLenString) );

        } else {
            //is a variable
            //scratchfile <<(*tempDeclarationList).childSymbols.size() ;




            string variableName = tempDeclarationList->getChildSymbols()[2]->getName();
            //scratchfile << variableName << endl << endl;

            SymbolInfo* var = createSymbolInfoForVariableID(variableName, typeOfVariables);
            insertIDToSymbolTable(var);

            string assemblyID = generateAssemblyIdVariable(var->getName(), symbolTable.getCurrentScope()->getUniqueTableNumber());

            var->setAssemblyID(assemblyID);
            variableDeclarationList.push_back(assemblyID);






        }


        tempDeclarationList = tempDeclarationList->getChildSymbols()[0];

    }


    if (tempDeclarationList->getChildSymbols().size() > 3) {
        //is an array
        string arrayName = tempDeclarationList->getChildSymbols()[0]->getName();
        string arrayLenString = tempDeclarationList->getChildSymbols()[2]->getName();
        int arrayLen = stoi(arrayLenString);


       //scratchfile << arrayName << arrayLen << endl << endl;
       SymbolInfo* arr = createSymbolInfoForArrayID(arrayName, typeOfVariables, arrayLen);

                insertIDToSymbolTable(arr);

            string assemblyID = generateAssemblyIdVariable(arr->getName(), symbolTable.getCurrentScope()->getUniqueTableNumber());

           arr->setAssemblyID(assemblyID);
           arrayDeclarationList.push_back(make_pair(assemblyID,  arrayLenString) );



    } else {
        //is a variable
        string variableName = tempDeclarationList->getChildSymbols()[0]->getName();
       // scratchfile << variableName << endl << endl;
         SymbolInfo* var = createSymbolInfoForVariableID(variableName, typeOfVariables);
            insertIDToSymbolTable(var);

            string assemblyID = generateAssemblyIdVariable(var->getName(), symbolTable.getCurrentScope()->getUniqueTableNumber());

            var->setAssemblyID(assemblyID);
            variableDeclarationList.push_back(assemblyID);
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
                    logfile << "Function argument declared as type 'void' " << endl << endl;

            } else {
                functionSymbolInfo->getFunctionInfoDataPtr()->addArguments(argType, argName);
            }


        } else {
            //ID not included
            string argType = tempParameterList->getChildSymbols()[2]->getName();

            if(argType == "void") {
                addLineNoErr();
                logfile << "Function argument declared as type 'void' " << endl << endl;

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
            logfile << "Function argument declared as type 'void' " << endl << endl;

        } else {
            functionSymbolInfo->getFunctionInfoDataPtr()->addArguments(argType, argName);
        }


    } else {
        //ID not included
        string argType = tempParameterList->getChildSymbols()[0]->getName();

        if(argType == "void") {
            addLineNoErr();
            logfile << "Function argument declared as type 'void' " << endl << endl;

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
   // symbolTable.printAllScopeTable(scratchfile);
    //functionSymbolInfo->getFunctionInfoDataPtr()->print(scratchfile);
}



void createSymbolTableEntryForFunctionID (SymbolInfo *typeSpecifier, SymbolInfo *functionID, SymbolInfo *parameterList) {
    SymbolInfo* functionSymbolInfo = createSymbolInfoForFunctionID(typeSpecifier,functionID, parameterList);
    insertIDToSymbolTable(functionSymbolInfo);
    //symbolTable.printAllScopeTable(scratchfile);
    //functionSymbolInfo->getFunctionInfoDataPtr()->print(scratchfile);
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




// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

string findCmd(string line)
{
	int i = 0;
	int len = line.size();
	// while(line[i]!=' ') i++;

	for(i = 0; line[i]!=' '; i++) {

		if(i >= len) {
			return "";
		}
	}
	return line.substr(0,i);
}


string findDestArg(string line)
{
	int i=0;
	int len = line.size();
	// while(line[i]!=' ') i++;

	for(i = 0; line[i]!=' '; i++) {

		if(i >= len) {
			return "";
		}
	}
	i++;
	int j = i + 1;
	
	//while(line[j] != ',' && j<line.size()) j++;

	for( ; line[j] != ',' ; j++) {
		
		if(j >= line.size()) {
			return "";
		}
	}
	return trim_copy(line.substr(i, j-i));
}


string findSrcArg(string line)
{
	int len = line.size();
	int i = 0;
	//while(line[i] != ',') i++;

		for(i = 0; line[i]!= ','; i++) {

		if(i >= len) {
			return "";
		}
	}

	i += 1;
	return trim_copy(line.substr(i, len-i));
}

void optimizeCode()
{	

	ifstream inputStream("code.asm");
	ofstream outputStream("optimized-code.asm");

	
	string prevLine = "";
	string currentLine = "";

	while(1) {
	getline(inputStream, prevLine);
	
	if(!inputStream) {
		inputStream.close();
		outputStream.close();
		 return;
	}
	
	if(prevLine != "") break;

	}



	outputStream << prevLine << endl;
	

	while(1)
	{
		getline(inputStream, currentLine);
		
		if(!inputStream) {
		inputStream.close();
		outputStream.close();
		 return;
		}
		
		if(currentLine == "") {
			continue;
		}

		
		// cout << "\nLine: " << currentLine << endl;
		// cout << "CMD: " << findCmd(currentLine) << endl;
		// cout << "Source Arg: " << findSrcArg(currentLine) << endl;
		// cout << "Dest Arg: " << findDestArg(currentLine) << "\n\n";


		if(findCmd(prevLine) == "MOV" && findCmd(currentLine) == "MOV")
		{	
			
			if(findSrcArg(prevLine) == findDestArg(currentLine) && findSrcArg(currentLine) == findDestArg(prevLine))
			{
				// discard new line
				outputStream << ";Line Omitted for optimization" << endl;

				//cout << "\nShit detected yo\n";
				//cout << currentLine << endl;
				
				continue;
			}
		}
		
		outputStream << currentLine << endl;

		prevLine = currentLine;
		
	}

	
			return;

	
}


#endif