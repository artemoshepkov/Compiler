#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <stack>
#include <cctype>
#include <algorithm>

using namespace std;

#define POS_INDEX_LINE 0
#define POS_COMMAND_LINE 1
#define POS_VARIABLE_LINE 2
#define POS_COMPARE_SIGN_LINE 3
#define POS_FIRST_IF_EXAMPLE_LINE 2
#define POS_SECOND_IF_EXAMPLE_LINE 4
#define TEMP_VARIABLE "TEMP"
#define POS_OPERAND_IF 6

int countLineAssembler = 0;

int numPrevLine = -1;

vector <string> output;

vector <string> lineProgram;

map <string, string> variables;

map <string, string> indexesFromBasicToAssembler;

map <string, string> operations
{
	{"+", "ADD"},
	{"-", "SUB"},
	{"*", "MUL"},
	{"/", "DIVIDE"},
};

map <string, string> basicCommands
{
	{"REM", ""},
	{"INPUT", "READ"},
	{"PRINT", "WRITE"},
	{"GOTO", "JUMP"},
	{"IF", ""},
	{"LET", ""},
	{"END", "HALT"}
};

void printVector(vector <string> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;

		if ((i + 1) % 3 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}

void printMap(map <string, string> m)
{
	for (auto& item : m)
	{
		cout << item.first << " - " << item.second << endl;
	}
}

int loadCodeFromFileToVector(vector<string> &v, string path)
{
	ifstream basicFile(path); 	// ifstream basicfile(argv[1]);
	if (!basicFile.is_open())
	{
		return -1;
	}
	else
	{
		string str;
		while (!basicFile.eof())
		{
			str = "";
			getline(basicFile, str);
			v.push_back(str);
		}
	}
	basicFile.close();

	return 0;
}

void getElemsFromLine(string line, vector <string>& v)
{
	string temp;
	for (int i = 0; i < line.size() + 1; i++)
	{
		if (i == line.size() || line[i] == ' ')
		{
			v.push_back(temp);
			temp = "";
		}
		else
		{
			temp += line[i];
		}
	}
}

int verifyLine(vector <string> line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (i == 2 || line[1] == "REM")
		{
			break;
		}
		for (int j = 0; j < line[i].size(); j++)
		{
			if (isalpha(line[i][j]))
			{
				if (!isupper(line[i][j]))
				{
					cout << "Invalid uppercase. ";
					return -1;
				}
			}
		}
	}

	if (basicCommands.count(line[POS_COMMAND_LINE]) < 1) // verify command
	{
		return -1;
	}

	int num = stoi(line[POS_INDEX_LINE]);
	if (num <= numPrevLine) // verify numbers of lines
	{
		cout << "Invalid numbers of lines. ";
		return -1;
	}
	numPrevLine = stoi(line[POS_INDEX_LINE]);

	return 0;
}

string getIndexLineToAssembler()
{
	string indexLineAssembler;

	if (countLineAssembler < 10)
	{
		indexLineAssembler = "0" + to_string(countLineAssembler);
	}
	else
	{
		indexLineAssembler = to_string(countLineAssembler);
	}
	countLineAssembler++;

	return indexLineAssembler;
}

void addIndexFromBasicToAssembler(string basicIndexLine)
{
	string indexLineAssembler = getIndexLineToAssembler();

	indexesFromBasicToAssembler.emplace(basicIndexLine, indexLineAssembler);
}

void addVariableFromBasicToAssembler(string basicVariable)
{
	if (variables.count(basicVariable) > 0)
		return;

	int sizeArrayMemory = 99;

	int indexVariableAssembler = sizeArrayMemory - variables.size();

	variables.emplace(basicVariable, to_string(indexVariableAssembler));
}

string getExample(vector <string> line)
{
	string example;

	for (int i = POS_VARIABLE_LINE + 2; i < line.size(); i++)
	{
		example += line[i];
	}

	return example;
}

void convenientForm(string& row)
{
	string temp = row;
	string rowResult = "";
	string historyTemp;
	int count = 0;
	while (temp != "")
	{
		if (temp.substr(0, 1) == " " || isalpha(temp[0]) || isdigit(temp[0]))
		{
			rowResult += temp.substr(0, 1);
			historyTemp = temp.substr(0, 1);
			temp.erase(0, 1);
		}
		else
		{
			if (historyTemp != " ") rowResult += " ";
			rowResult += temp.substr(0, 1);
			temp.erase(0, 1);
		}
	}
	temp = rowResult;
	rowResult = "";

	count = 0;

	while (temp != "")
	{
		if (temp.substr(0, 1) != " ")
		{
			rowResult += temp.substr(0, 1);
			temp.erase(0, 1);
		}
		else
		{
			while (temp.substr(0, 1) == " ")
			{
				temp.erase(0, 1);
			}
			rowResult += " ";
		}
	}
	row = rowResult;
}
int calculateCountChar(string row, char element)
{
	int count = 0;
	while (true)
	{
		int findBracket = row.find(element);
		if (findBracket == -1)
			break;
		else
			row.erase(findBracket, 1);
		count++;
	}
	return count;
}
vector <string> translateToReversePolishNotation(string str)
{
	string str_rpn;
	string::size_type ind;
	while (str.find(" ") != -1)
	{
		str.erase(str.find(" "), 1);
	}

	for (int i = 0; i < str.size(); ++i)
	{
		if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
		{
			auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c); });
			str.insert(it, ')');
			str.insert(i, "(0");
			int nnn = 0;
		}
	}

	map<char, size_t> priority;
	priority.insert(std::make_pair('*', 3));
	priority.insert(std::make_pair('/', 3));
	priority.insert(std::make_pair('+', 2));
	priority.insert(std::make_pair('-', 2));
	priority.insert(std::make_pair('(', 1));
	stack<char> stack;
	for (auto str_element : str)
	{
		if (!isalnum(str_element) && ('.' != str_element))
		{
			str_rpn += ' ';
			if (')' == str_element)
			{
				while (stack.top() != '(')
				{
					str_rpn += stack.top();
					stack.pop();
					str_rpn += ' ';
				}
				stack.pop();
			}
			else if ('(' == str_element)
			{
				stack.push(str_element);
			}
			else if (stack.empty() || (priority[stack.top()] < priority[str_element]))
			{
				stack.push(str_element);
			}
			else
			{
				do
				{
					str_rpn += stack.top();
					str_rpn += ' ';
					stack.pop();
				} while (!(stack.empty() || (priority[stack.top()] < priority[str_element])));
				stack.push(str_element);
			}
		}
		else
		{
			str_rpn += str_element;
		}
	}
	while (!stack.empty())
	{
		str_rpn += stack.top();
		str_rpn += ' ';
		stack.pop();
	}

	convenientForm(str_rpn);

	vector <string> strRpnVector;

	int j = 1;
	for (int i = 0; i < str_rpn.size(); i++)
	{
		if (isdigit(str_rpn[i]))
		{
			string elementStrRpn = "";
			j = i;
			while (isdigit(str_rpn[j]))
			{
				elementStrRpn += str_rpn.substr(j, 1);
				str_rpn.erase(j, 1);
			}
			strRpnVector.push_back(elementStrRpn);
		}
		else if (str_rpn.substr(i, 1) != " ")
		{
			strRpnVector.push_back(str_rpn.substr(i, 1));
			str_rpn.erase(i, 1);
		}
	}
	return strRpnVector;
}

void initVariableIntoAssembler(string variable)
{
	string indexLine = getIndexLineToAssembler();
	output.push_back(indexLine);

	variables.emplace(variable, indexLine);

	output.push_back("=");

	string value = "+";
	for (int i = 0; i < 4 - variable.size(); i++)
	{
		value += '0';
	}
	value += variable;

	output.push_back(value);
}

void handleDigitExample(vector <string> example)
{
	for (int i = 0; i < example.size(); i++)
	{
		if (isdigit(example[i][0]))
		{
			initVariableIntoAssembler(example[i]);
		}
	}
}

int findCharSign(vector <string> example)
{
	if (example.size() < 2)
		return 1;

	int index = 0;
	
	while (isalpha(example[index][0]) || isdigit(example[index][0]))
	{
		index++;
	}

	return index;
}

void addCommandToAssembler(string command, string operand)
{
	string indexLine = getIndexLineToAssembler();

	output.push_back(indexLine);
	output.push_back(command);
	output.push_back(operand);
}

void addOperationCommandToAssembler(int index, string command, vector <string> &example)
{
	string operand = variables[example[index]];
	addCommandToAssembler(command, operand);

	example.erase(example.begin() + index);
}

void addExampleCommandsToAccumToAssembler(vector <string> example)
{
	int index = findCharSign(example);

	if (index < 2)
	{
		addOperationCommandToAssembler(index - 1, "LOAD", example);
	}
	else
	{
		addOperationCommandToAssembler(index - 2, "LOAD", example);

		while (!example.empty())
		{
			index = findCharSign(example);

			string sign = example[index];

			example.erase(example.begin() + index);

			addOperationCommandToAssembler(index - 1, operations[sign], example);
		}
	}
}

void addExampleCommandsToVarToAssembler(string variable, vector <string> example)
{
	addExampleCommandsToAccumToAssembler(example);

	addCommandToAssembler("STORE", variable);
}
string getIndexLineToAssembler(bool b)
{
	string indexLineAssembler;

	if (countLineAssembler < 10)
	{
		indexLineAssembler = "0" + to_string(countLineAssembler);
	}
	else
	{
		indexLineAssembler = to_string(countLineAssembler);
	}

	return indexLineAssembler;
}
void addCompringCommandsToAssembler(int indexFirstExample, int indexSecondExample)
{
	vector <string> example;


	example = translateToReversePolishNotation(lineProgram[indexFirstExample]);

	handleDigitExample(example);

	string variableAssembler = variables[TEMP_VARIABLE];

	addExampleCommandsToVarToAssembler(variableAssembler, example);


	example = translateToReversePolishNotation(lineProgram[indexSecondExample]);

	handleDigitExample(example);

	addExampleCommandsToAccumToAssembler(example);


	addCommandToAssembler("SUB", variableAssembler);
}

void handleLineIfCommand()
{
	vector <string> comparingSigns = { "<", ">", "<=", ">=", "==" };

	string temp = "";
	int index;
	
	index = POS_COMMAND_LINE + 1;
	while (find(comparingSigns.begin(), comparingSigns.end(), lineProgram[index]) == comparingSigns.end())
	{
		temp += lineProgram[index];

		lineProgram.erase(lineProgram.begin() + index);

	}
	lineProgram.insert(lineProgram.begin() + index, temp);
	temp = "";

	index = POS_COMMAND_LINE + 3;
	while (lineProgram[index] != "GOTO")
	{
		temp += lineProgram[index];

		lineProgram.erase(lineProgram.begin() + index);

	}
	lineProgram.insert(lineProgram.begin() + index, temp);
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		return -1;
	}


	vector <string> programCode;

	if (loadCodeFromFileToVector(programCode, argv[1]) == -1)
	{
		cout << "Input file is not open" << endl;
		return -1;
	}
	cout << "Input file is open" << endl;


	for (int indexLine = 0; indexLine < programCode.size(); indexLine++)
	{
		getElemsFromLine(programCode[indexLine], lineProgram);

		if (verifyLine(lineProgram) == -1)
		{
			cout << "Invalid syntax" << endl;
			return -1;
		}


		if (basicCommands[lineProgram[POS_COMMAND_LINE]] != "")
		{
			addIndexFromBasicToAssembler(lineProgram[POS_INDEX_LINE]);

			string indexAssembler = indexesFromBasicToAssembler[lineProgram[POS_INDEX_LINE]];
			output.push_back(indexAssembler); // Add index line

			string commandAssembler = basicCommands[lineProgram[POS_COMMAND_LINE]];
			output.push_back(commandAssembler); // Add translate word from basic to assembler		
		}

		if (lineProgram[POS_COMMAND_LINE] == "INPUT")
		{
			addVariableFromBasicToAssembler(lineProgram[POS_VARIABLE_LINE]);

			string variableAssembler = variables[lineProgram[POS_VARIABLE_LINE]];

			output.push_back(variableAssembler);
		}
		else if (lineProgram[POS_COMMAND_LINE] == "PRINT")
		{
			string variable = variables[lineProgram[POS_VARIABLE_LINE]];

			output.push_back(variable);
		}
		else if (lineProgram[POS_COMMAND_LINE] == "END")
		{
			output.push_back("00");
		}
		else if (lineProgram[POS_COMMAND_LINE] == "LET")
		{
			addIndexFromBasicToAssembler(lineProgram[POS_INDEX_LINE]);

			output.push_back(indexesFromBasicToAssembler[lineProgram[POS_INDEX_LINE]]);
			output.push_back("JUMP");
			output.push_back(getIndexLineToAssembler(true));

			addVariableFromBasicToAssembler(lineProgram[POS_VARIABLE_LINE]);
			string variableAssembler = variables[lineProgram[POS_VARIABLE_LINE]]; // Add var to map variables

			vector <string> example = translateToReversePolishNotation(getExample(lineProgram));

			handleDigitExample(example);

			addExampleCommandsToVarToAssembler(variableAssembler, example);
		}
		else if (lineProgram[POS_COMMAND_LINE] == "IF")
		{
			handleLineIfCommand();


			addVariableFromBasicToAssembler(TEMP_VARIABLE);

			if (lineProgram[POS_COMPARE_SIGN_LINE] == "<")
			{			
				addCompringCommandsToAssembler(POS_SECOND_IF_EXAMPLE_LINE, POS_FIRST_IF_EXAMPLE_LINE);

				addCommandToAssembler("JNEG", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);
			}
			else if (lineProgram[POS_COMPARE_SIGN_LINE] == ">")
			{
				addCompringCommandsToAssembler(POS_FIRST_IF_EXAMPLE_LINE, POS_SECOND_IF_EXAMPLE_LINE);

				addCommandToAssembler("JNEG", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);
			}
			else if (lineProgram[POS_COMPARE_SIGN_LINE] == "==")
			{
				addCompringCommandsToAssembler(POS_FIRST_IF_EXAMPLE_LINE, POS_SECOND_IF_EXAMPLE_LINE);

				addCommandToAssembler("JZ", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);
			}
			else if (lineProgram[POS_COMPARE_SIGN_LINE] == "<=")
			{
				addCompringCommandsToAssembler(POS_SECOND_IF_EXAMPLE_LINE, POS_FIRST_IF_EXAMPLE_LINE);

				addCommandToAssembler("JNEG", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);

				addCommandToAssembler("JZ", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);

			}
			else if (lineProgram[POS_COMPARE_SIGN_LINE] == ">=")
			{
				addCompringCommandsToAssembler(POS_FIRST_IF_EXAMPLE_LINE, POS_SECOND_IF_EXAMPLE_LINE);

				addCommandToAssembler("JNEG", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);

				addCommandToAssembler("JZ", indexesFromBasicToAssembler[lineProgram[POS_OPERAND_IF]]);
			}
		}

		lineProgram.clear();
	}

	ofstream assemblerFile(argv[2]);
	if (!assemblerFile.is_open())
	{
		cout << "Output file is not open" << endl;
		return -1;
	}

	for (int i = 0; i < output.size(); i++)
	{
		assemblerFile << output[i] << " ";

		if ((i + 1) % 3 == 0)
			assemblerFile << endl;
	}


	assemblerFile.close();

	return 0;
}
