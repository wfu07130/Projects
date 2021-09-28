#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "LetStatement.h"
#include "ProgramState.h"

class DivStatement: public LetStatement
{
private:
	std::string m_variableName;
	std::string m_variableName2;
	bool useValue;
	int m_value;


public:
	DivStatement(std::string variableName, int value);
	DivStatement(std::string variableName, std::string variableName2);
	
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
