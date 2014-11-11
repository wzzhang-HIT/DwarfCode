#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin;
ofstream fout;

typedef vector <string> VS;
VS line, oline;
VS saveS, saveR, saveW, saveTime;

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

string getFunc(string s)
{
	int start,end;
	
	start=s.find(":")+2;
	end=s.find("=")-1;
	return s.substr(start, end - start + 1);
}

string getCount(string s)
{
	int start,end;
	
	start=s.find("count=")+7;
	end=s.find("datatype")-2;
	return s.substr(start, end - start + 1);
}

string getTime(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=']')
		end++;
	return a.substr(start, end-start+1);
}

void getSaveTime()
{
	int i,j,n;
	string s;
	
	n=line.size();
	saveTime.clear();
	for (i=0;i<n;i++)
	{
		s=getTime(line[i],"S=[") + " " + getTime(line[i],"E=[");
		saveTime.push_back(s);
	}
}

void replaceSETime(string &a, const string &key)
{
	int start, end;
	
	
	start= a.find("S=[");
	end=start;
	
	while (a[end]!=']')
		end++;
	end++;
	while (a[end]!=']')
		end++;
	a.replace(start, end - start + 1, key);
}

void work()
{
	string s,func,funcTmp,count;
	int n,i,j,k,w;
	int endA;
	int endB;
	
	getline(fin ,s);
	line.clear();
	oline.clear();
	while (fin)
	{
		line.push_back(s);
		
		getline(fin ,s);
	}
	
	n = line.size();
	getSaveTime();
	
	i = 0;
	while (i < n)
	{
		
		func = getFunc(line[i]);
		
		//cout << func << endl;
		
		endB = endA = i;
		if (func == "MPI_Send" || func == "MPI_Recv")
		{
			j = i+1;
			count = getCount(line[i]);
			while (j < n)
			{
				funcTmp = getFunc(line[j]);
				if ((funcTmp == "MPI_Send" || funcTmp == "MPI_Recv") && (getCount(line[j]) == count))
					j++;
				else
					break;
			}
			endA = j;
		}
		
		if (func == "MPI_Send" || func == "MPI_Irecv" || func == "MPI_Wait")
		{
			j = i+1;
			count = getCount(line[i]);
			while (j < n)
			{
				funcTmp = getFunc(line[j]);
				if ( ((funcTmp == "MPI_Send" || funcTmp == "MPI_Irecv") && (getCount(line[j]) == count)) 
					|| funcTmp == "MPI_Wait")
					j++;
				else
					break;
			}
			endB = j;
		}
		
		if (endA > endB && endA > i)
		{
			//cout << i << " -- " << endA << endl;
			saveS.clear(); saveW.clear(); saveR.clear();
			
			for (j = i; j < endA; j++)
			{
				if (getFunc(line[j])=="MPI_Send")
					saveS.push_back(line[j]);
				if (getFunc(line[j])=="MPI_Recv")
					saveR.push_back(line[j]);
			}
			
			for (j=0, k=0; j < saveS.size() && k < saveR.size(); j++, k++)
			{
				oline.push_back(saveR[k]);
				oline.push_back(saveS[j]);
			}
			
			for (; k < saveR.size(); k++)
			{
				oline.push_back(saveR[k]);
			}
			
			for (; j < saveS.size(); j++)
			{
				oline.push_back(saveS[j]);
			}
			
			i = endA;
		}
		else if (endA < endB && endB > i)
		{
			//cout << i << " -- " << endB << endl;
			saveS.clear(); saveW.clear(); saveR.clear();
			
			for (j = i; j < endB; j++)
			{
				if (getFunc(line[j])=="MPI_Send")
					saveS.push_back(line[j]);
				if (getFunc(line[j])=="MPI_Irecv")
					saveR.push_back(line[j]);
				if (getFunc(line[j])=="MPI_Wait")
					saveW.push_back(line[j]);
			}
			
			for (j=0, k=0, w=0; j < saveS.size() && k < saveR.size() && w < saveW.size(); j++, k++, w++)
			{
				oline.push_back(saveR[k]);
				oline.push_back(saveW[w]);
				oline.push_back(saveS[j]);
			}
			
			for (; k < saveR.size() && w < saveW.size(); k++, w++)
			{
				oline.push_back(saveR[k]);
				oline.push_back(saveW[w]);
			}
			
			for (; k < saveR.size(); k++)
			{
				oline.push_back(saveR[k]);
			}
			
			for (; w < saveW.size(); w++)
			{
				oline.push_back(saveW[w]);
			}
			
			for (; j < saveS.size(); j++)
			{
				oline.push_back(saveS[j]);
			}
			
			i = endB;
		}
		else
		{
			oline.push_back(line[i]);
			i++;
		}
		
	}
	
	for (i = 0; i < oline.size(); i++)
		replaceSETime(oline[i],saveTime[i]);
	
	for (i = 0; i < oline.size(); i++)
		fout << oline[i] << endl;
}

int main(int argc,char *argv[])
{
	string name,oname;
	int i;
	
	//char ts1[16] = "0.symbol";
	//char ts2[12] = "0.order";
	//char ts3[10] = "1";

	if (argc != 4)
	{
		cout<<"Usage: order inputfile outputfile $n"<<endl;
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
			cout << "Bad file name: [" << name << "]!\n" << endl;
            return 0;
		}

		fout.open(oname.c_str());

        cout << "Order(V1.0) by Yuanjing" << endl;
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
