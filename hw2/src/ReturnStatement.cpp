// ReturnStatement.cpp:
#include "ReturnStatement.h"
using namespace std;

// The Goto version of execute() should:
//
//    * Jump to the designated line in the code
void ReturnStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	state->needReturn = true;
}
