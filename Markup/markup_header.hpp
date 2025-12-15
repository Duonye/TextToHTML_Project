
/*

Allison Daniel
Due Date
Purpose: declare functions, define structs

*/

#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

extern vector <string> args;
extern int wordCount[];
extern string colors[];
extern int lineCount;
extern int paraCount;

//define struct


// declare functions

/*
name: createFooter()
purpose: Creates a footer for a document.
parameter: none
return: footer.str()
*/
string createFooter();

/*
name: createHeader
purpose:  Create a header for a document using an array of colors, a vector of words, and a file name.
parameter: string col[], vector <string> words, string fileName
return: header.str()
*/
string createHeader(string col[], vector <string> words, string fileName);

/*
name: runBreak
purpose: Perform a line break on a specified input file.
parameter: string infilename
return:  buff.str()
*/
string runBreak(string infilename);

/*
name: runPara
purpose: Perform paragraph formatting on a specified input file.
parameter: string infilename
return: buff.str()
*/
string runPara(string infilename);

/*
name: runKeyword
purpose: To extract a keyword from a stringstream object.
parameter: stringstream & input
return: myOutput.str()
*/
string runKeyword(stringstream & input);

/*
name: runReport()
purpose: To run a report
parameter: none
return: none
*/
void runReport();

/*
name: displayHelp()
purpose: To display help information
parameter: none
return: none
*/
void displayHelp(); 
