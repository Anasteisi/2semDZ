#include <ctime>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void Menu1()
{
	cout << endl << "Glavnoe menu. Deistvie:" << endl;
	cout << "Rabota s imejusheisya bazoi -- 1" << endl;
	cout << "Sozdanie novoi bazy -- 2" << endl;
	cout << "Zavershenie programmy -- lybaya drugaya klavisha" << endl << endl;
}

void Menu2()
{
	cout << endl << "Menu. Dal'neishie deistviya:" << endl;
	cout << "Vyvesti bazu na ekran -- 1" << endl;
	cout << "Dobavit' novujy stroku -- 2" << endl;
	cout << "Udalit' stroku -- 3" << endl;
	cout << "Poisk zapisi -- 4" << endl;
	cout << "Glavnoe menu -- 5" << endl;
	cout << "Zavershenie programmy -- lybaya drugaya klavisha" << endl << endl;
}

void Menu3()
{
	cout << endl << "Vyberite pole, po kotoromu sovershit' poisk:" << endl;
	cout << "Familia -- 1" << endl;
	cout << "Imya -- 2" << endl;
	cout << "Otchestvo -- 3" << endl;
	cout << "God rozhdeniya -- 4" << endl;
	cout << "ID -- 5" << endl;
	cout << "Menu -- 6" << endl;
	cout << "Glavnoe menu -- 7" << endl;
	cout << "Zavershenie programmy -- lybaya drugaya klavisha" << endl << endl;
}

void Shapka()
{
	cout << endl << "Familia Imya Otshestvo God rozhdeniya ID" << endl << endl;
}

void Error(char* filename)
{
	cout << "Fail " << filename << " otkryt' nevozmozhno." << endl;
	system("pause");
}

template <typename T>
struct TreeNode //uzel
{
	bool color; //true - black, false - red
	T data;//dannye
	TreeNode* left;//levyi potomok
	TreeNode* right;//pravyi potomok
	TreeNode* parent;//predok

	TreeNode(T zapis)
	{
		color = true;//black po umolchaniyu
		data = zapis;//dannye
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

template <typename T>
class RBtree
{
private:
	int size;//kolichestvo uzlov
	TreeNode<T>* root;//koren' dereva
	TreeNode<T>* NIL;//list dereva (odin)

	void rotate_left(TreeNode<T>* uzel);//left povorot
	void rotate_right(TreeNode<T>* uzel);//right povorot
	void painting(TreeNode<T>* uzel);//raskraska (balans)
	void deleting(TreeNode<T>* uzel);//udalenie uzla
	void balans(TreeNode<T>* uzel);//balansirovka dereva posle udaleniya uzla

	void delete_subtree(TreeNode<T>* subroot);//udalit' podderevo

	void add_item_subtree(TreeNode<T>* subroot, T&);//dobavit' uzel v podderevo
	bool find_subtree(TreeNode<T>* subroot, T key, T& res);//poisk v poddereve po ID
	void traverse_subtree(TreeNode<T>* subroot);//obhod poddereva
	void traverse_subtree_FIOG(TreeNode<T>* subroot, T key, bool(*res)(T, T));//obhod poddereva, poisk zapisei po key
	void delete_item_subtree(TreeNode<T>* subroot, T key);//udalit' element key iz poddereva
	void subtree_to_f(TreeNode<T>* subroot, fstream &fileBD); //obhod dereva, zapis' v fail
public:
	RBtree();//konstruktor
	~RBtree();//destruktor
	void add_item(T&);//dobavit' uzel v derevo
	bool find(T key, T& res);//poisk v dereve po ID, vyvod zapisi
	void traverse();//obhod dereva
	void traverse_FIOG(T key, bool(*res)(T, T));//obhod dereva, vyvod zapisei key
	void delete_item(T key);//udalit' element key
	void tree_to_f(fstream &fileBD); //zapis' v fail
};

struct ZapisBD //data v uzle
{
	char* Familia;//familia
	char* Imya;//imya
	char* Otshestvo;//otchestvo
	int GodR;//god rozhdeniya
	int ID;//unikal'nyi nomer

	ZapisBD()
	{
		Familia = nullptr;
		Imya = nullptr;
		Otshestvo = nullptr;
		GodR = 0;
		ID = 0;
	}

	ZapisBD(char* F, char* I, char* O, int G, int id)
	{
		Familia = F;
		Imya = I;
		Otshestvo = O;
		GodR = G;
		ID = id;
	}
};


int KolStrok(fstream &fileBD)//kolichestvo strok v faile
{
	char str[255];
	int kstr = 0;
	while (!fileBD.eof())//poka ne konec faila
	{
		fileBD.getline(str, 256);//stroka
		kstr++;
	}
	return kstr;
}

void strtozapis(char* str, ZapisBD& zapis)//perevod stroki v strukturu
{
	char *context;//otslezhivayet, kakoe slovo chitaetsya
	char *Familia = strtok_s(str, " ", &context);//slovo do " "
	char* Imya = strtok_s(NULL, " ", &context);//sledujushee slovo
	char* Otshestvo = strtok_s(NULL, " ", &context);//sledujushee slovo
	char* sGodR = strtok_s(NULL, " ", &context);//sledujushee slovo
	char* sID = strtok_s(NULL, " ", &context);//sledujushee slovo

	int GodR = atoi(sGodR);//chislo
	int ID = atoi(sID);//chislo

	int FL = strlen(Familia);//dlina elementa Familia
	if (zapis.Familia == nullptr)//pustoi
	{
		zapis.Familia = new char[FL + 1];//novaya stroka zadannoi dliny
		strcpy_s(zapis.Familia, FL + 1, Familia);//kopirovanie Familia v BD.Familia
	}
	else
	{
		delete[] zapis.Familia;//ochistit'
		zapis.Familia = new char[FL + 1];
		strcpy_s(zapis.Familia, FL + 1, Familia);
	}

	int IL = strlen(Imya);
	if (zapis.Imya == nullptr)
	{
		zapis.Imya = new char[IL + 1];
		strcpy_s(zapis.Imya, IL + 1, Imya);
	}
	else
	{
		delete[] zapis.Imya;
		zapis.Imya = new char[IL + 1];
		strcpy_s(zapis.Imya, IL + 1, Imya);
	}

	int OL = strlen(Otshestvo);
	if (zapis.Otshestvo == nullptr)//pustoi
	{
		zapis.Otshestvo = new char[OL + 1];
		strcpy_s(zapis.Otshestvo, OL + 1, Otshestvo);
	}
	else
	{
		delete[] zapis.Otshestvo;//ochistit'
		zapis.Otshestvo = new char[FL + 1];
		strcpy_s(zapis.Otshestvo, OL + 1, Otshestvo);
	}

	zapis.GodR = GodR;
	zapis.ID = ID;
}

void ZapVF(fstream &fileBD, int kstr, char* str)//zapis' strok s konsoli v fail
{
	for (int i = 0; i < kstr - 1; i++)
	{
		cin.getline(str, 255);//stroka
		fileBD << str << endl;//zapis' v fail
	}
	cin.getline(str, 255);
	fileBD << str;//bez endl
}


bool operator<(ZapisBD& zapis1, ZapisBD& zapis2)//peregruzka <
{
	if (zapis1.ID < zapis2.ID)
		return true;
	else
		return false;
}

bool operator==(ZapisBD& zapis1, ZapisBD& zapis2)//peregruzka ==
{
	if (zapis1.ID == zapis2.ID)
		return true;
	else
		return false;
}

class BD
{
private:
	RBtree<ZapisBD> tree;
public:
	BD() {}
	~BD() {}
	void add_zapisBD(ZapisBD&);
	bool find_zapisBDID(int ID);//poisk zapisi po unikal'nomu ID
	void printBD();//vyvod bazy
	void find_zapisBDF(char* Familia);//poisk zapisi po familii -- s povtoreniem
	void find_zapisBDI(char* Imya);//poisk zapisi po imeni -- s povtoreniem
	void find_zapisBDO(char* Otshestvo);//poisk zapisi po otchestvu -- s povtoreniem
	void find_zapisBDG(int GodR);//poisk zapisi po godu rozhdeniya -- s povtoreniem
	void delete_zapisBD(int ID);//udalenie zapisi iz bazy
	void zapis_v_f(fstream &fileBD);
};

template <typename T>
void print(T& data)//vyvod dannyh dlya standartnyh tipov
{
	cout << data << endl;
}

template <typename T>
void RBtree<T>::rotate_left(struct TreeNode<T>* uzel)//left povorot dereva
{
	struct TreeNode<T>* y = uzel->right;
	uzel->right = y->left;
	if (y->left != NIL)
		y->left->parent = uzel;
	y->parent = uzel->parent;
	if (uzel->parent == nullptr)
		root = y;
	else
		if (uzel == uzel->parent->left)
			uzel->parent->left = y;
		else
			uzel->parent->right = y;
	y->left = uzel;
	uzel->parent = y;
}

template <typename T>
void RBtree<T>::rotate_right(struct TreeNode<T>* uzel)//right povorot dereva
{
	struct TreeNode<T>* y = uzel->left;
	uzel->left = y->right;
	if (y->right != NIL)
		y->right->parent = uzel;
	y->parent = uzel->parent;
	if (uzel->parent == nullptr)
		root = y;
	else
		if (uzel == uzel->parent->right)
			uzel->parent->right = y;
		else
			uzel->parent->left = y;
	y->right = uzel;
	uzel->parent = y;
}

template <typename T>
void RBtree<T>::painting(struct TreeNode<T>* uzel)//raskraska
{
	if (uzel->parent == nullptr) //root
	{
		uzel->color = true;
		return;
	}
	else //ne root
	{
		if (uzel->parent->color == true)//parent black, OK
			return;
		else//parent red
		{
			struct TreeNode<T>* unc;//potomok predpredka != predok
			if (uzel->parent == uzel->parent->parent->right)
				unc = uzel->parent->parent->left;
			else
				unc = uzel->parent->parent->right;

			if (unc == NIL || unc->color == true) //unc black or null
			{
				if (uzel->parent == uzel->parent->parent->left)//prpr->left->uzel
				{
					if (uzel == uzel->parent->right)//uzel=prpr->left->right
					{
						rotate_left(uzel->parent);
						painting(uzel->parent);//rekursiya
					}
					else//uzel=prpr->left->left
					{
						uzel->parent->color = true;
						uzel->parent->parent->color = false;
						rotate_right(uzel->parent->parent);
						return;
					}
				}
				else//prpr->right->uzel
				{
					if (uzel == uzel->parent->left)//uzel=prpr->right->left
					{
						rotate_right(uzel->parent);
						painting(uzel->parent);//rekursiya
					}
					else//uzel=prpr->right->right
					{
						uzel->parent->color = true;
						uzel->parent->parent->color = false;
						rotate_left(uzel->parent->parent);
						return;
					}
				}

			}//unc black or null
			else//unc red
			{
				uzel->parent->color = true;
				unc->color = true;
				uzel->parent->parent->color = false;
				painting(uzel->parent->parent);//rekursiya
			}//unc red
		}//parent red
	}//ne root
}

template <typename T>
void RBtree<T>::balans(TreeNode<T>* uzel)//balansirovka dereva posle udaleniya uzla
{
	if (uzel != NIL)
	{
		while (uzel != root && uzel->color == true)//black !=root
		{
			if (uzel == uzel->parent->left) //uzel -- left potomok
			{
				TreeNode<T>* bro = uzel->parent->right;//potomok parenta != uzel
				if ((bro != NIL) && (bro->color == false))//red
				{
					bro->color = true;//black
					uzel->parent->color = false;//red
					rotate_left(uzel->parent);//left povorot
					bro = uzel->parent->right;//pereopredelenie
				}
				if (bro->left->color == true && bro->right->color == true) //oba potomka bro black
				{
					bro->color = false;//red
					uzel = uzel->parent;//pereopredelenie
				}
				else
					if (bro != NIL)//bro -- black, !NIL
					{
						if (bro->right->color == true)
						{
							bro->left->color = true;
							bro->color = false;
							rotate_right(bro);//left povorot
							bro = uzel->parent->right;//pereopredelenie
						}
						bro->color = uzel->parent->color;//perekraska
						uzel->parent->color = true;//black
						bro->right->color = true;//black
						rotate_left(uzel->parent);//left povorot
						uzel = root;//pereopredelenie
					}
			}
			else //uzel -- right potomok
			{
				TreeNode<T>* bro = uzel->parent->left;
				if (bro->color == false) //red
				{
					bro->color = true;//black
					uzel->parent->color = false;//red
					rotate_right(uzel->parent);//right povorot
					bro = uzel->parent->left;//pereopredelenie
				}
				if (bro->right->color == true && bro->left->color == true) //oba potomka bro black
				{
					bro->color = false;//red
					uzel = uzel->parent;//pereopredelenie
				}
				else
					if (bro != NIL)
					{
						if (bro->left->color == true) //black
						{
							bro->right->color = true;//black
							bro->color = false;//red
							rotate_left(bro);//left povorot
							bro = uzel->parent->left;//pereopredelenie
						}
						bro->color = uzel->parent->color;//perekraska
						uzel->parent->color = true;//black
						bro->left->color = true;//black
						rotate_right(uzel->parent);//right povorot
						uzel = root;//pereopredelenie
					}
			}
		}
		uzel->color = true;// root black
	}
}

template <typename T>
void RBtree<T>::deleting(TreeNode<T>* uzel) //udaleine uzla
{
	TreeNode<T>* x;
	TreeNode<T>* y;

	if (uzel->left == NIL || uzel->right == NIL) //odin potomok !NIL
	{
		y = uzel;
	}
	else //oba potomka !NIL
	{
		y = uzel->right;//right potomok
		while (y->left != NIL)
			y = y->left;//samyi levyi potomok pravogo potomka uzel
	}
	if (y->left != NIL)
		x = y->left;
	else
		x = y->right;
	if (x != NIL)
		x->parent = y->parent;
	if (y->parent != NIL)
		if (y == y->parent->left) //y -- left potomok
			y->parent->left = x;
		else //y -- right potomok
			y->parent->right = x;
	else //y->parent == NIL
		root = x;
	if (y != uzel)
		uzel->data = y->data;
	if (y->color == true)//black
		balans(x);//perekraska
	free(y);
}

template <typename T>
RBtree<T>::RBtree() //pustoe derevo
{
	NIL = nullptr;
	root = NIL;
	size = 0;
}

template <typename T>
void RBtree<T>::delete_subtree(TreeNode<T> *subroot) //udalenie poddereva, rekursiya
{
	if (subroot->left != nullptr)
		delete_subtree(subroot->left);//udalenie levogo podddereva
	if (subroot->right != nullptr)
		delete_subtree(subroot->right);//udalenie pravogo podddereva
	delete subroot;
}

template <typename T>
RBtree<T>::~RBtree()
{
	if (size == 0) return; //derevo pusto
	delete_subtree(root); //udalenie dvuh podderev'ev i kornya
}

template <typename T>
void RBtree<T>::add_item_subtree(TreeNode<T> *subroot, T& zapis) //dobavit' uzel v podderevo
{
	if (zapis < subroot->data) //dobavlenie uzla v left podderevo
	{
		if (subroot->left == NIL)//net left uzlov
		{
			subroot->left = new TreeNode<T>(zapis);//new uzel
			subroot->left->color = false;//red
			subroot->left->left = NIL;//privyazka left lista
			subroot->left->right = NIL;//privyazka right lista
			subroot->left->parent = subroot;//privyazka predka
			painting(subroot->left);//raskraska
			return;
		}
		add_item_subtree(subroot->left, zapis);//inache -- rekursiya
	}
	else //dobavlenie uzla v right podderevo
	{
		if (subroot->right == NIL)//net right uzlov
		{
			subroot->right = new TreeNode<T>(zapis);//new uzel
			subroot->right->color = false;//red
			subroot->right->left = NIL;//privyazka left lista
			subroot->right->right = NIL;//privyazka right lista
			subroot->right->parent = subroot;//privyazka predka
			painting(subroot->right);//raskraska
			return;
		}
		add_item_subtree(subroot->right, zapis);//inache -- rekursiya
	}
}

template <typename T>
void RBtree<T>::add_item(T& zapis) //dobavlenie uzla
{
	if (root == NIL)//derevo pustoe
	{
		root = new TreeNode<T>(zapis);//koren'
		root->left = NIL;
		root->right = NIL;
		root->parent = NIL;
		++size;
		return;
	}
	add_item_subtree(root, zapis);//nepustoe
	++size;
}

template <typename T>
bool RBtree<T>::find_subtree(TreeNode<T> *subroot, T key, T &res) //poisk uzla po key v poddereve, zapis' data v res
{
	if (key == subroot->data)//naiden
	{
		res = subroot->data;
		return true;
	}

	if (key < subroot->data) //key < inf -- poisk v left poddereve
	{
		if (subroot->left == NIL)
			return false;
		find_subtree(subroot->left, key, res);
	}
	else //key > inf -- poisk v right poddereve
	{
		if (subroot->right == NIL)
			return false;
		find_subtree(subroot->right, key, res);
	}
}

template <typename T>
bool RBtree<T>::find(T key, T& res) //poisk v dereve
{
	if (root == NIL) //derevo pustoe
	{
		cout << "Empty!" << endl;
		return false;
	}
	return find_subtree(root, key, res); //rekursiya
}

template <typename T>
void RBtree<T>::traverse_subtree(TreeNode<T>* subroot) //obhod poddereva
{
	if (subroot->left != NIL)//left podderevo
		traverse_subtree(subroot->left);//rekursiya
	print(subroot->data);//vyvod zapisi
	if (subroot->right != NIL)//right podderevo
		traverse_subtree(subroot->right);//rekursiya
}

template <typename T>
void RBtree<T>::traverse() //obhod dereva, vyvod na konsol'
{
	if (root == NIL)
	{
		cout << "Empty!" << endl;
		return;
	}
	traverse_subtree(root);//koren' & podderevya
}


template <typename T>
void printf(T& data, fstream &fileBD)
{
	fileBD << data << endl;
}

void printf(ZapisBD& zapis, fstream &fileBD)
{
	fileBD << zapis.Familia << " " << zapis.Imya << " " << zapis.Otshestvo << " " << zapis.GodR << " " << zapis.ID << endl;
}

void printf_last(ZapisBD& zapis, fstream &fileBD)
{
	fileBD << zapis.Familia << " " << zapis.Imya << " " << zapis.Otshestvo << " " << zapis.GodR << " " << zapis.ID;
}

template <typename T>
void RBtree<T>::subtree_to_f(TreeNode<T>* subroot, fstream& fileBD) //obhod dereva, zapis' v fail
{
	TreeNode<T>* max = root;//max elem dlya vyvoda v fail (last stroka bez endl)
	while (max->right != NIL)
		max = max->right;

	if (subroot->left != NIL)//left podderevo
		subtree_to_f(subroot->left, fileBD);//rekursiya

	if (subroot == max)
		printf_last(subroot->data, fileBD);
	else
		printf(subroot->data, fileBD);//zapis v fail

	if (subroot->right != NIL)//right podderevo
		subtree_to_f(subroot->right, fileBD);//rekursiya
}

template <typename T>
void RBtree<T>::tree_to_f(fstream &fileBD) //zapis' v fail
{
	if (root == NIL)
	{
		cout << "Empty!" << endl;
		return;
	}
	subtree_to_f(root, fileBD);//koren' & podderevya
}

template <typename T>
void RBtree<T>::traverse_subtree_FIOG(TreeNode<T>* subroot, T key, bool(*res)(T, T)) //obhod poddereva, poisk zapisei key, 
																					 //res == ravenstvo elementov
{
	if (subroot->left != NIL)//left podderevo
		traverse_subtree_FIOG(subroot->left, key, res);//rekursiya
	if (res(key, subroot->data) == true)//podhodit
		print(subroot->data);//vyvod zapisi
	if (subroot->right != NIL)//right podderevo
		traverse_subtree_FIOG(subroot->right, key, res);//rekursiya
}

template <typename T>
void RBtree<T>::traverse_FIOG(T key, bool(*res)(T, T)) //obhod dereva, poisk zapisei key, res == ravenstvo elementov, vyvod na konsil'
{
	if (root == NIL) //derevo pustoe
	{
		cout << "Empty!" << endl;
		return;
	}
	traverse_subtree_FIOG(root, key, res); //rekursiya
}

template <typename T>
void RBtree<T>::delete_item_subtree(TreeNode<T>* subroot, T key)//udalit' element key iz poddereva
{
	if (key == subroot->data)
	{
		if (subroot->right == NIL)
			if (subroot->left == NIL)
				if (subroot->parent != nullptr)//ne root
				{
					if (subroot == subroot->parent->right)
						subroot->parent->right = NIL;
					else
						subroot->parent->left = NIL;
				}
				else//root
					subroot = NIL;
			else
				deleting(subroot);
		else
			deleting(subroot);
		return;
	}

	if (key < subroot->data)
	{
		if (subroot->left == NIL)
			return;
		delete_item_subtree(subroot->left, key);
	}
	else
	{
		if (subroot->right == NIL)
			return;
		delete_item_subtree(subroot->right, key);
	}
}

template <typename T>
void RBtree<T>::delete_item(T key)//udalit' element key iz dereva
{
	if (root == NIL) //derevo pustoe
	{
		cout << "Empty!" << endl;
		return;
	}
	delete_item_subtree(root, key);
}

void print(ZapisBD& zapis)//vyvod zapisi, peregruzka
{
	cout << zapis.Familia << " " << zapis.Imya << " " << zapis.Otshestvo << " " << zapis.GodR << " " << zapis.ID << endl;
}

void BD::add_zapisBD(ZapisBD& zapis) //dobavlenie zapisi v BD
{
	tree.add_item(zapis);
}

bool BD::find_zapisBDID(int ID)//poisk zapisi po unikal'nomu ID
{
	ZapisBD key;
	key.ID = ID;
	ZapisBD otvet;

	bool res = tree.find(key, otvet);
	if (res == true) //perezapis' otvet
	{
		Shapka();
		print(otvet);
	}
	return res;
}

void BD::printBD()//vyvod BD na konsol'
{
	Shapka();
	tree.traverse();
}


bool ravF(ZapisBD zapis1, ZapisBD zapis2)//zapisi == po familii
{
	if (strcmp(zapis1.Familia, zapis2.Familia) == 0)
		return true;
	else
		return false;
}

bool ravI(ZapisBD zapis1, ZapisBD zapis2)//zapisi == po imeni
{
	if (strcmp(zapis1.Imya, zapis2.Imya) == 0)
		return true;
	else
		return false;
}

bool ravO(ZapisBD zapis1, ZapisBD zapis2)//zapisi == po otchestvu
{
	if (strcmp(zapis1.Otshestvo, zapis2.Otshestvo) == 0)
		return true;
	else
		return false;
}

bool ravG(ZapisBD zapis1, ZapisBD zapis2)//zapisi == po imeni
{
	if (zapis1.GodR == zapis2.GodR)
		return true;
	else
		return false;
}

void BD::find_zapisBDF(char* Familia) //poisk zapisi po familii -- s povtoreniem
{
	ZapisBD key(Familia, "", "", 0, 0);
	Shapka();
	tree.traverse_FIOG(key, ravF);
}

void BD::find_zapisBDI(char* Imya) //poisk zapisi po imeni -- s povtoreniem
{
	ZapisBD key("", Imya, "", 0, 0);
	Shapka();
	tree.traverse_FIOG(key, ravI);
}

void BD::find_zapisBDO(char* Otshestvo) //poisk zapisi po otchestvu -- s povtoreniem
{
	ZapisBD key("", "", Otshestvo, 0, 0);
	Shapka();
	tree.traverse_FIOG(key, ravO);
}

void BD::find_zapisBDG(int GodR) //poisk zapisi po godu rozhdeniya -- s povtoreniem
{
	ZapisBD key;
	key.GodR = GodR;
	Shapka();
	tree.traverse_FIOG(key, ravG);
}

void BD::delete_zapisBD(int ID)
{
	ZapisBD key("", "", "", 0, ID);
	tree.delete_item(key);
}

void BD::zapis_v_f(fstream &fileBD)
{
	tree.tree_to_f(fileBD);
}