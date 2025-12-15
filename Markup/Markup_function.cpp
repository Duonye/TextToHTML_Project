/*

Allison Daniel
Due Date
Purpose: implementation of functions

*/


#include "markup_header.hpp" // include the header file

using namespace std;

    // Create footer function that creates the footer for an HTML document
    string createFooter() {
        stringstream footer;
        footer << "</body>" << '\n' << "</html>";

        return footer.str();
    }

    // Create header function that creates the header for an HTML document
    string createHeader(string col[], vector <string> words, string fileName) {
        string fName = fileName.substr(0, fileName.find_last_of('.'));
        stringstream header;
        if (words.size() == 0) {
            header << "<!DOCTYPE html>" << '\n' << "<html>" << '\n' << "<head>" <<
                '\n' << "<title>" << fName << "</title>" << '\n' << "<style>" << '\n' << '\n' << "</style>" << '\n' <<
                "</head>" << '\n' << "<body>" << '\n';
        }

        else {
            int len = words.size();

            header << "<!DOCTYPE html>" << '\n' << "<html>" << '\n' << "<head>" <<
                '\n' << "<title>" << fName << "</title>" << '\n' << "<style>" << '\n';
            
            // Loop through each keyword and color and add a style for the keyword
            for (int i = 0; i < len; i++) {
                header << "key-" << col[i] << " { color : " << col[i] << " }" << '\n';
            }

            header << "</style>" << '\n' << "</head>" << '\n' << "<body>" << '\n';
        }

        return header.str();

    }

    // Run break function that replaces line breaks with HTML line break tags
    string runBreak(string infilename) {

        string line;
        char ch;

        char prevch = '0';

        ifstream myInput;
        stringstream buff;

        myInput.open(infilename);

        // Read each line of the input file
        if (myInput) {
            while (getline(myInput, line)) {
                buff << line << '\n';
                ch = myInput.peek();

                // Count paragraphs
                if (lineCount == 0 && !line.empty()) {
                    paraCount++;
                }

                // Replace double line breaks with paragraph tags and count paragraphs
                if (ch != '\n' && prevch == '\n' && ch != EOF) {
                    paraCount++;
                }

                // Replace single line breaks with HTML line break tags
                if (ch == '\n' && prevch != '\n') {

                    buff << "<br>" << '\n' << "<br>";
                    prevch = ch;

                }

                // Add HTML line break tag if there is an empty line
                if (ch == '\n' && prevch == '\n' && line.empty()) {
                    buff << "<br>";
                    prevch = ch;
                }


                lineCount++;
                prevch = ch;
            }

        }
        else {
            cout << "Error: text filename \"" << infilename << "\" --> No such file or directory" << endl;
            return "bad file";

        }
        myInput.close();

        return buff.str();
    }

    // Run paragraph function that replaces double line breaks with paragraph tags and counts paragraphs
    string runPara(string infilename) {

        stringstream buff;
        char ch;
        char prevch = '0';
        string line;

        ifstream myInput;
        myInput.open(infilename);

        if (myInput) {
            while (getline(myInput, line)) {

                if (lineCount == 0 && !line.empty()) {
                    buff << "<p>" << '\n';
                    paraCount++;
                }


                buff << line << '\n';


                ch = myInput.peek();

                if (ch != '\n' && prevch == '\n' && ch != EOF) {
                    buff << "<p>" << '\n';
                    prevch = ch;
                    paraCount++;
                }

                if (ch == '\n' && prevch != '\n') {
                    buff << "</p>";
                    prevch = ch;
                }

                if (ch == '\n' && prevch == '\n' && line.empty()) {
                    buff << "<br>";
                    prevch = ch;
                }
                lineCount++;
                prevch = ch;
            }

        }

        else {
            cout << "Error: text filename \"" << infilename << "\" --> No such file or directory" << endl;
            return "bad file";

        }
        myInput.close();
        return buff.str();

    }
    
    // Searches for keywords in the input and adds styles to them based on the provided color codes.
    string runKeyword(stringstream& input) {

        string str, lineRead;
        stringstream myOutput;

        size_t sublen;
        while (getline(input, lineRead)) {
            stringstream searchbuff(lineRead);

            while (searchbuff >> str) {
                int wordlent = str.size();

                int ind = 0;

                int found = 0;

                for (string w : args) {

                    int lent = w.size();
                    sublen = str.find(w);
                    string str2, str1, str3;

                    if (sublen != string::npos) {

                        found = 1;
                        wordCount[ind] = wordCount[ind] + 1;

                        if (sublen > 0 && ((sublen + lent) < wordlent)) {

                            str1 = str.substr(0, sublen);
                            myOutput << str1;

                            str2 = str.substr(sublen, lent);
                            myOutput << "<key-" << colors[ind] << ">" << str2 << "</key-" << colors[ind] << ">";
                   
                            str3 = str.substr(sublen + lent, wordlent);
                            myOutput << str3 << " ";

                        }

                        else if (sublen == 0) {
                            str1 = str.substr(sublen, lent);
                            myOutput << "<key-" << colors[ind] << ">" << str1 << "</key-" << colors[ind] << ">";

                            str2 = str.substr(sublen + lent, wordlent);
                            myOutput << str2 << " ";
                        }

                        else {

                            str1 = str.substr(0, sublen);
                            myOutput << str1;
                            str2 = str.substr(sublen, lent);
                            myOutput << "<key-" << colors[ind] << ">" << str2 << "</key-" << colors[ind] << ">";
                        }


                    }

                    ind++;

                }

                if (found == 0) {

                    myOutput << str << " ";

                }

            }
            myOutput << '\n';

        }

        return myOutput.str();

    }
    
    //creates and saves a report file containing the details of the document processing, The report file is saved in the same directory as the input file.
    void runReport() {
        cout << "# lines input = " << lineCount << endl;
        cout << "# paragraphs output = " << paraCount << endl;
        int tags = 0;
        for (int i = 0; i < 5; i++) {
            tags += wordCount[i];
        }
        cout << "# tags = " << tags << endl;
        for (int i = 0; i < 5; i++) {
            if (wordCount[i] == 0) {
                continue;
            }
            cout << "\t # " << args[i] << "( " << colors[i] << ") = " << wordCount[i] << endl;
        }

    }

    //Displays a help message containing information about how to use the program, It also provides an overview of the program's functionality and examples of how to use it.
    void displayHelp() {
        cout << "markup [--help] [-rp] textfilename [htmlfilename] --keywords [Args]" << endl;
        cout << "\n\t --help \t\t display the help text for the program." << endl;
        cout << "\t -r \t\t\t report conversion metrics" << endl;
        cout << "\t -p \t\t\t use <p> tag for paragraph breaks" << endl;
        cout << "\n\t textFilename \t\t the name of the ASCII text file to process" << endl;
        cout << "\t htmlFilename \t\t the name of the HTML file receiving the output. \n \
            \t\t\t If not provided the text filename will be used \n \
            \t\t\t with its extension changed to \".html\"" << endl;

        cout << "\t--keywords \t\t the words to tag and colorize" << endl;

    }