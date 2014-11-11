#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;

#define MAX_DEPTH 200

ifstream fin;
ofstream fout;
typedef vector <string> VS;
vector <VS> file;
VS line;
typedef map<string, string> MapSS;

bool finish ( vector <unsigned int> p)
{	
	for (unsigned i=0;i != p.size();i++)
	{
		if (p[i] != file[i].size())
			return 0;
	}
	return 1;
}

string getPara(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=',')
		end++;
	return a.substr(start, end-start+1);
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

double getDoubleTime(const string &a, const string &key)
{
	int start, end;
	double re;
	
	start= a.find(key);
	end=start;
	while (a[end]!=']')
		end++;
	while (a[start]!='[')
		start++;
	
	sscanf(a.substr(start+1, end-start).c_str(), "%lf", &re);
	
	return re;
}

string getFunc(string s)
{
	int start,end;
	
	start=s.find(":")+1;
	end=s.find("=")-1;
	return s.substr(start, end - start + 1);
}

bool samePara(MapSS  a, MapSS  b)
{
	
	MapSS::iterator itA = a.begin();
	MapSS::iterator itB = b.begin();
	
	while (itA != a.end() && itB != b.end())
	{
		if ( ((*itA).second) != ((*itB).second) )
			return 0;
		itA++;
		itB++;
	}
	return 1;
}

bool sameTrace(const string &a, const string &b)
{
	string funcA, funcB;
	int pA,pB;
	MapSS paraA, paraB;
	
	paraA.clear();
	paraB.clear();
	
	pA = a.find("=");
	funcA = a.substr(0, pA);
	
	pB = b.find("=");
	funcB = b.substr(0, pB);
	
	if (funcA != funcB)
		return 0;
	
	if (funcA == funcB)
		return 1;

	return 0;
}

void showFunc(int count, int flag[], vector <unsigned int> p)
{
	int i;
	string func;
	int n = file.size();
	
	fout << "{ same=" << count << ": ";
	for (i = 0; i < n; i++)
	{
		if (flag[i])
			fout << i << ", ";
	}
	fout << "} " << endl;
	for (i = 0; i < n; i++)
	{
		if (flag[i])
		{
			func = getFunc(file[i][p[i]]);
			
			fout << "{ file=" << i << ", ";
			fout << "func=" << func << ", ";
			if (func == "MPI_Send")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "dest") << " ";
			}
			if (func ==  "MPI_Recv")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "source") << " ";
			}
			if (func ==  "MPI_Isend")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "dest") << " ";
				fout << getPara(file[i][p[i]], "request") << " ";
			}
			if (func == "MPI_Irecv")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "source") << " ";
				fout << getPara(file[i][p[i]], "request") << " ";
			}
			if (func == "MPI_Wait")
			{
				fout << getPara(file[i][p[i]], "request") << " ";
			}
			if (func == "MPI_Waitall")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
			}
			if (func ==  "MPI_Bcast")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "root") << " ";
			}
			if (func == "MPI_Alltoall")
			{
				fout << getPara(file[i][p[i]], "sendcount") << " ";
				fout << getPara(file[i][p[i]], "sendtype") << " ";
				fout << getPara(file[i][p[i]], "recvcnt") << " ";
				fout << getPara(file[i][p[i]], "recvtype") << " ";
			}
			if (func == "MPI_Alltoallv")
			{
				fout << getPara(file[i][p[i]], "sendcnts") << " ";
				fout << getPara(file[i][p[i]], "sendtype") << " ";
				fout << getPara(file[i][p[i]], "recvcnts") << " ";
				fout << getPara(file[i][p[i]], "recvtype") << " ";				
			}
			if (func == "MPI_Reduce")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "op") << " ";
				fout << getPara(file[i][p[i]], "root") << " ";
			}
			if (func == "MPI_Allreduce")
			{
				fout << getPara(file[i][p[i]], "count") << " ";
				fout << getPara(file[i][p[i]], "datatype") << " ";
				fout << getPara(file[i][p[i]], "op") << " ";				
			}
			if (func == "MPI_Barrier")
			{
				;
			}
			if (func == "MPI_Comm_split")
			{
				;
			}
			if (func == "MPI_Comm_dup")
			{
				;
			}
			fout << getTime(file[i][p[i]], "S=[") << ", ";
			fout << getTime(file[i][p[i]], "E=[") << ", ";
			fout << getTime(file[i][p[i]], "D=[") << ", ";
			fout << "Blank=[ ";
			fout.precision(10);
			if (p[i] == 0)
				fout << 0;
			else
				fout << getDoubleTime(file[i][p[i]], "S=[") - getDoubleTime(file[i][p[i]-1], "E=[");
			fout << " ], }" << endl;
		}
	}
}

void work()
{
	unsigned int n = file.size();
	vector <unsigned int> p ( n );
	unsigned int i, j, k;
	bool same;
	int flag[128];
	int total;
	
	for (i=0;i<n;i++)
	{
		p[i]=0;
	}
	while ( ! finish(p))
	{
		for (i = 0; i<n; i++)
			cout << p[i] << "\t";
		cout << endl;
		for (i=0;i<n;i++)
		{
			if (p[i] != file[i].size())
				cout << file[i][p[i]] << "\n";
			else
				cout << "--------------\n";
		}
		cout << endl;
		same = 1;
		if (p[0] != file[0].size())
		{
			for (i=1;i<n;i++)
			{
				if (p[i] != file[i].size())
				{
					if (!sameTrace(file[i][p[i]], file[0][p[0]]))
					{
						same = 0;
						break;
					}
				}
			}
		}
		else
			same = 0;
		
		if (same)
		{
			for (i=0;i<n;i++)
			{
				flag[i]=1;
			}
			showFunc(n, flag, p);
			
			for (i = 0; i < n; i++)
				p[i]++;			
		}
		else
		{
			int maxd_fori, maxd, reci, sum_fori;
			
			maxd = 0;
			reci = -1;
			for (i=0;i<n;i++)
			{
				if (p[i] == file[i].size())
					continue;
				
				maxd_fori = 0;
				sum_fori = 0;
				for (j=0;j<n;j++)
				{
					if (i == j)
						continue;
					
					k = p[j];
					while (k != file[j].size() && (! sameTrace(file[i][p[i]], file[j][k])) && k - p[j] < MAX_DEPTH)
						k++;
					
					if (k == file[j].size())
						k = p[j] + MAX_DEPTH;
					
					if (k - p[j] > maxd_fori)
					{
						maxd_fori = k - p[j];
						sum_fori += k - p[j];  
					}
				}
				//if (maxd_fori > maxd)
				if (sum_fori > maxd)
				{
					//maxd = maxd_fori;
					maxd = sum_fori;
					reci = i;
				}
				else if (sum_fori == maxd && reci != -1)
					if (p[i] < p[reci])
					{
						reci = i;
					}
			}
			
			total=0;
			for (i=0;i<n;i++)
			{
				flag[i]=0;
				if (p[i] == file[i].size())
					continue;
				
				if (sameTrace(file[i][p[i]], file[reci][p[reci]]))
				{
					total++;
					flag[i]=1;					
				}
			}
			showFunc(total, flag, p);
			for (i=0;i<n;i++)
			{
				if (flag[i])
					p[i]++;
			}
		}
	}
}

void readfile()
{
	string s;
	int start, end;
	
	getline(fin ,s);
	line.clear();
	while (fin)
	{
		start=s.find(":")+2;
		end=s.size();
		line.push_back(s.substr(start, end - start + 1));
		
		getline(fin ,s);
	}
	file.push_back(line);
}

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


int main(int argc,char *argv[])
{
	string nameIn;
	int i;

	//char ts1[16] = "0.logic";
	//char ts2[12] = "output.txt";
	//char ts3[10] = "4";
	
    if (argc != 4)
    {
        cout<<"Usage: combine inputfile outputfile $n\n"<<endl;
        return 0;
		
    }

	file.clear();
	nameIn.assign(argv[1]);
	//nameIn.assign(ts1);
	
  for (i=0;i<atoi(argv[3]);i++)
	//for (i=0;i<atoi(ts3);i++)
    {
        fin.open(nameIn.c_str());

        if (fin.fail())
        {
            cout << "Bad file name: [" << nameIn << "]!\n" << endl;
            return 0;
        }
		
		cout << "Combine(V1.0) by Yuanjing" << endl;
		cout << "Reading " << nameIn << "...";
			
		readfile();
			
		fin.close();
		fin.clear();
			
		cout << "Done." << endl;
		nameIn=nextName(nameIn);
    }
    
    
	fout.open(argv[2]);
	//fout.open(ts2);
	work();

	fout.close();
	fout.clear();


    return 0;
}

