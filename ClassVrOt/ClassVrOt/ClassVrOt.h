#include <iostream>
using namespace std;

class Time
{
public:
	Time();//konstruktor po umolchaniyu
	Time(char* str);//konstruktor so strokoi
	Time(int hour, int min, int sec);//konstruktor s hour:min:sec
	~Time();//destruktor
	void print();//vyvod
	Time operator-(Time);
private:
	int h, m, s;//h:m:s
};