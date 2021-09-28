#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class GotoStatement: public Statement
{
private:
	int m_lineNumber;
public:
	GotoStatement(int lineNumber);
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
