#include <iostream>

using namespace std;

template <typename T>//uzel spiska
struct Node
{
	T data;//znachenie elementa
	Node* next;//ukazatel' na adres sled elementa
	Node* prev;//ukazatel' na adres pred elementa

	Node(T d) { data = d; next = nullptr; prev = nullptr; }
};

template <typename T>
class List
{
private:
	Node<T>* first;//ukazatel' na 1 element spiska
	Node<T>* last;//ukazatel' na poslesnii element spiska
	int size;//razmer spiska
public:
	List();//konstruktor po umolchaniju
	~List();//destruktor

	void push_front(const T& data);//+element v nachalo
	void push_back(const T& data);//+element v konec

	bool pop_front(T& data);//-element iz nachala
	bool pop_back(T& data);//-element iz konca

	template <typename T1>
	friend ostream& operator<<(ostream&, List<T1>&);//vyvod spiska

	class Iterator
	{
	private:
		Node<T>* p;//ukazatel' na element spiska
	public:

		Iterator(Node<T>* pp = nullptr) { p = pp; }//konstruktor

		T& operator*() const { return p->data; }//peregruzka operatora razymynovaniya !!!

		Iterator& operator++()//peregruzka ++x
		{
			p = p->next;
			return *this;
		}

		Iterator operator++(int)//peregruzka x++
		{
			Iterator it(p);
			p = p->next;
			return it;
		}

		Iterator& operator--()//peregruzka --x !!!
		{
			p = p->prev;
			return *this;
		}

		Iterator operator--(int)//peregruzka x-- !!!
		{
			Iterator it(p);
			p = p->prev;
			return it;
		}

		bool operator!=(Iterator it)//peregruzka sravnaniya !!!
		{
			return p != it.p;
		}
		bool operator==(Iterator it)
		{
			return p == it.p;
		}
	};

	Iterator begin();//vozvrat iteratora nachala spiska
	Iterator end();//vozvrat iteratora konca spiska

	bool remove(Iterator it, T& data);//-element[index]
};

template <typename T> //konstruktor po umolchaniju
List<T>::List()
{
	first = last = nullptr;
	size = 0;
}

template <typename T> //destruktor
List<T>::~List()
{
	while (first != nullptr)//udalenie uzlov poka chto-to est'
	{
		last = first->next;//adres sledujushego elementa
		delete first;//ochistka pamyati
		first = last;//perehod k sled elementu
	}
}

template <typename T> //+element v nachalo
void List<T>::push_front(const T &data)
{
	Node<T>* newNode = new Node<T>(data);

	if (size == 0)//esli spisok pustoi
	{
		first = newNode;
		last = newNode;
		size = 1;
		return;
	}

	newNode->next = first;//svyaz' pervogo elementa s dobavlennym
	first->prev = newNode;//svyaz' dobavlennogo elementa s pervym
	first = newNode;//pervyi element
	++size;

}

template <typename T> //+element v konec
void List<T>::push_back(const T &data)
{
	Node<T>* newNode = new Node<T>(data);//novyi uzel

	if (size == 0)//esli spisok pustoi
	{
		first = newNode;
		last = newNode;
		size = 1;
		return;
	}

	last = first;

	while (last->next != nullptr)//poisk poslednego elementa
		last = last->next;

	newNode->prev = last;//svyaz' dobavlennogo elementa s predydushim
	last->next = newNode;//svyaz' poslednego elementa s dobavlennym
	last = newNode;//poslednii element
	++size;
}

template <typename T> //-element iz nachala
bool List<T>::pop_front(T &data)
{
	if (size == 0) //pustoi spisok
		return false;

	if (first->next == nullptr) //1 element
		cout << "nullptr!" << endl;

	Node<T>* tmp = first;//udalyaemyi element
	data = first->data;//dannye
	first = first->next;
	delete tmp;
	first->prev = nullptr;

	--size;
	return true;
}

template <typename T> //-element iz konca
bool List<T>::pop_back(T &data)
{
	if (size == 0) //pustoi spisok
		return false;

	Node<T>* last = first;
	if (size > 1)
	{
		while (last->next->next != nullptr)
			last = last->next;

		data = last->next->data;
		delete last->next;

		last->next = nullptr;
		--size;
	}
	else  //=1
	{
		data = first->data;
		delete first;
		first = nullptr;
		size = 0;
	}
	return true;
}

template <typename T>//vozvrat iteratora nachala spiska
typename List<T>::Iterator List<T>::begin()
{
	if (first == nullptr) return Iterator();
	while (first->prev != nullptr)
		first = first->prev;
	return Iterator(first);
}

template <typename T> //vozvrat iteratora konca spiska
typename List<T>::Iterator List<T>::end()
{
	last = first;
	if (last == nullptr) return Iterator();
	while (last->next != nullptr)
		last = last->next;
	return Iterator(last);
}



template <typename T> //udalenie elementa [index]
bool List<T>::remove(typename List<T>::Iterator it, T& data)
{
	Iterator curr = begin(); //nachalo spiska
	if (curr == it) //pervyi element
	{
		return pop_front(data);
	}

	Node<T>* tmp = first;//ukazatel' na 1-i element

	while (tmp->next != nullptr) //po  spisku (cherez ukazaateli)
	{
		Iterator nextIt(tmp->next); //iterator sled elementa
		if (nextIt == it) //sovpadenie
		{
			data = *nextIt;//dannye
			Node<T>* nextElem = tmp->next;//adres sled elementa
			tmp->next = nextElem->next;
			if (nextElem->next != nullptr)
				nextElem->next->prev = tmp;
			delete nextElem;
			return true;
		}
		tmp = tmp->next;//sled element
	}

	return false;//net takogo
}


/*template <typename T> //udalenie elementa [index]
bool List<T>::remove(typename List<T>::Iterator it, T& data)
{
Iterator curr = end(); //konec spiska
if (curr == it) //poslednii element
{
return pop_back(data);
}

Node<T>* tmp = first;//ukazatel' na 1-i element
while (tmp->next != nullptr)
tmp = tmp->next;

while (tmp->prev != nullptr) //po  spisku (cherez ukazaateli)
{
Iterator prevIt(tmp->prev); //iterator pred elementa
if (prevIt == it) //sovpadenie
{
data = *prevIt;//dannye
Node<T>* prevElem = tmp->prev;//adres pred elementa
tmp->prev = prevElem->prev;
if (prevElem->prev != nullptr)
prevElem->prev->next = tmp;
delete prevElem;
return true;
}
tmp = tmp->prev;//pred element
}

return false;//net takogo
}*/


template <typename T>
ostream& operator<<(ostream& out, List<T>& list)
{
	if (list.size == 0)
	{
		out << "Empty list!" << endl;
		return out;
	}

	list.last = list.first;
	out << list.last->data << " ";
	while (list.last->next != nullptr)
	{
		list.last = list.last->next;
		out << list.last->data << " ";
	}

	//	typename List<T>::Iterator it = list.begin();
	//	for (; it != list.end();++it)
	//		out << *it<<" ";
	//	out << endl;

	return out;
}