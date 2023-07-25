#include <iostream>
using namespace std;

int main(){
   setlocale(LC_ALL, "Russian");
   double depositAmount, annualPercentage;
   cout << "Введите сумму вклада: ";
   while(!(cin >> depositAmount) || (cin.peek() != '\n') || depositAmount < 1)
	{
		cin.clear();
		while(cin.get() != '\n');
		cout << "Введите положительное число: ";
	}
   cout << "Введите годовой процент: ";
   while(!(cin >> annualPercentage) || (cin.peek() != '\n')  || annualPercentage < 0 || annualPercentage > 100) 
	{
		cin.clear();
		while(cin.get() != '\n');
		cout << "Введите число от 0 до 100: ";
	}
   cout << "Сумма через год с учетом капитализации процентов: "
   << depositAmount + depositAmount * annualPercentage / 100 << endl;
}
