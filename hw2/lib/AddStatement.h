#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "LetStatement.h"
#include "ProgramState.h"

class AddStatement: public LetStatement
{
private:
	std::string m_variableName;
	std::string m_variableName2;
	bool useValue;
	int m_value;


public:
	AddStatement(std::string variableName, int value);
	AddStatement(std::string variableName, std::string variableName2);
	
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
