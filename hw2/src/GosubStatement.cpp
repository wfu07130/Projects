// GosubStatement.cpp:
#include "GosubStatement.h"
#include <iostream>
using namespace std;

GosubStatement::GosubStatement(int lineNumber, int returnLine):GotoStatement(lineNumber)
{
	m_lineNumber= lineNumber;
	m_returnLine= returnLine;
}


// The Goto version of execute() should:
//
//    * Jump to the designated line in the code
void GosubStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	vector<int> temp = state -> returns;
	state->skipLine = m_lineNumber;
	temp.push_back(m_returnLine);
	state->returns = temp;
}
