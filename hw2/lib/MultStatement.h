#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "LetStatement.h"
#include "ProgramState.h"

class MultStatement: public LetStatement
{
private:
	std::string m_variableName;
	std::string m_variableName2;
	bool useValue;
	int m_value;


public:
	MultStatement(std::string variableName, int value);
	MultStatement(std::string variableName, std::string variableName2);
	
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
