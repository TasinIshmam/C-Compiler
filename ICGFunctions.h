#ifndef ICGFUNCTIONS
#define ICGFUNCTIONS

#include<bits/stdc++.h>

#include "1605115_symboltable.h"


using namespace std;

extern int line_no;
extern int errorCount;
extern ofstream logfile;
extern ofstream scratchfile;



extern int labelCount=0;
extern int temp_count=0;



//todo modify this function for checker
string to_string(int a)
{
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

string newLabel()
{
	string lb= "L" + to_string(labelCount);
	labelCount++;
	return lb;
}

string newTemp()
{
	string temp = "t" + to_string(temp_count);
	data_code = data_code + temp + " DW ?\n";
	temp_count++;
	return temp;
}



#endif