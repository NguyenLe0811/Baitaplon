#include <iostream>
#include <string>
#include <vector>
#include "Infix.h"

using namespace std;

int foundSpace(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			return i;
	}
	return -1;
}

void deleteSpace(string &str) 
{
	int index;

	while((index = foundSpace(str)) != -1)
		str.erase(index,1);
}

int foundOperator(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'sqrt' || str[i] == 'cos' || str[i] == 'sin' || str[i] == 'log' || str[i] == 'exp' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '!')
			return i;
	}
	return -1;
}

int foundNumber(string str)
{
	for (int i = 0; i < str.length();i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			return i;
	}
	return -1;
}
void detailOperator(string& Input)
{
	for (int i = 0; i < Input.length(); i++)
	{
		if (Input[i] == '-' && Input[i + 1] == '-')
		{
			Input.replace(i, 2, "+");
			detailOperator(Input);
		}

		if ((Input[i] == '+' && Input[i + 1] == '-') || (Input[i]) == '-' && Input[i + 1] == '+')
		{
			Input.replace(i, 2, "-");
			detailOperator(Input);
		}

		if ((Input[i] == '*' || Input[i] == '/') && (Input[i + 1] == '+'))
		{
			Input.erase(i + 1, 1);
			detailOperator(Input);
		}
	}
}
	
void parseInput(string Input, vector<string> &M) 
{
	int length = Input.length();
	int count = 0;

	for (int i = 0; i < length; i++)
	{
		if (Input[i] >= '0' && Input[i] <= '9')
		{
			if(i < length - 1)
			{
				int j = i + 1;
				if (Input[j] == '(' || Input[j] == ')' || Input[j] == '*' || Input[j] == '/' || Input[j] == '+' || Input[j] <= '-' || Input[j] == '%' || Input[j] == '^' || Input[j] == 't' || Input[j] == 'n' || Input[j]=='p' || Input[j] == 'cos' || Input[j] == 'g' || Input[j] == '!')
				{
					M.push_back(Input.substr(i-count, 1 + count));
					count = 0;
				}
				else
					count++;
			}	
			else
			{
				M.push_back(Input.substr(i - count, count+1));
				break;
			}
		}
		else 
		{
			if (Input[i] == '(' || Input[i] == ')' || Input[i] == '*' || Input[i] == '/' || Input[i] == '+' || Input[i] == '-' || Input[i] == '%' || Input[i] == '^' || Input[i] == 't' || Input[i] =='s' || Input[i] == 'p' || Input[i] == 'g' || Input[i] == '!' || Input[i] == 'n')
			{
				string temp(1, Input[i]);
				M.push_back(temp);
			}
		}
	}
}

void quickTransition(string &Input)
{
	int index[5];
	index[0] = Input.find("sqrt");
	if (index[0] != -1)
	{
		Input.erase(index[0], 4);
		int i = index[0];
		while (true)
		{
			if (Input[i] == ')')
			{
				Input.insert(i, "t"); //them ki tu vao sau vi tri i 
				break;
			}
			i++;
		}
	}

	index[1] = Input.find("sin");
	if (index[1] != -1)
	{
		Input.erase(index[1], 3);
		int i = index[1];
		while (true)
		{
			if (Input[i] == ')')
			{
				Input.insert(i, "n");
				break;
			}
			i++;
		}
	}

	index[2] = Input.find("cos");
	if (index[2] != -1)
	{
		Input.erase(index[2], 3);
		int i = index[2];
		while (true)
		{
			if (Input[i] == ')')
			{
				Input.insert(i, "s"); //them ki tu vao sau vi tri i 
				break;
			}
			i++;
		}
	}

	index[3] = Input.find("exp");
	if (index[3] != -1)
	{
		Input.erase(index[3], 3);
		int i = index[3];
		while (true)
		{
			if (Input[i] == ')')
			{
				Input.insert(i, "p"); //them ki tu vao sau vi tri i 
				break;
			}
			i++;
		}
	}

	index[4] = Input.find("log");
	if (index[4] != -1)
	{
		Input.erase(index[4], 3);
		int i = index[4];
		while (true)
		{
			if (Input[i] == ')')
			{
				Input.insert(i, "g"); //them ki tu vao sau vi tri i 
				break;
			}
			i++;
		}
	}
}

bool Step1(string& Input)
{
	deleteSpace(Input);
	if (foundNumber(Input) == -1 && foundOperator(Input) == -1)
	{
		return false;
	}
	detailOperator(Input);
	return true;
}

void Step2(string& Input, float &Result)
{
	Infix* infix = new Infix();
	vector<string> M;
	quickTransition(Input);
	parseInput(Input, M);
	Result = infix->calculateValue(M);
}

void Process(string &Input)
{
	if (Step1(Input) == true)
	{
		float Result = 0;
		Step2(Input, Result);
		cout << "Result: " << Result << endl;
	}
	else
		cout << "Result: Error" << endl;
}

void main()
{
	string Input;
	cout << "\nEnter: ";
	getline(cin, Input);

	Process(Input);
	
	system("pause");
}