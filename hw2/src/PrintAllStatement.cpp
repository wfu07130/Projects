// PrintAllStatement.cpp:
#include "PrintAllStatement.h"

void PrintAllStatement::execute(ProgramState * state, std::ostream &outf)
{
	std::map<std::string, int>::iterator it;
	for (it = state -> lineList.begin(); it != state-> lineList.end(); ++it)
	{
		outf << it -> first << " " << it -> second << std::endl;
	}
}