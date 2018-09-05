#include <iostream>
#include "TFormula.h"
#include <conio.h>
#include <string>
#define MAXSIZE 100
using namespace std;
void main()
{
	char stroka[MAX];
	int bracket[MAXSIZE];
	int size = 0;
	TELEM result;
	cin >> stroka;
	TFormula A(stroka); 
	int count;
	count = A.FormulaChecker(bracket, size);
	for (int j = 0; j < size - 1; j += 2)
		cout << bracket[j] << " " << bracket[j + 1] << endl;
	cout <<"Errors: " << count << endl;
	cout << A.FormulaConverter() << endl;
	result = A.FormulaCalculator();
	cout << result << endl;
	_getch();
}