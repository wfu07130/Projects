// LetStatement.cpp:
#include "LetStatement.h"
using namespace std;

LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{}
LetStatement::LetStatement(std::string variableName, std::string variableName2)
	: m_variableName( variableName ), m_variableName2( variableName2 )
{}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	if (state -> lineList.find(m_variableName) == state -> lineList.end())
	{
		state -> lineList.insert(std::pair<string,int>(m_variableName,m_value));
	}
	else
	{
		state -> lineList[m_variableName] = m_value;
	}
}
