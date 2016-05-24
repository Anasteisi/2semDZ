#include <iostream>
#include <cstring>
#include <fstream>
#include "Header.h"

using namespace std;

int main(int argc, char** argv)
{

	if (argc < 2)//tol'ko 1 argument -- imya programmy
	{
		cout << "Nazvanie faila ne zadano!" << endl << endl;
		system("pause");
		return 0;
	}

	char* filename = argv[1];//nazvanie faila

	bool cikl1 = true;//cikl Menu1
	int do1 = 0, do2 = 0, do3 = 0, do4 = 0;//vybor deistviya v switch
	char str[255];//stroka BD
	int kstr = 0;//zapisei v BD

	ofstream fileBD(filename, ios::app);//otkrytie ili sozdanie faila
	if (!fileBD.is_open())//ne otkryvaetsya
	{
		Error(filename);
		return 0;
	}

	fileBD.close();//poka zakryt'

	while (cikl1 = true)
	{
		Menu1();
		cin >> do1;//deistvie v Menu1

		switch (do1)
		{
		case 1:
			break;//zavershit' switch
		case 2:
		{
			fstream fileBD(filename, ios::out);//otkrytie faila na perezapis'
			cout << endl << "Vvedite kolichestvo zapisei." << endl << endl;
			cin >> kstr;
			cout << endl << "Vvedite zapisi cherez Enter." << endl << endl;
			Shapka();
			cin.ignore();//pervaya stroka bez endl
			ZapVF(fileBD, kstr, str);//zapis' strok s konsoli v fail
			fileBD.close();
			break;//zavershit' switch
		}
		default://inache
			return 0;//zavershit' programmu
		}//zakrytie do1

		bool cikl2 = true;//cikl Menu2

		while (cikl2 == true)
		{
			fstream fileBD(filename, ios::in);//otkrytie faila na chtenie
			kstr = KolStrok(fileBD);
			BD baza;
			fileBD.seekg(0);//vozvrat v nachalo faila

			for (int i = 0; i < kstr; i++)
			{
				fileBD.getline(str, 255);
				ZapisBD zapis;
				strtozapis(str, zapis);//stroka --> ZapisBD zapis
				baza.add_zapisBD(zapis);//zapolnenie bazy
			}

			fileBD.close();
			Menu2();
			cin >> do2;//deistvie v Menu2
			switch (do2)
			{
			case 1:
			{
				baza.printBD();
				break;
			}
			case 2:
			{
				fileBD.open(filename, ios::app);//otkrytie faila na dozapis'
				cout << endl << "Vvedite novuju stroku." << endl << endl;
				Shapka();
				ZapVF(fileBD, 2, str);//endl i stroka
				fileBD.close();
				break;//zavershit' switch
			}
			case 3:
			{
				int id = 0;
				cout << "Vvedite ID nenuzhnoi zapisi" << endl;
				cin >> id;
				baza.delete_zapisBD(id);
				fileBD.open(filename, ios::out);//perezapis' faila
				baza.zapis_v_f(fileBD);
				fileBD.close();
				baza.printBD();
				break;
			}
			case 4:
			{
				Menu3();//deistvie v Menu3
				cin >> do3;

				char key[255];//slovo dlya Menu3
				int k = 0;//chislo dlya Menu3

				switch (do3)
				{
				case 1:
				{
					cout << endl << "Vvedite Familiju." << endl << endl;
					cin >> key;
					baza.find_zapisBDF(key);
					break;
				}
				case 2:
				{
					cout << endl << "Vvedite Imya." << endl << endl;
					cin >> key;
					baza.find_zapisBDI(key);
					break;
				}
				case 3:
				{
					cout << endl << "Vvedite Otshestvo." << endl << endl;
					cin >> key;
					baza.find_zapisBDO(key);
					break;
				}
				case 4:
				{
					cout << endl << "Vvedite god rozhdeniya" << endl << endl;
					cin >> k;
					baza.find_zapisBDG(k);//poisk po polu GodR
					break;
				}
				case 5:
				{
					cout << endl << "Vvedite ID" << endl << endl;
					cin >> k;
					baza.find_zapisBDID(k);;//poisk po polu ID
					break;
				}
				case 6:
					break;//vozvrat v Menu2
				case 7:
				{
					cikl2 = false;//vozvrat v Menu1
					break;
				}
				default:
					return 0;
				}//do3
				break;
			}//4
			case 5:
			{
				cikl2 = false;//vozvrat v Menu1
				break;
			}
			default:
				return 0;
			}//do2
		}//cikl2
	}//cikl1
}