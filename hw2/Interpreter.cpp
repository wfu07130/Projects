// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "EndStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "GotoStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "IfStatement.h"
#include "GosubStatement.h"
#include "ReturnStatement.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <iostream>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main(int argc, char *argv[])
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
		//change output stream
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	string line;
	int x;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
		x++;
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	string var;
	string var2;
	int lineNumber;
	int val;

	ss << line;
	ss >> lineNumber;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
	else if ( type == "END" || type == ".")
	{
		statement = new EndStatement();
	}
	else if ( type == "PRINT")
	{
		ss >> var;
		statement = new PrintStatement(var);
	}		
	else if ( type == "PRINTALL")
	{
		statement = new PrintAllStatement();
	}
	else if ( type == "GOTO")
	{
		ss >> val;
		statement = new GotoStatement(val);
	}
	else if ( type == "ADD" )
	{
		ss >> var;
		stringstream ss2; 
		string temp = ss.str();
		int waste1;
		string waste2;
		string waste3;
		ss2 << temp;
		ss2 >> waste1;
		ss2 >> waste2;
		ss2 >> waste3;
		if (ss >> val)
		{
			statement = new AddStatement(var, val);
		}
		else
		{
			ss2 >> var2;
			statement = new AddStatement(var, var2);
		}
	}
	else if ( type == "SUB")
	{
		ss >> var;
		stringstream ss2; 
		string temp = ss.str();
		int waste1;
		string waste2;
		string waste3;
		ss2 << temp;
		ss2 >> waste1;
		ss2 >> waste2;
		ss2 >> waste3;
		if (ss >> val)
		{
			statement = new SubStatement(var, val);
		}
		else
		{
			ss2 >> var2;
			statement = new SubStatement(var, var2);
		}
	}
	else if ( type == "MULT")
	{
		ss >> var;
		stringstream ss2; 
		string temp = ss.str();
		int waste1;
		string waste2;
		string waste3;
		ss2 << temp;
		ss2 >> waste1;
		ss2 >> waste2;
		ss2 >> waste3;
		if (ss >> val)
		{
			statement = new MultStatement(var, val);
		}
		else
		{
			ss2 >> var2;
			statement = new MultStatement(var, var2);
		}
	}
	else if ( type == "DIV")
	{
		ss >> var;
		stringstream ss2; 
		string temp = ss.str();
		int waste1;
		string waste2;
		string waste3;
		ss2 << temp;
		ss2 >> waste1;
		ss2 >> waste2;
		ss2 >> waste3;
		if (ss >> val)
		{
			statement = new DivStatement(var, val);
		}
		else
		{
			ss2 >> var2;
			statement = new DivStatement(var, var2);
		}
	}
	else if ( type == "IF" )
	{
		string waste1;
		ss >> var;
		ss >> var2;
		ss >> val;
		ss >> waste1;
		ss >> lineNumber;
		statement = new IfStatement(var,var2,val,lineNumber);
	}
	else if ( type == "GOSUB" )
	{
		ss >> val;
		statement = new GosubStatement(val,lineNumber);
	}
	else if ( type == "RETURN" )
	{
		ss >> val;
		statement = new ReturnStatement();
	}
	return statement;
}


void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );

	ProgramState* progState = new ProgramState((int)(program.size()));
	progState -> skipLine = -9999;
	for(unsigned int i =1; i < program.size();i++)
	{
		// check if interpreter is still running through code, END terminates working
		if(progState -> working)
		{
			program[i] -> execute(progState, outf);
			// check if there is a GOTO, a true IF, or RETURN command
			// and check to make sure GOTO is within range
			if(progState -> skipLine < (int)program.size() && progState -> skipLine >= 0)
			{
				i = progState -> skipLine - 1;
				progState -> skipLine = -9999;
			}
			// if GOTO command is jumping out of bounds
			else if (progState -> skipLine == -9999)
			{
			}
			else
			{
				outf << "Illegal jump instruction" << endl;
				break;
			}
			if(progState -> needReturn)
			{
				vector<int> temp = progState -> returns;
				i = temp.back();
				temp.pop_back();
				progState -> returns = temp;
				progState -> needReturn = false;
			}
		}
	}
}
