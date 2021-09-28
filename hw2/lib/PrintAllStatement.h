#ifndef PRINT_ALL_STATEMENT_INCLUDED
#define PRINT_ALL_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>
#include <map>

class PrintAllStatement: public Statement
{
private:
	
public:
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
