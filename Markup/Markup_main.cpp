/*
Allison Daniel
Due Date
Purpose: of the entire project
*/

#include "markup_header.hpp"
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

//using namespace std::filesystem;


using namespace std;

vector <string> args;
int wordCount[] = { 0,0,0,0,0 };
string colors[] = { "Green", "Red", "Blue", "Yellow","Purple" };                                                                               
int lineCount = 0;
int paraCount = 0;


int main(int argc, char** argv) {

	// 1. parse command line args
	bool colorize = false; 
	for (int i = 1; i < argc; ++i) // move argv to a vector, excluding the .exe name
	{
		args.push_back(argv[i]);
	}

	// if no args, quit
	if (args.empty())
	{
		cout << "no args provided\n";
		return 1;
	}

	// if --help, display help and quit
	vector<string>::iterator locator = find(args.begin(), args.end(), "--help");
	if (locator != args.end())
	{
		displayHelp();
		return 1;
	}

	//check for switches(-p -r -rp -pr)
	bool report = false;
	bool paragraph = false;
	string switches;
	
	if (args.at(0).at(0) == '-') //look for '-'
	{
		switches = args.front();
		args.erase(args.begin());
	}


	//r switch
	size_t r_index = switches.find('r');
	if (r_index != string::npos)
	{
		report = true;
		switches.erase(r_index, 1);
	}

	//p switch
	size_t p_index = switches.find('p');
	if (p_index != string::npos)
	{
		paragraph = true;
		switches.erase(p_index, 1);
	}

	cout << "res: " << report << endl;
	cout << "para: " << paragraph << endl;

	// check input file name
	string inFilename;
	if (!args.empty() && args.front() != "--keywords") {
		inFilename = args.front();
		args.erase(args.begin());
	}
	else {
		cout << "Error: text file not specified." << endl;
	}
	cout << "infile: " << inFilename << endl;

	// check output file name
	string outFilename;
	if (!args.empty() && args.front() != "--keywords") {
		outFilename = args.front();
		args.erase(args.begin());
	}
	else {
		outFilename = inFilename.substr(0, inFilename.find_last_of('.')) + ".html";
	}
	cout << "outfile: " << outFilename << endl;

	// Check for same input and output files
	if (outFilename == inFilename) {
		cout << "Error: input and output files are the same." << endl;
		return 1;
	}

	bool runKey = false;

	// check for --keywords
	if (!args.empty() && args.front() != "--keywords") {
		cout << "Error: too many command line arguments \"" << args.front() << "\"" << endl;
		return 1;
	}

	if (!args.empty() && args.front() == "--keywords") {
		args.erase(args.begin());
		if (args.empty()) {
			cout << "Error: keyword list is empty" << endl;
			return 1;
		}
		else {
			runKey = true;
		}

	}
	
	// check for actual words following
	if (!paragraph && !runKey) {
		ofstream myOutput;
		string body = runBreak(inFilename);
		if (body == "bad file") {
			return 1;
		}

		string header = createHeader(colors, args, inFilename);
		string footer = createFooter();
	
		myOutput.open(outFilename);
		if (myOutput) {
			myOutput << header << body << footer;
		}

		myOutput.close();
	}

	else if (paragraph && !runKey) {
		string body = runPara(inFilename);
		if (body == "bad file") {
			return 1;
		}

		ofstream myOutput;
		myOutput.open(outFilename);

		string header = createHeader(colors, args, inFilename);
		string footer = createFooter();

		if (myOutput) {
			myOutput << header << body << footer;
		}

		myOutput.close();
	}


	else if (runKey && paragraph) {
		string body = runPara(inFilename);
		stringstream text;
		text << body;
		string val = runKeyword(text);

		ofstream myOutput;
		myOutput.open(outFilename);

		string header = createHeader(colors, args, inFilename);
		cout << header;
		string footer = createFooter();

		if (myOutput) {
			myOutput << header << val << footer;
		}

		myOutput.close();
	}

	else {
		string body = runBreak(inFilename);
		stringstream text;
		text << body;
		string val = runKeyword(text);

		ofstream myOutput;
		myOutput.open(outFilename);

		string header = createHeader(colors, args, inFilename);
		string footer = createFooter();

		if (myOutput) {
			myOutput << header << val << footer;
		}

		myOutput.close();
	}

	if (report) {
		runReport();
	}

	
	return 0;

}
