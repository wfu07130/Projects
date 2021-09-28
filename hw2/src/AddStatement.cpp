// AddStatement.cpp:
#include "AddStatement.h"
using namespace std;

AddStatement::AddStatement(std::string variableName, int value):LetStatement(variableName,value){
	m_variableName = variableName;
 	m_value =  value;
	useValue = true;
}

AddStatement::AddStatement(std::string variableName, std::string variableName2):LetStatement(variableName,variableName2){
	m_variableName = variableName;
 	m_variableName2 =  variableName2;
	useValue = false;
} 


void AddStatement::execute(ProgramState * state, ostream &outf)
{
	if(useValue)
	{
		state -> lineList[m_variableName]+= m_value;
	}
	else
	{
		state -> lineList[m_variableName]+= state -> lineList[m_variableName2];
	}
}
