#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "GotoStatement.h"
#include "ProgramState.h"

class GosubStatement: public GotoStatement
{
private:
	int m_lineNumber;
	int m_returnLine;
public:
	GosubStatement(int lineNumber, int returnLine);
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
