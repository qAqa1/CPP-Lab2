#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

vector<string> month[31];
int month_lengths[12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };
int month_now = 0;

void ADD(int day_index, string input)
{
	vector<string>::iterator find_str;
	find_str = find(month[day_index].begin(), month[day_index].end(), input);

	if (find_str != month[day_index].end()) 
	{		
		cout << "���� \""<< input <<"\" ��������������� �� "<< day_index << " ����� ��� ����������";
	}
	else 
	{
		month[day_index].push_back(input);
		cout << "���� \"" << input << "\" ��������������� �� " << day_index << " ����� ���������";
	}
}

void REMOVE(int day_index, string input)
{
	vector<string>::iterator find_str;
	find_str = find(month[day_index].begin(), month[day_index].end(), input);

	if (find_str != month[day_index].end())
	{		
		month[day_index].erase(find_str);
		cout << "���� \"" << input << "\" ��������������� �� " << day_index << " ����� �������";
	}
	else
	{
		cout << "�� "<< day_index <<" ����� �� ������������� ���� \""<<input<<"\"";
	}
}

void NEXT()
{
	int month_previous_lenght = month_lengths[month_now];

	if (month_now == 11)
	{
		month_now = 0;
	}
	else
	{
		month_now++;
	}

	if (month_lengths[month_now] < month_previous_lenght)
	{
		for (int x = month_lengths[month_now] + 1; x <= month_previous_lenght; x++)
		{
			for (string deal : month[x])
			{
				month[month_lengths[month_now]].push_back(deal);
			}
			month[x].clear();
		}
	}

	switch (month_now)
	{
	case 0:
		cout << "������ ������, ����� ����: " << month_lengths[month_now];
		break;
	case 1:
		cout << "������ �������, ����� ����: " << month_lengths[month_now];
		break;
	case 2:
		cout << "������ ����, ����� ����: " << month_lengths[month_now];
		break;
	case 3:
		cout << "������ ������, ����� ����: " << month_lengths[month_now];
		break;
	case 4:
		cout << "������ ���, ����� ����: " << month_lengths[month_now];
		break;
	case 5:
		cout << "������ ����, ����� ����: " << month_lengths[month_now];
		break;
	case 6:
		cout << "������ ����, ����� ����: " << month_lengths[month_now];
		break;
	case 7:
		cout << "������ ������, ����� ����: " << month_lengths[month_now];
		break;
	case 8:
		cout << "������ ��������, ����� ����: " << month_lengths[month_now];
		break;
	case 9:
		cout << "������ �������, ����� ����: " << month_lengths[month_now];
		break;
	case 10:
		cout << "������ ������, ����� ����: " << month_lengths[month_now];
		break;
	case 11:
		cout << "������ �������, ����� ����: " << month_lengths[month_now];
		break;
	}
}

void DUMP(int day_index)
{
	if (!month[day_index].empty())
	{
		cout << "���� �� " << day_index << " �����:";
		for (string &deal : month[day_index])
		{
			cout <<  " " << deal;
		}
	}
	else
	{
		cout << "�� " << day_index<< " ����� ������ �� ��������������";
	}
}

int find_space_second_index(string input)
{
	bool first_index = false;
	for (int x = 0; x < input.length(); x++)
	{
		if (input[x] == 32)
		{
			if (first_index == false)
			{
				first_index = true;
			}
			else
			{
				return(x);
			}
		}
	}

	return (-1);	
}

void Command_Color()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
}

void Standart_Color()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
}

void HELP()
{
	cout << "�������:";
	Command_Color();
	cout << endl << "HELP";
	Standart_Color();
	cout << " ��� ��������� ������ ���� ������";
	Command_Color();
	cout << endl << "ADD_�����_����";
	Standart_Color();
	cout << " ��� ���������� ������ ����";
	Command_Color();
	cout << endl << "REMOVE_�����_����";
	Standart_Color();
	cout << " ��� �������� ����";
	Command_Color();
	cout << endl << "NEXT";
	Standart_Color();
	cout << " ��� �������� � ���������� ������";
	Command_Color();
	cout << endl << "DUMP_�����";
	Standart_Color();
	cout << " ��� ��������� ���� ��� � ��������� ����";
	Command_Color();
	cout << endl << "EXIT";
	Standart_Color();
	cout << " ��� �������� ���������";
}

void Execute_Command(string input)
{
	if (strstr(input.c_str(), "  "))
	{
		cout << "���� �� ���������";
		return;
	}

	if (input == "HELP")
	{
		HELP();
		return;
	}

	if (input == "NEXT")
	{
		NEXT();
		return;
	}

	if (input == "EXIT")
	{
		exit(1);
	}

	if (input.substr(0, 5) == "DUMP ")
	{
		int command_len = 5;
		int day_index = atoi((input.substr(command_len, input.length() - command_len)).c_str());
		if (day_index < 1 || day_index > month_lengths[month_now])
		{
			cout << "�������� ����� ������� ���� �� 1 �� " << month_lengths[month_now] << "!";
			return;
		}
		else
		{
			DUMP(day_index);
		}
		return;
	}

	if (input.substr(0, 4) == "ADD ")
	{
		int command_len = 4;
		int second_space_index = find_space_second_index(input);
		if (second_space_index == -1)
		{
			cout << "���� �� ���������";
			return;
		}
		else
		{
			int day_index = atoi((input.substr(command_len, input.length() - command_len - second_space_index)).c_str());
			if (day_index < 1 || day_index > month_lengths[month_now])
			{
				cout << "�������� ����� ������� ���� �� 1 �� " << month_lengths[month_now] << "!";
				return;
			}
			else
			{
				string deal = input.substr(second_space_index + 1, input.length() - second_space_index);
				if (deal == "")
				{
					cout << "���� �� ���������!";
					return;
				}
				ADD(day_index, deal);
			}
			return;
		}
	}

	if (input.substr(0, 7) == "REMOVE ")
	{
		int command_len = 7;
		int second_space_index = find_space_second_index(input);
		if (second_space_index == -1)
		{
			cout << "���� �� ���������";
			return;
		}
		else
		{
			int day_index = atoi((input.substr(command_len, input.length() - command_len - second_space_index)).c_str());
			if (day_index < 1 || day_index > month_lengths[month_now])
			{
				cout << "�������� ����� ������� ���� �� 1 �� " << month_lengths[month_now] << "!";
				return;
			}
			else
			{
				string deal = input.substr(second_space_index + 1, input.length() - second_space_index);
				if (deal == "")
				{
					cout << "���� �� ���������!";
					return;
				}
				REMOVE(day_index, deal);
			}
			return;
		}
	}
	cout << "�������� ���� ������� �� ����������!";
}

void main()
{
	//setlocale(LC_ALL, "russian");
	SetConsoleCP(1251); //��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); //��������� ������� �������� win-cp 1251 � ����� 
	while (true)
	{
		cout << endl << endl << "(������� ";
		Command_Color();
		cout << "HELP";
		Standart_Color();
		cout << " ��� ��������� ������ ���� ������ ��� ";
		Command_Color();
		cout << "EXIT";
		Standart_Color();
		cout << " ��� �������� ���������)";
		cout << endl << "������� �������: ";
		Command_Color();
		string input;
		getline(cin, input);
		Standart_Color();
		cout << endl;
		Execute_Command(input);
	}
}