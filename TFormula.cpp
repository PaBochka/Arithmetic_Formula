#include<iostream>
#include"TFormula.h"
using namespace std;
TFormula::TFormula(char*_Formula)
	{
	
		strcpy_s(Formula, _Formula);
		strcpy_s(Postfix_Form, "");
	}
int TFormula::FormulaChecker(int Brackets[], int &size)
{
	TStack Stack(MAX);
	int index, count;
	index = 1;
	count = 0;
	int len = strlen(Formula);
	for (int i = 0; i < len; i++)
	{
		if (Formula[i] == '(')
		{
			Stack.InsElem(index++);
		}
		else
			if (Formula[i] == ')')
			{
				if (!Stack.IsEmpty())
				{
					Brackets[size++] = Stack.DelElem();
					Brackets[size++] = index++;
				}
				else {
					Brackets[size++] = 0;
					count++;
					Brackets[size++] = index++;
				}
			}
	}
	while (!Stack.IsEmpty())
	{
		count++;
		Brackets[size++] = Stack.DelElem();
		Brackets[size++] = 0;
	}
		return count;
	}
	

char*TFormula::FormulaConverter(void)
{
	TStack Stack(MAX); int temp = strlen(Postfix_Form); int size = 0; int brackets[50]; int countErr=0;
	countErr=FormulaChecker(brackets, size);
	int len = strlen(Formula); int prior; char tmp; char num;
	for (int i = 0; i<len; i++)
		if (!checkoper(Formula[i]))
		{
			Postfix_Form[temp++] = Formula[i];
		}
		else
				if (Stack.IsEmpty())
					Stack.InsElem(Formula[i]);
				else
				{
					prior = priority(Formula[i]);					//+
					if (!prior)										//x
						Stack.InsElem(Formula[i]);
					else {
						tmp = Stack.DelElem();
						if (prior>priority(tmp))							//x+y+z
						{	
							if ((Formula[i] != ')') || (tmp != '('))
							{
								Stack.InsElem(tmp);
								Stack.InsElem(Formula[i]);
							}					//1-3-2-4
						}
						else
						{
							if (prior == priority(tmp))
							{
								if ((tmp != ')') && (Formula[i] != '(')&&(Formula[i]!=')')&&(tmp!='('))
								{
									Postfix_Form[temp++] = tmp;
									Stack.InsElem(Formula[i]);
								}

							}
							else{
								if ((tmp != ')') && (tmp!='('))
									Postfix_Form[temp++] = tmp;
								num = Formula[i];
								if (num == ')')							//1+2*(3-2)-4     1232-*-4+
								{
									do
									{
										if (!Stack.IsEmpty())
										tmp = Stack.DelElem();
										if (tmp != '(')
											Postfix_Form[temp++] = tmp;
									} while (tmp != '(');
								}
								else
								{
									if (!Stack.IsEmpty())
										num = Stack.DelElem();
									if ((prior <= priority(num)) && (num != '(') && (Formula[i] != ')'))
									{
										Postfix_Form[temp++] = num;
										Stack.InsElem(Formula[i]);
									}
									else {
										Stack.InsElem(num);/* Stack.InsElem(tmp);*/
									}
								}
							}
						}
					}
				}
	while (!Stack.IsEmpty())
		Postfix_Form[temp++] = Stack.DelElem();
	Postfix_Form[temp++] = '\0';
	for (int l = 0; l < temp; l++)
		if ((Postfix_Form[l] == ')') || (Postfix_Form[l] == '('))
		{
			strcpy_s(Postfix_Form, ""); break;
		}
	try
	{
		if (countErr != 0)
			throw ExceptionParenthesis(1);
		return Postfix_Form;
	}
	catch (ExceptionParenthesis exp)
	{
		exp.display();
		return (char*)("");
	}
}
						int TFormula::checkoper(char x)
						{
							int res=0;
							switch (x)
							{
							case '+':
							case '/':
							case '-':
							case '*':
							case '(':
							case ')': {res = 1; break; }
							}
							return res;
						}
						int TFormula::priority(int z)
						{
							int res;
							if (z == '(')
								res = 0;
							if (z == ')') res = 1;
							if ((z == '+') || (z == '-')) res = 2;
							if ((z == '*') || (z == '/')) res = 3;
							return res;
						}

						TELEM TFormula::FormulaCalculator(void)
						{
							TStack Stack; int size = 0; int brackets[50]; int countErr = 0;
							countErr = FormulaChecker(brackets, size);
							int temp; TELEM Preobr; TELEM result = 0;
							temp = strlen(Postfix_Form);
							int i; TELEM op1, op2; op1 = 0; op2 = 0; TELEM res = 0;
							for (i = 0; i < temp; i++)
							{
								if ((Postfix_Form[i] >= '0') || (Postfix_Form[i] <= '9'))
								{
									if (!checkoper(Postfix_Form[i]))
									{
										Preobr = (Postfix_Form[i] - '0');
										Stack.InsElem(Preobr);
									}
									else
									{
										if (!Stack.IsEmpty())
											op1 = Stack.DelElem();
										if (!Stack.IsEmpty())
											op2 = Stack.DelElem();
										switch (Postfix_Form[i])
										{
											res = 0;
										case '+':{res = op2 + op1; Stack.InsElem(res); break; }
										case '/':{
											try
											{
												if (op1 == 0)
													throw ExceptionZero(4);
												res = op2 / op1;
												Stack.InsElem(res);
												break;
											}
											catch (ExceptionZero cnt)
											{
												cnt.display();
												return NULL;
											}
										}
										case '-':{res = op2 - op1; Stack.InsElem(res); break; }
										case '*':{res = op2 * op1; Stack.InsElem(res); break; }
										}
									}
								}
								else {
									cout << "ERROR" << endl; return TELEM(NULL);
								}
							}
							if (!Stack.IsEmpty())
							result = Stack.DelElem();
							else result = 0;
							try
							{
								if (countErr != 0)
									throw ExceptionParenthesis(2);
									if (temp % 2 == 0)
									throw ExceptionOperands(3);

								return result;
							}
							catch (ExceptionParenthesis exp)
							{
								return NULL;
							}
							catch (ExceptionOperands excep)
							{
								excep.display();
								return NULL;
							}		
						}

