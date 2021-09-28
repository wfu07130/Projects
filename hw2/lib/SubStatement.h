#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "LetStatement.h"
#include "ProgramState.h"

class SubStatement: public LetStatement
{
private:
	std::string m_variableName;
	std::string m_variableName2;
	bool useValue;
	int m_value;


public:
	SubStatement(std::string variableName, int value);
	SubStatement(std::string variableName, std::string variableName2);
	
	void execute(ProgramState * state, std::ostream &outf);
};

#endif
