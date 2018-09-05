#include <iostream>
#include"E:\\Visual Studio 2013\\Projects\\Stack\\Stack\\TStack.h"
const int MAX = 100;// максимальный размер входной строки 
class Exception{
protected:
	int num;
public:
	virtual void display() = 0; 
};
class TFormula { 
	class ExceptionParenthesis :public Exception
	{
	public:
		ExceptionParenthesis(int num)
		{
			this->num = num;
		}
		void display()
		{
			cout << "Convert and calculate is impossible" << endl;
		}
	};
	class ExceptionOperands :public Exception
	{
	public:
		ExceptionOperands(int tmp)
		{
			this->num = tmp;
		}
		void display()
		{
			cout << "ERROR___Insufficient operands to execute" << endl;
		}
	};	class ExceptionZero :public Exception
	{
	public:
		ExceptionZero(int temp)
		{
			this->num = temp;
		}
		void display()
		{
			cout << "ERROR___division by ZERO" << endl;
		}
	};
private: 
	char Formula[MAX]; // входная строка 
	char Postfix_Form[MAX]; // постфиксная запись 
public: 
	TFormula(char Form[]);
int FormulaChecker(int Brackets[], int &size) ;// проверка правильности 
char* FormulaConverter(void); // перевод в постфиксную форму 
double FormulaCalculator(void); // вычисление результата 
int checkoper(char x);
int priority(int z);
};