// EndStatement.h
//
// CS 104 / Fall 2021
//
// The EndStatement class encapsulates an End statement in a BASIC program.
// A END statement looks like this:
//
//     END


#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class EndStatement: public Statement
{
private:

public:
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
