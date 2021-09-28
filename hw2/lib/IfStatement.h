#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
	std::string m_variableName;
	std::string m_operation;
	int m_compare;
	int m_lineNumber;


public:
	IfStatement(std::string variableName, std::string operation, int compare, int lineNumber);
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
