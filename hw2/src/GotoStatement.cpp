// GotoStatement.cpp:
#include "GotoStatement.h"
using namespace std;

GotoStatement::GotoStatement(int lineNumber)
	: m_lineNumber(lineNumber)
{}


// The Goto version of execute() should:
//
//    * Jump to the designated line in the code
void GotoStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	state -> skipLine = m_lineNumber;
}
