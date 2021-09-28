// IfStatement.cpp:
#include "IfStatement.h"
#include <iostream>
using namespace std;

IfStatement::IfStatement(std::string variableName, std::string operation, int compare, int lineNumber)
	: m_variableName(variableName) , m_operation(operation), m_compare(compare), m_lineNumber(lineNumber)
{}


// The Goto version of execute() should:
//
//    * Compare value in variable to int and if true skip to lineNumber
void IfStatement::execute(ProgramState * state, ostream &outf)
{
	int x = state -> lineList[m_variableName];
	if (m_operation == "<")
	{
		if (x < m_compare)
		{
			state -> skipLine = m_lineNumber;
		}
	}
	else if (m_operation == ">")
	{
		if (x > m_compare)
		{
			state -> skipLine = m_lineNumber;
		}
	}
	else if (m_operation == "<=")
	{
		if (x <= m_compare)
		{
			state -> skipLine = m_lineNumber;
		}
	}
	else if (m_operation == ">=")
	{
		if (x >= m_compare)
		{
			state -> skipLine = m_lineNumber;
		}
	}
	else if (m_operation == "=")
	{
		if (x == m_compare)
		{
			state -> skipLine = m_lineNumber;
		}
	}
	else if (m_operation == "<>")
	{
		if (x != m_compare)
		{
			state -> skipLine = m_lineNumber;
		}
	}
}
