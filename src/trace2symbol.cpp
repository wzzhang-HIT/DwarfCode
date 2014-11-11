#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream fin;
ofstream fout;

string my_itos(int i)
{
        string r;
        char c[128];

        sprintf(c, "%d\0", i);
        r += c;

        return r;
}

string nextName(string name)
{
        string n;
        int posi;

        posi = name.find(".");
        n = my_itos (atoi( name.substr(0, posi).c_str() ) + 1) + name.substr( posi, name.size() ) + "\0";
        return n;
}

void work()
{
	string s;
	int count = 0;
	
	getline(fin ,s);
	while (fin)
	{
		//Line 1, Func Name
		count++;
		fout << count << ": ";
		
		int funcPosi = s.find("Function:") ;
		fout << s.substr(funcPosi + 10, s.size()) << "= ";
		
		//Line 2, Parameters
		getline(fin ,s);
		
		//Line 3, Parameters' values
		getline(fin ,s);
		int paraPosi = s.find("Paravalues:") ;
		fout << s.substr(paraPosi + 14, s.size());
		
		//Line 4, StartTime
		getline(fin ,s);
		int timePosi = s.find("Starttime = ") ;
		fout << "S=" << s.substr(timePosi + 12, s.size()) << " ";
		
		//Line 5, Func Name
		//getline(fin ,s);	
		
		//Line 6, EndTime
		getline(fin ,s);
		timePosi = s.find("Endtime = ") ;
		fout << "E=" << s.substr(timePosi + 10, s.size()) << " ";
		
		//Line 7, DurTime
		getline(fin ,s);
		timePosi = s.find("Durtime = ") ;
		fout << "D=" << s.substr(timePosi + 10, s.size()) << endl;
		
		getline(fin ,s);		
	}
}

int main(int argc,char *argv[])
{
	string name,oname;
	int i;
	
	//char ts1[16] = "0.trace";
	//char ts2[12] = "0.symbol";
	//char ts3[10] = "1";


	if (argc != 4)
	{
		cout<<"Usage: trace2symbol inputfile outputfile $n\n"<<endl;
		return 0;
	}
	
	name.assign(argv[1]);
	//name.assign(ts1);
	oname.assign(argv[2]);
	//oname.assign(ts2);
	for (i=0;i<atoi(argv[3]);i++)
	//for (i=0;i<atoi(ts3);i++)
	{
		fin.open(name.c_str());
	
		if (fin.fail())
		{
			cout<<"Bad file name!\n"<<endl;
			return 0;
		}
	
		fout.open(oname.c_str());	
	
		cout<<"Trace2Symbol(V1.0) by Yuanjing"<<endl;
	
		cout << "Dealing with " << name << "...";

		work();

		fin.close();
		fout.close();
		fin.clear();
		fout.clear();
		
		cout << "Done." << endl;
    name=nextName(name);
		oname=nextName(oname);
	}
	return 0;
}
