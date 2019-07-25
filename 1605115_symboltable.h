#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include<bits/stdc++.h>

using namespace std;

extern int line_no;
extern int errorCount;
extern ofstream errorfile;
extern ofstream logfile;
extern ofstream scratchfile;

class ArgumentInfo {

    string argumentType, argumentName;

public:

    ArgumentInfo(const string &argumentType, const string &argumentName) : argumentType(argumentType),
                                                                           argumentName(argumentName) {}


    ArgumentInfo(const string &argumentType) : argumentType(argumentType){
        argumentName = "";
    }


    const string &getArgumentType() const {
        return argumentType;
    }

    void setArgumentType(const string &argumentType) {
        ArgumentInfo::argumentType = argumentType;
    }

    const string &getArgumentName() const {
        return argumentName;
    }

    void setArgumentName(const string &argumentName) {
        ArgumentInfo::argumentName = argumentName;
    }
};



class ArrayInfo {

    int arraySize = -1;

public:

    ArrayInfo( int arrSize)  {
        arraySize = arrSize;
    }


    int getArraySize() {
        return arraySize;
    }





};


class FunctionInfo {
    vector<ArgumentInfo> arguments;

public:
    FunctionInfo()  {

    }

    const vector<ArgumentInfo> &getArguments() const {
        return arguments;
    }

    void addArguments(const string &argumentType, const string &argumentName) {

        ArgumentInfo argumentInfo(argumentType, argumentName);
        arguments.push_back(argumentInfo);
    }

    void addArguments(const string &argumentType) {
        ArgumentInfo argumentInfo(argumentType);
        arguments.push_back(argumentInfo);
    }

    void addArguments(ArgumentInfo argumentInfo) {
        arguments.push_back(argumentInfo);


    }



    int getArgumentsNumber() {
        return arguments.size();
    }

    void print(ofstream& out) {
        out << "Arguments: \n";
        for (int i = 0; i < arguments.size() ; i++) {
            out << arguments[i].getArgumentType() << "  " << arguments[i].getArgumentName() << endl;
        }
    }



};



class SymbolInfo {
private:
    string name, type;
    SymbolInfo *nextPtr;
    vector<SymbolInfo*> childSymbols;
    bool isVariableType = false;
    ArrayInfo* arrayDataPtr;
    FunctionInfo* functionDataPtr;
    string returnType = "";

public:

    bool isVariable() {
       return isVariableType;
    }

    bool isArray() {
        if(arrayDataPtr != nullptr) {
            return true;
        } else {
            return false;
        }

    }

    bool isFunction() {
        if(functionDataPtr != nullptr) {
            return true;
        } else {
            return false;
        }

    }

    bool isID() {
        return isVariable() || isArray() || isFunction();
    }



    void initializeVariable (const string &variableType) {
        isVariableType = true;
       this->setReturnType(variableType);
    }

    ArrayInfo* getArrayInfoPtr() {
        return arrayDataPtr;
    }

    void initializeArray(const string &variableType, int arrSize) {
        arrayDataPtr = new ArrayInfo( arrSize);
        this->setReturnType(variableType);
    }

    FunctionInfo* getFunctionInfoDataPtr() {
        return functionDataPtr;
    }

    void initializeAsFunction(const string &returnType ) {
        functionDataPtr = new FunctionInfo();
        this->setReturnType(returnType);
    }

    bool isReturnTypeSet() {
        if(returnType == "") {
            return false;
        } else return true;
    }



    SymbolInfo(const string &name, const string &type) : name(name), type(type) {
        nextPtr = nullptr;
        functionDataPtr = nullptr;
        returnType = "";
        isVariableType = false;

    }

    SymbolInfo(const string &name, const string &type, const string &returnType) : name(name), type(type), returnType(returnType) {
        nextPtr = nullptr;
        functionDataPtr = nullptr;
        isVariableType = false;



    }

    virtual ~SymbolInfo() {
        delete nextPtr;
        delete arrayDataPtr;
        delete functionDataPtr;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        SymbolInfo::name = name;
    }

    const string &getType() const {
        return type;
    }

    void setType(const string &type) {
        SymbolInfo::type = type;
    }

    const string &getReturnType() const {
        return returnType;
    }

    void setReturnType(const string &retType) {
        SymbolInfo::returnType = retType;

        if(!isFunction() && retType == "void") {
            // cout << name << " of type " << type << " return type set to void\n";
        }

        if (retType == "") {
            // cout << name << " of type " << type << " return type set to empty\n";

        }

        scratchfile <<  name << " of type " << type << " return type set to " << retType << "\n";
    }

    SymbolInfo *getNext() const {
        return nextPtr;
    }

    void setNext(SymbolInfo *next) {
        SymbolInfo::nextPtr = next;
    }

    void addChildSymbol(SymbolInfo* child) {
        childSymbols.push_back(child);


    }

    void setChildSymbolVector(vector<SymbolInfo*> argchildSymbols) {
        childSymbols = argchildSymbols;
    }

    vector<SymbolInfo*> &getChildSymbols(){
        return childSymbols;
    }
};


class ScopeTable {
    SymbolInfo **hashTable;
    ScopeTable *parentScopeTable;
    int tableId, tableSize;

public:


    ScopeTable(int tableSize, int table_id) {
        hashTable = (SymbolInfo **) malloc(tableSize * sizeof(SymbolInfo *));
        for (int i = 0; i < tableSize; i++) {
            hashTable[i] = nullptr;
        }
        parentScopeTable = nullptr;
        this->tableId = table_id;
        this->tableSize = tableSize;
    }


    virtual ~ScopeTable() {
        for (int i = 0; i < tableSize; i++) {
            delete hashTable[i];
        }
        delete hashTable;
    }

    SymbolInfo **getHashTable() const {
        return hashTable;
    }

    void setHashTable(SymbolInfo **hashTable) {
        ScopeTable::hashTable = hashTable;
    }

    ScopeTable *getParentScopreTable() const {
        return parentScopeTable;
    }

    void setParentScopreTable(ScopeTable *parentScopreTable) {
        ScopeTable::parentScopeTable = parentScopreTable;
    }

    int getTableId() const {
        return tableId;
    }

    void setTableId(int tableId) {
        ScopeTable::tableId = tableId;
    }

    int getTableSize() const {
        return tableSize;
    }

    void setTableSize(int tableSize) {
        ScopeTable::tableSize = tableSize;
    }

    int getHash(string key) {
        int hash = 0;

        for (char i : key) {
            hash = hash + (int) i << 2;
        }

        hash = hash % tableSize;

        return hash;

    }



    SymbolInfo *lookUp(const string &itemName) {
        int hash = getHash(itemName);
        int counter = 0;

        if (hashTable[hash] == nullptr) {
            // cout << "\nSymbol Not found in Scopetable# " << tableId << endl;
            return nullptr;
        } else {

            SymbolInfo *iter = hashTable[hash];

            while (iter != nullptr) {


                if (iter->getName() == itemName) {
                    // cout << "\nFound in ScopeTable# "
                      //   << tableId << " at position " << hash << ", " << counter << "\n";
                    return iter;

                }
                iter = iter->getNext();
                counter++;
            }

            // cout << "\nSymbol Not found in Scopetable# " << tableId << endl;
            return nullptr;
        }

    }

    bool insert(SymbolInfo *item) {
        int hash = getHash(item->getName());
        int counter = 0;


        if (hashTable[hash] == nullptr) {
            hashTable[hash] = item;
            // cout << "\nInserted in ScopeTable# " << tableId << " at position " << hash << ", " << counter << "\n";

            return true;
        } else {
            SymbolInfo *iter = hashTable[hash];

            if (iter->getName() == item->getName() && iter->getType() == item->getType()) {
              //   cout << "\n<" << iter->getName() << "," << iter->getType() << ">already exists in ScopeTable# " << tableId << endl;
                return false;
            }

            SymbolInfo *prev = hashTable[hash];
            iter = iter->getNext();
            counter++;


            while (iter != nullptr) {

                if (iter->getName() == item->getName() && iter->getType() == item->getType()) {
                //       cout << "\n<" << iter->getName() << "," << iter->getType() << ">already exists in ScopeTable# " << tableId << endl;
                    return false;
                }

                iter = iter->getNext();
                prev = prev->getNext();
                counter++;
            }

            prev->setNext(item);
            //cout << "\nInserted in ScopeTable# " << tableId << " at position " << hash << ", " << counter << "\n";
            return true;
        }
    }

    bool deleteItem(const string &itemName) {
        int hash = getHash(itemName);
        int counter = 0;

        if (hashTable[hash] == nullptr) {
            // cout << "\nCould not delete. Symbol Not found in Scopetable# " << tableId << endl;
            return false;
        } else {

            SymbolInfo *prev = hashTable[hash];
            SymbolInfo *iter = prev->getNext();


            if (prev->getName() == itemName) {
                hashTable[hash] = iter;
                delete prev;
                cout << "\nDeleted from ScopeTable# "
                     << tableId << " at position " << hash << ", " << counter << "\n";
                return true;

            }

            counter++;

            while (iter != nullptr) {


                if (iter->getName() == itemName) {
                    prev->setNext(iter->getNext());
                    delete iter;
                    // cout << "\nDeleted from ScopeTable# "
                        // << tableId << " at position " << hash << ", " << counter << "\n";
                    return true;

                }

                iter = iter->getNext();
                prev = prev->getNext();
                counter++;
            }

            // cout << "\nCould not delete. Symbol Not found in Scopetable# " << tableId << endl;
            return false;
        }

    }

    void print() {
        // cout << "\n ScopeTable # " << tableId << endl;

        for (int i = 0; i < tableSize; i++) {
            // cout << " " << i << "--> ";

            SymbolInfo *iter = hashTable[i];

            while (iter != nullptr) {
                // cout << " < " << iter->getName() << " : " << iter->getType() << "> ";
                iter = iter->getNext();
            }
            // cout << endl;
        }
    }

    void print(ofstream& out) {
        out << "\n ScopeTable # " << tableId << endl;

        for (int i = 0; i < tableSize; i++) {
            out << " " << i << "--> ";

            SymbolInfo *iter = hashTable[i];

            while (iter != nullptr) {
                out << " < " << iter->getName() << " : " << iter->getType() << "> ";
                iter = iter->getNext();
            }
            out << endl;
        }
    }


};



class SymbolTable {
private:
    ScopeTable *currentScope;
    int bucketSizeForTables;

    int scopeDepth;
public:
    virtual ~SymbolTable() {
        delete currentScope;
    }


    bool containsWhiteSpace(const string &entry) {
        for(int i = 0; i < entry.size(); i++) {
            if(isspace(entry[i])) {
                return true;
            }
        }

        return false;
    }



    SymbolTable(int buckets) {
        scopeDepth = 1;
        this->bucketSizeForTables = buckets;

        currentScope = new ScopeTable(buckets, scopeDepth++);
    }

    void printAllScopeTable() {
        ScopeTable *temp = currentScope;

        while (temp != nullptr) {
            temp->print();
            temp = temp->getParentScopreTable();
        }
    }

    void printAllScopeTable(ofstream& out) {
        ScopeTable *temp = currentScope;

        while (temp != nullptr) {
            temp->print(out);
            temp = temp->getParentScopreTable();
        }
    }




    SymbolInfo *lookup(const string &name) {
        if(containsWhiteSpace(name)) {
            scratchfile << "Warning: Cannot look up name with white space in it. Cancelling lookup and returning nullptr for search string: " << name << endl << endl;
            // cout << "Warning: Cannot look up name with white space in it. Cancelling lookup and returning nullptr for search string: " << name << endl << endl;
            return nullptr;
        }
        ScopeTable *temp = currentScope;

        while (temp != nullptr) {
            SymbolInfo *res = temp->lookUp(name);

            if (res != nullptr) {
                return res;
            }

            temp = temp->getParentScopreTable();
        }

        return nullptr;
    }

    int getBucketSizeForTables() const {
        return bucketSizeForTables;
    }

    void setBucketSizeForTables(int bucketSizeForTables) {
        SymbolTable::bucketSizeForTables = bucketSizeForTables;
    }


    ScopeTable *getCurrentScope() const {
        return currentScope;
    }

    void setCurrentScope(ScopeTable *currentScope) {
        SymbolTable::currentScope = currentScope;
    }

    void enterScope() {
        auto *newScopeTable = new ScopeTable(bucketSizeForTables, scopeDepth++);
        newScopeTable->setParentScopreTable(currentScope);
        currentScope = newScopeTable;

        // cout << "\n New ScopeTable with id " << currentScope->getTableId() << " created\n";
    }

    void exitScope() {
        ScopeTable *temp = currentScope;
        // cout << "\nScopeTable with id " << currentScope->getTableId() << " removed\n";

        currentScope = currentScope->getParentScopreTable();
        delete temp;
        scopeDepth--;

    }

    bool insert(SymbolInfo *token) {
        return currentScope->insert(token);
    }

    bool remove(const string &name) {
        return currentScope->deleteItem(name);
    }

    void printCurrentScopeTable() {
        return currentScope->print();
    }

    void printCurrentScopeTable(ofstream& out) {
        return currentScope->print(out);
    }





};


#endif
