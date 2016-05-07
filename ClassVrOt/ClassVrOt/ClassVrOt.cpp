#include "ClassVrOt.h"
#include <ctime>
#include <iostream>
#include <exception>

using namespace std;

Time::Time()
{
	h = 12; m = 13; s = 14;//po umolchaniyu
}

Time::Time(char* str)//konstruktor so strokoi
{
	char *context;//peremennaya dlya strtok
	char *hh = strtok_s(str, ":", &context);//chast' stroki do :
	char *mm = strtok_s(NULL, ":", &context);
	char *ss = strtok_s(NULL, " ", &context);//ostatok stroki
	if (hh == nullptr || mm == nullptr || ss == nullptr)//zashita ot stroki ne vida HH:MM:SS
	{
		h = 23; m = 59; s = 59;
	}
	else
	{
		h = atoi(hh);//int chas
		m = atoi(mm);//int min
		s = atoi(ss);//int sec
		if (h < 0 || h > 23) h = 23;//0<=h<=23
		if (m < 0 || m > 59) m = 59;
		if (s < 0 || s > 59) s = 59;
	}
}

Time::Time(int hour, int min, int sec)
{
	h = hour;
	m = min;
	s = sec;
}

Time::~Time()
{
	h = 0; m = 0; s = 0;//obnulenie
}

void Time::print()
{
	cout << "Vremya " << h << ":" << m << ":" << s << endl;
}

Time Time::operator-(Time vr1)
{
	int vsec1 = vr1.h * 60 * 60 + vr1.m * 60 + vr1.s;//vremya v secundah -- nachalo sobytiya
	int vsec2 = h * 60 * 60 + m * 60 + s;//vremya v secundah -- konec sobytiya
	int vsec = vsec2 - vsec1;//raznost'
	int hres = vsec / 60 / 60;
	int mres = (vsec - hres * 60 * 60) / 60;
	int sres = vsec - hres * 60 * 60 - mres * 60;
	Time res(hres, mres, sres);
	return res;
}