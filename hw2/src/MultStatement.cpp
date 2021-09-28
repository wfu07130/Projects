// MultStatement.cpp:
#include "MultStatement.h"
using namespace std;

MultStatement::MultStatement(std::string variableName, int value):LetStatement(variableName,value){
	m_variableName = variableName;
 	m_value =  value;
	useValue = true;
}

MultStatement::MultStatement(std::string variableName, std::string variableName2):LetStatement(variableName,variableName2){
	m_variableName = variableName;
 	m_variableName2 =  variableName2;
	useValue = false;
} 


void MultStatement::execute(ProgramState * state, ostream &outf)
{
	if(useValue)
	{
		state -> lineList[m_variableName]*= m_value;
	}
	else
	{
		state -> lineList[m_variableName]*= state -> lineList[m_variableName2];
	}
}
