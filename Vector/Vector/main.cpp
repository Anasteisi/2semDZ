#include <iostream>
#include "vector.h"


using namespace std;

int main()
{
	cout << "Hello World!" << endl;

	Vector<int> qwerty;//konstruktor po umolchniyu
	cout << qwerty.getSize() << endl;//razmer
	qwerty.print();//vyvod

	char manArray[5] = {'g','h','j','k','l'};//massiv

	Vector<char> arr2(5, manArray);//konstruktor s size i massivom elementov
	cout << arr2.getSize() << endl;

	arr2.print();//vyvod arr2
	arr2.setElem(0, 'p'); // arr2.array[0] = p;
	arr2.setElem(1, 'm');  // arr2.array[0] = m;
	arr2.print();//vyvod arr2

	arr2.setSize(5);//obrezka
	arr2.print();//vyvod arr2

	arr2.setSize(15);//+0 do 15 elementov
	arr2.print();//vyvod arr2

	arr2.deleteElem(1);//delete 2 element
	arr2.print();//vyvod arr2

	arr2.addElem('b');//+ b -- v konec
	arr2.print();//vyvod arr2

	Vector<char> arr3(arr2);//konstruktor copy
	arr3.print();

	arr2.addElem('i');//+ i -- v konec
	arr2.print();
	arr3.print();

	arr2.print();
	cout << "Sortirovka => ";
	arr2.sortElems(Ub);
	arr2.print();

	//Vector<int>* arr_pointer = new Vector<int>(10, true);//dinamicheskoe sozdanie objecta cherez ukazatel'(10 randomnyh elementov) ???
	//arr_pointer->print(); //???

	Vector<char>* arr_pointers = new Vector<char>[3]; //dinamicheskii massiv objectov

	for (int i = 0; i < 3; ++i)
	{
		arr_pointers[i].print();//vyvod massiva objectob
	}
	
	//Vector<int> arr_cmp = qwerty.TArrayCompare(arr2);//arr_cmp=max(qwerty,arr2) ???
	//arr_cmp.print();// ???

	//cout << arr_pointer->getArrCount() << endl; //???
	cout << Vector<char>::getArrCount() << endl;

	//delete arr_pointer; //ochistka pamyati (destruktor) ???
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
