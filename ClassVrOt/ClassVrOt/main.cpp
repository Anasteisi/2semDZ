#include <iostream>
#include "ClassVrOt.h"

using namespace std;

int main()
{
	cout << "ClassVrOt" << endl;

	char str[100];//stroka

	cout << "Vvedite stroku vida HH:MM:SS" << endl;
	cin.getline (str, 100);//schityvanie stroki

	Time vremya (str);//vyzov konstruktora so strokoi
	vremya.print();//vyvod

	cout << "Vvedite stroku vida HH:MM:SS -- vremya, kogda sobytie nachalos'" << endl;
	cin.getline(str, 100);//schityvanie stroki
	Time vr1(str);//vyzov konstruktora so strokoi
	vr1.print();//vyvod

	cout << "Vvedite stroku vida HH:MM:SS -- vremya, kogda sobytie zakonchilos'" << endl;
	cin.getline(str, 100);//schityvanie stroki
	Time vr2(str);//vyzov konstruktora so strokoi
	vr2.print();//vyvod

	Time otvet = vr2 - vr1;//podshet raznitsy

	cout << "Mezhdu ukazannymi promezhutkami proshlo ";
	otvet.print();

	system("pause");
	return 0;
}