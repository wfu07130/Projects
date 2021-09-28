// DivStatement.cpp:
#include "DivStatement.h"
#include <iostream>
using namespace std;

DivStatement::DivStatement(std::string variableName, int value):LetStatement(variableName,value){
	m_variableName = variableName;
 	m_value =  value;
	useValue = true;
}

DivStatement::DivStatement(std::string variableName, std::string variableName2):LetStatement(variableName,variableName2){
	m_variableName = variableName;
 	m_variableName2 =  variableName2;
	useValue = false;
} 


void DivStatement::execute(ProgramState * state, ostream &outf)
{
	if(useValue)
	{
		if (m_value != 0)
		{
			state -> lineList[m_variableName] /= m_value;
		}
		else
		{
			outf << "Divide by zero exception" << endl;
			state -> working = false;
		}
	}
	else
	{
		if (state -> lineList[m_variableName2] != 0)
		{
			state -> lineList[m_variableName] /= state -> lineList[m_variableName2];
		}
		else
		{
			outf << "Divide by zero exception" << endl;
			state -> working = false;
		}
	}
}
