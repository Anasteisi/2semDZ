#include <iostream>
#include "vector.h"


using namespace std;

int main()
{
	cout << "Hello World!" << endl;

	Vector<int> qwerty;//konstruktor po umolchniyu
	cout << qwerty.getSize() << endl;//razmer
	qwerty.print();//vyvod

	int manArray[5] = { 1,2,3,4,5 };//massiv

	Vector<int> arr2(5, manArray);//konstruktor s size i massivom elementov
	cout << arr2.getSize() << endl;

	arr2.print();//vyvod arr2
	arr2.setElem(0, 55); // arr2.array[0] = 55;
	arr2.setElem(1, 66);  // arr2.array[0] = 66;
	arr2.print();//vyvod arr2

	arr2.setSize(4);//obrezka
	arr2.print();//vyvod arr2

	arr2.setSize(15);//+0 do 15 elementov
	arr2.print();//vyvod arr2

	arr2.deleteElem(1);//delete 2 element
	arr2.print();//vyvod arr2

	arr2.addElem(44);//+ b -- v konec
	arr2.print();//vyvod arr2

	Vector<int> arr3(arr2);//konstruktor copy
	arr3.print();

	arr2.addElem(56);//+ i -- v konec
	arr2.print();
	arr3.print();
	cout << "Sortirovka po vozrastaniju => " << endl;
	arr2.sortElems();
	arr2.print();

	Vector<int>* arr_pointers = new Vector<int>[3]; //dinamicheskii massiv objectov

	for (int i = 0; i < 3; ++i)
	{
		arr_pointers[i].print();//vyvod massiva objectob
	}

	cout << Vector<int>::getArrCount() << endl;

	delete[] arr_pointers; //ochistka pamyati (destruktor)

	cout << "arr2.getSize = " << arr2.getSize() << endl;
	try
	{
		cout << arr2.getElem(16) << endl;
	}
	catch (range_error rng_err)
	{
		cout << rng_err.what() << endl;
	}

	St* AAA = new St[5];//massiv struktur
	for (int i = 0; i < 5;i++)//zapolnenie
		AAA[i].A = i;

	AAA[0].B = "Ivanov";
	AAA[1].B = "Petrov";
	AAA[2].B = "Sidorov";
	AAA[3].B = "Belov";
	AAA[4].B = "Afanas'ev";

	cout << "Massiv struktur: " << endl;
	for (int i = 0; i < 5;i++)
		cout << AAA[i].A << " : " << AAA[i].B << endl;//vyvod massiva struktur

	Vector<St> STT(5, AAA);//konstruktor klassa
	cout << "Klass struktur: " << endl;
	STT.print();//vyvod klassa struktur 

	STT.sortElems(VozrB);//sortirovka po alfavitu -- polu B
	cout << "Sortirovka po alfavitu: " << endl;
	STT.print();//vyvod otsortirovannogo massiva

	system("pause");
	return 0;
}

//    //Potencial'no opasnyi kod -- v try
//    try
//    {
//        double x=1, y=0;
//        if (y == 0)
//            throw runtime_error("Division by zero");

//        if (x == 1)
//            throw 'c';

//        double div = x/y;
//        throw -1;
//    }
//    catch (runtime_error rt_err)
//    {
//        cout << rt_err.what() << endl;
//    }
//    catch(char* err_str)
//    {
//        cout << err_str << endl;
//    }
//    catch(int err_num)
//    {
//        cout<<"error code: "<<err_num<<endl;
//    }
//    catch (...)
//    {
//        cout <<"Smth happened" <<endl;
//    }
