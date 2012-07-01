#include<iostream>
#include<cstdio>
#include<boost/python/module.hpp>
#include<boost/python/def.hpp>
#include<boost/python/class.hpp>
#include<boost/python/list.hpp>
#include<boost/python/call_method.hpp>

using namespace std;
using namespace boost::python;

#define BUF 1024

class Polecenia
{
	string args;
public:
	Polecenia(list);
	list ls(string);
	list grep(list,list);
	void mail(list,list);
};

Polecenia::Polecenia(list a)
{
	for(int i = 0; i < len(a); ++i)
	{
		args.append(extract<string>(a[i]));
		args.append(" ");
	}
}

list Polecenia::ls(string s)
{
	char tmp[BUF];
	string wynik;
	FILE * p = popen(("ls " + args + " " + s).c_str(), "r");
	while(fgets(tmp, BUF, p))
		wynik.append(tmp);
	pclose(p);
	list wyn;
	stringstream ss(wynik);
	string s2;
	while(getline(ss, s2, '\n'))
		wyn.append(s2);
	return wyn;
}

list Polecenia::grep(list what, list whos)
{
	char tmp[BUF];
	string arg, wynik;
	for(int i = 0; i < len(what); ++i)
	{
		arg.append(extract<string>(what[i]));
		arg.append("\n");
	}
	FILE * p;
	string tm, s2;
	list wyn;
	for(int i = 0; i < len(whos); ++i)
	{
		tm = extract<string>(whos[i]);
		p = popen(("grep " + tm + " < " + arg).c_str(), "r");	//to nie dziala
		while(fgets(tmp, BUF, p))
			wynik.append(tmp);
		pclose(p);
		stringstream ss(wynik);
		while(getline(ss, s2, '\n'))
			wyn.append(s2);
	}
	return wyn;
}

void Polecenia::mail(list who, list what)
{
	
}

BOOST_PYTHON_MODULE(zad1)
{
	class_<Polecenia>("Polecenia", init<list>())
		.def("ls", &Polecenia::ls)
		.def("grep", &Polecenia::grep);
}


