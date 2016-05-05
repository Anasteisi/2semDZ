#include <iostream>

using namespace std;

template <typename T>
class Vector
{
public:
	int getSize() const;//razmer massiva
	void setSize(int n);//obrezaet massiv ili dopolnyaet 1 do n
	int getElem(int index) const;//znachenie elem[index]
	void setElem(int index, T val);//zadat' znachenie elem[index]
	void deleteElem(int index);//udalit' elem[index]
	void addElem(T val);//+ elem[size]==val
	void addElemMiddle(int index, T val);//+elem[index]==val
	static int getArrCount() {return arrCount;}//tekuschee kolichestvo sozdannyh objectov
										 //Vector& TArrayCompare(Vector& anotherArr);//Sravnenie massivov po razmeru, vorvrat ukazatelya na bolshii ???
	void sortElems(bool (*res)(T,T));//sortirovka elementov

	Vector();//konstruktor po umolchaniyu
	Vector(int n, const T* arr);//konstruktor s size i massivom elementov
	Vector(const Vector& sec_arr);//konstruktor copy
								  //Vector(int n, bool random = false);//konstruktor n randomnyh elementov, esli false //???

	~Vector();//destruktor

	void print() const;//vyvod na konsol'

private:
	int size;//razmer massiva
	T* array;//ukazatel' na massiv
	static int arrCount;//kolichestvo objectov classa
};

template <typename T>
int Vector<T>::getSize() const //razmer massiva
{
	return size;
}

template <typename T>
void Vector<T>::setSize(int n) //obrezaet massiv ili dopolnyaet 1 do n
{
	T* tmpArr = new T[n];
	if (n <= size)
	{
		for (int i = 0; i < n; ++i)
			tmpArr[i] = array[i];
	}
	else
	{
		for (int i = 0; i < size; ++i)
			tmpArr[i] = array[i];
		for (int i = size ; i < n; ++i)
			tmpArr[i] = 1;
	}

	size = n;//novyi razmer
	delete[] array;//ochistka starogo massiva
	array = tmpArr;//perezapis' ukazatelya
}

template <typename T>
int Vector<T>::getElem(int index) const //znachenie elem[index]
{
	if (index > size - 1)
		throw range_error("Index is greater than size");//oshibka
	return array[index];
}

template <typename T>
int Vector<T>::arrCount = 0;

template <typename T>
void Vector<T>::setElem(int index, T val) //zadat' znachenie elem[index]
{
	array[index] = val;
}

template <typename T>
void Vector<T>::deleteElem(int index) //udalit' elem[index]
{
	if (index > size - 1 || index < 0)
		return;//net takogo

	T* tmp = new T[size - 1];//novyi massiv
	int j = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i == index)
			continue;//propustit'

		tmp[j] = array[i];
		++j;
	}
	--size;
	delete[] array;//ochistka starogo massiva
	array = tmp;//perezapis' ukazatelya
}

template <typename T>
void Vector<T>::addElem(T val) //+ elem[size]==val
{
	T* tmp = new T[size + 1];
	for (int i = 0; i < size; ++i)
		tmp[i] = array[i];
	tmp[size] = val;
	++size;
	delete[] array;
	array = tmp;
}

template <typename T>
void Vector<T>::addElemMiddle(int index, T val) //+elem[index]==val
{
	T* tmp = new T[size + 1];
	int j = 0;
	for (int i = 0; i < size + 1; ++i)
	{
		if (i == index)
		{
			tmp[i] = val;
			continue;
		}

		tmp[i] = array[j];
		++j;
	}

	++size;
	delete[] array;
	array = tmp;
}

/*
template <typename T>
& Vector<T>::TArrayCompare(Vector& anotherArr) //Sravnenie massivov po razmeru, vorvrat ukazatelya na bolshii //???
{
if (anotherArr.getSize() > this->getSize())
return anotherArr;
else
return *this;
}
*/

template <typename T>
bool Vozr(T a, T b)
{
	return a > b;
}

template <typename T>
bool Ub(T a, T b)
{
	return a < b;
}

template <typename T>
void Obmen(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>
void Vector<T>::sortElems(bool(*res)(T, T))
{
	for (int i = 1;i<size;++i)
		for (int j = 0;j<size - i;++j)
			if (res(array[j], array[j + 1]) == true)
				Obmen(array[j], array[j + 1]);
}

template <typename T>
Vector<T>::Vector() //konstruktor po umolchaniyu
{
	size = 0;
	array = nullptr;
	++arrCount;
}

template <typename T>
Vector<T>::Vector(int n, const T* arr) //konstruktor s size i massivom elementov
{
	size = n;
	array = new T[size];
	for (int i = 0;i<size;++i)
		array[i] = arr[i];
	++arrCount;
}

template <typename T>
Vector<T>::Vector(const Vector& sec_arr) //konstruktor copy
{
	size = sec_arr.getSize();
	array = new T[size];
	for (int i = 0;i<size;++i)
		array[i] = sec_arr.getElem(i);
	++arrCount;
}

/*template <typename T>
Vector<T>::Vector(int n, bool random) //konstruktor n randomnyh elementov, esli false ???
{
srand(time(NULL));
size = n;
array = new int[size];

for (int i = 0; i < size; ++i)
{
if (random == false)
array[i] = 0;
else
array[i] = rand() % 10;
}
++arrCount;
}*/

template <typename T>
Vector<T>::~Vector() //destruktor
{
	delete[] array;
	--arrCount;
}

template <typename T>
void Vector<T>::print() const //vyvod massiva na konsol'
{
	for (int i = 0; i < size; ++i)
		cout << array[i] << " ";
	cout << endl;
}