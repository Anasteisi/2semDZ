#include <iostream>
#include "hh.h"

using namespace std;

int main()
{
	cout << "Hello World!" << endl;
	cout << "Manual work with list" << endl;
	Node<int> first(0);//pervyi uzel spiska
	Node<int>* element = &first;//ukazatel' na pervyi element (first)
	for (int i = 1; i < 4; ++i)
	{
		Node<int>* tmp = new Node<int>(i);//3 uzla
		element->next = tmp;//svyaz' so sled
		tmp->prev = element;//svyaz' s pred
		element = tmp;//smeschenie pred elementa na sosdannyi
	}

	element = &first;//pervaya yacheika

	cout << element->data << "\n";//0

	cout << "One: ";//012
	for (int i = 1; i < 4; ++i)
	{
		if (element != nullptr)
			cout << element->data << "\t";
		element = element->next;
	}
	cout << element->data << "\t";//3 - poslednee znachenie

	cout << "Two: ";//obratno 3210
	for (int i = 1; i < 5; ++i)
	{
		if (element != nullptr)
			cout << element->data << "\t";
		element = element->prev;
	}

	cout << endl;

	cout << "Working with list through the containter class" << endl;
	List<int>* intList = new List<int>;
	cout << *intList;
	intList->push_back(1);//1
	intList->push_back(2);//1 2
	intList->push_front(3);//3 1 2
	intList->push_back(10);//3 1 2 10
	intList->push_front(11);//11 3 1 2 10
	intList->push_back(15);//11 3 1 2 10 15
	cout << *intList << endl;
	intList->push_front(34);//34 11 3 1 2 10 15
	intList->push_front(55);//55 34 11 3 1 2 10 15
	intList->push_back(345);//55 34 11 3 1 2 10 15 345
	intList->push_front(733);//733 55 34 11 3 1 2 10 15 345
	intList->push_front(7);//7 733 55 34 11 3 1 2 10 15 345
	cout << *intList << endl;

	List<int>::Iterator it = intList->end();
	int data;

	intList->remove(it--, data);
	cout << "Removed last element" << endl;
	cout << *intList << "\n";

	intList->remove(--it, data);
	cout << "Removed last but one element" << endl;
	cout << *intList << "\n";

	delete intList;
	system("pause");
	return 0;
}