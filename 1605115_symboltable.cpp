#include<bits/stdc++.h>

using namespace std;

class SymbolInfo {
private:
    string name, type;
    SymbolInfo *nextPtr;

public:


    SymbolInfo(const string &name, const string &type) : name(name), type(type) {
        nextPtr = nullptr;
    }

    virtual ~SymbolInfo() {
        delete nextPtr;
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

    SymbolInfo *getNext() const {
        return nextPtr;
    }

    void setNext(SymbolInfo *next) {
        SymbolInfo::nextPtr = next;
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
            cout << "\nSymbol Not found in Scopetable# " << tableId << endl;
            return nullptr;
        } else {

            SymbolInfo *iter = hashTable[hash];

            while (iter != nullptr) {


                if (iter->getName() == itemName) {
                    cout << "\nFound in ScopeTable# "
                         << tableId << " at position " << hash << ", " << counter << "\n";
                    return iter;

                }
                iter = iter->getNext();
                counter++;
            }

            cout << "\nSymbol Not found in Scopetable# " << tableId << endl;
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
               // cout << "\n<" << iter->getName() << "," << iter->getType() << ">already exists in ScopeTable# " << tableId << endl;
                return false;
            }

            SymbolInfo *prev = hashTable[hash];
            iter = iter->getNext();
            counter++;


            while (iter != nullptr) {

                if (iter->getName() == item->getName() && iter->getType() == item->getType()) {
                //    cout << "\n<" << iter->getName() << "," << iter->getType() << ">already exists in ScopeTable# " << tableId << endl;
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
            cout << "\nCould not delete. Symbol Not found in Scopetable# " << tableId << endl;
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
                    cout << "\nDeleted from ScopeTable# "
                         << tableId << " at position " << hash << ", " << counter << "\n";
                    return true;

                }

                iter = iter->getNext();
                prev = prev->getNext();
                counter++;
            }

            cout << "\nCould not delete. Symbol Not found in Scopetable# " << tableId << endl;
            return false;
        }

    }

    void print() {
        cout << "\n ScopeTable # " << tableId << endl;

        for (int i = 0; i < tableSize; i++) {
            cout << " " << i << "--> ";

            SymbolInfo *iter = hashTable[i];

            while (iter != nullptr) {
                cout << " < " << iter->getName() << " : " << iter->getType() << "> ";
                iter = iter->getNext();
            }
            cout << endl;
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

        cout << "\n New ScopeTable with id " << currentScope->getTableId() << " created\n";
    }

    void exitScope() {
        ScopeTable *temp = currentScope;
        cout << "\nScopeTable with id " << currentScope->getTableId() << " removed\n";

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


