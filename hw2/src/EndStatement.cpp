// EndStatement.cpp:
#include "EndStatement.h"
#include <iostream>
using namespace std;


void EndStatement::execute(ProgramState * state, ostream &outf)
{
	// TODO
	state -> working = false;
}
