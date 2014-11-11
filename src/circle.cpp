//Much Thanks to Luo Sui-qian

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string.h>


using namespace std;


ifstream fin;
ofstream fout;
typedef vector <string> VS;
VS line;
VS tmpLine;

#define maxn 400001
#define EPS 1e-9
#define MAX_COUNT_DIFF 0.1


int wa[maxn],wb[maxn],wv[maxn],daws[maxn];
typedef struct S_save
{
	int s,e,clen;
}S_save;

	
S_save save[maxn];
int flag[maxn];
int rem[maxn];
int used[maxn];

bool comp(const S_save &a, const S_save &b)
{
	if (a.e-a.s != b.e-b.s)
		return a.e-a.s > b.e-b.s;
	if (a.s != b.s)
		return a.s < b.s;
	if (a.e != b.e)
		return a.e < b.e;
	return a.clen < b.clen;
}

string my_itos(int i)
{
        string r;
        char c[128];

        sprintf(c, "%d\0", i);
        r += c;

        return r;
}

string my_dtos(double i)
{
        string r;
        char c[128];

        sprintf(c, "%lf\0", i);
        r += c;

        return r;
}

inline int cmp(int *r,int a,int b,int l)
{ return (r[a]==r[b]&&r[a+l]==r[b+l]); }

//Luo Sui-qian's code
//Much thanks to the author
void algorithm_da(int *r,int *sa,int n,int m)
{
	int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++) daws[i]=0;
    for(i=0;i<n;i++) daws[x[i]=r[i]]++;
    for(i=1;i<m;i++) daws[i]+=daws[i-1];
    for(i=n-1;i>=0;i--) sa[--daws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
       for(p=0,i=n-j;i<n;i++) y[p++]=i;
       for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
       for(i=0;i<n;i++) wv[i]=x[y[i]];
       for(i=0;i<m;i++) daws[i]=0;
       for(i=0;i<n;i++) daws[wv[i]]++;
       for(i=1;i<m;i++) daws[i]+=daws[i-1];
       for(i=n-1;i>=0;i--) sa[--daws[wv[i]]]=y[i];
       for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
       x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}

int rank[maxn],height[maxn];

void calheight(int *r,int *sa,int n)
{
     int i,j,k=0;
     for(i=1;i<=n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++]]=k)
     for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}

int RMQ[maxn];
int mm[maxn];
int best[20][maxn];

void initRMQ(int n)
{
     int i,j,a,b;
     for(mm[0]=-1,i=1;i<=n;i++)
     mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
     for(i=1;i<=n;i++) best[0][i]=i;
     for(i=1;i<=mm[n];i++)
     for(j=1;j<=n+1-(1<<i);j++)
     {
       a=best[i-1][j];
       b=best[i-1][j+(1<<(i-1))];
       if(RMQ[a]<RMQ[b]) best[i][j]=a;
       else best[i][j]=b;
     }
     return;
}

int askRMQ(int a,int b)
{
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}

int lcp(int a,int b)
{
    int t;
    a=rank[a];b=rank[b];
    if(a>b) {t=a;a=b;b=t;}
    return(height[askRMQ(a+1,b)]);
}

int r[maxn],sa[maxn];


string getPara(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=',')
		end++;
	return a.substr(start, end - start + 1);
}

string getPurePara(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=',')
		end++;
	while (a[start]!=' ')
		start++;
	return a.substr(start+1, end - start + 1);
}

string getTime(const string &a, const string &key)
{
	int start, end;
	
	start= a.find(key);
	end=start;
	while (a[end]!=']')
		end++;
	return a.substr(start, end - start + 1);
}

void replaceTime(string &a, const string &key, double b)
{
	int start, end;
	string c;
	
	start= a.find(key);
	end=start;
	c="Blank=[ " + my_dtos(b) + " ]";
	while (a[end]!=']')
		end++;
	a.replace(start, end - start + 1, c);
}


void readfile()
{
	string s, single, sameNStr;
	string func;
	int start, end;
	int sameN, i;
	
	getline(fin ,s);
	line.clear();
	while (fin)
	{
		start= s.find("same=");
		end=start;
		while (s[end]!=':')
			end++;
		
		sameNStr = s.substr(start+5, end-start-5);
		sameN = atoi( sameNStr.c_str() );
		
		single = "{ UniPara: same=" + sameNStr + ", ";
		
		getline(fin ,s);
		func = getPara(s, "func=");
		func = func.substr(5, func.length() - 6);
		single += "func=" + func + ", ";
		cout << "func=" << func << endl;
		
		if (func == "MPI_Send")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";
		}
		if (func == "MPI_Recv")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";			
		}
		if (func == "MPI_Isend")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";
		}
		if (func == "MPI_Irecv")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";	
		}
		if (func == "MPI_Wait")
		{
			;
		}
		if (func == "MPI_Waitall")
		{
			single += getPara(s, "count") + " ";
		}
		if (func ==  "MPI_Bcast")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";
			single += getPara(s, "root") + " ";
		}
		if (func == "MPI_Alltoall")
		{
			single += getPara(s, "sendcount") + " ";
			single += getPara(s, "sendtype") + " ";
			single += getPara(s, "recvcnt") + " ";
			single += getPara(s, "recvtype") + " ";
		}
		if (func == "MPI_Alltoallv")
		{
			single += getPara(s, "sendcnts") + " ";
			single += getPara(s, "sendtype") + " ";
			single += getPara(s, "recvcnt") + " ";
			single += getPara(s, "recvtype") + " ";	
		}
		if (func == "MPI_Reduce")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";
			single += getPara(s, "op") + " ";
			single += getPara(s, "root") + " ";
		}
		if (func == "MPI_Allreduce")
		{
			single += getPara(s, "count") + " ";
			single += getPara(s, "datatype") + " ";
			single += getPara(s, "op") + " ";				
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
		single += "} { DiffPara: ";
			
		for (i=0;i<sameN;i++)
		{
			single += getPara(s, "file") + " ";
			single += getPara(s, "Blank=[") + " ";
			
			if (func == "MPI_Send")
			{
				single += getPara(s, "dest") + " ";
			}
			if (func ==  "MPI_Recv")
			{
				single += getPara(s, "source") + " ";
			}
			if (func ==  "MPI_Isend")
			{
				single += getPara(s, "dest") + " ";
				single += getPara(s, "request") + " ";
			}
			if (func == "MPI_Irecv")
			{
				single += getPara(s, "source") + " ";
				single += getPara(s, "request") + " ";
			}
			if (func == "MPI_Wait")
			{
				single += getPara(s, "request") + " ";
			}
			if (func == "MPI_Waitall")
			{
				;
			}
			if (func ==  "MPI_Bcast")
			{
				;
			}
			if (func == "MPI_Alltoall")
			{
				;
			}
			if (func == "MPI_Alltoallv")
			{
				;				
			}
			if (func == "MPI_Reduce")
			{
				;
			}
			if (func == "MPI_Allreduce")
			{
				;				
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
			
			getline(fin ,s);			
		}
		
		single += "}";
		
		
		line.push_back(single);
	}
}

void init()
{
	int i,j;

	readfile();
}

bool sameCountPara(string x, string y)
{
	int ix = atoi(x.c_str()), iy = atoi(y.c_str());
	
	return (fabs(double(ix) - iy) / (double(ix)+EPS) < MAX_COUNT_DIFF);

}

int getRValue(int x, int &count)
{
	int i;
	string funcX, funcI;
	string paraX, paraI;
	
	funcX = getPara(line[x], "func=");
	funcX = funcX.substr(5, funcX.length() - 6);
	for (i=0;i<x;i++)
	{
		funcI = getPara(line[i], "func=");
		funcI = funcI.substr(5, funcI.length() - 6);
		if (funcX != funcI)
			continue;
		if (funcX == "MPI_Send")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;
		}
		if (funcX == "MPI_Recv")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;	
		}
		if (funcX == "MPI_Isend")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;
		}
		if (funcX == "MPI_Irecv")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;
		}
		if (funcX == "MPI_Wait")
		{
			;
		}
		if (funcX == "MPI_Waitall")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
		}
		if (funcX ==  "MPI_Bcast")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;
			if ( getPara(line[i], "root") != getPara(line[x], "root") )
				continue;
		}
		if (funcX == "MPI_Alltoall")
		{
			if ( ! sameCountPara( getPurePara(line[i], "sendcount") , getPurePara(line[x], "sendcount") ) )
				continue;
			if ( getPara(line[i], "sendtype") != getPara(line[x], "sendtype") )
				continue;
			if ( ! sameCountPara( getPurePara(line[i], "recvcnt") , getPurePara(line[x], "recvcnt") ) )
				continue;
			if ( getPara(line[i], "recvtype") != getPara(line[x], "recvtype") )
				continue;
		}
		if (funcX == "MPI_Alltoallv")
		{
			if ( ! sameCountPara( getPurePara(line[i], "sendcnt") , getPurePara(line[x], "sendcnt") ) )
				continue;
			if ( getPara(line[i], "sendtype") != getPara(line[x], "sendtype") )
				continue;
			if ( ! sameCountPara( getPurePara(line[i], "recvcnt") , getPurePara(line[x], "recvcnt") ) )
				continue;
			if ( getPara(line[i], "recvtype") != getPara(line[x], "recvtype") )
				continue;			
		}
		if (funcX == "MPI_Reduce")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;
			if ( getPara(line[i], "op") != getPara(line[x], "op") )
				continue;
			if ( getPara(line[i], "root") != getPara(line[x], "root") )
				continue;
		}
		if (funcX == "MPI_Allreduce")
		{
			if ( ! sameCountPara( getPurePara(line[i], "count") , getPurePara(line[x], "count") ) )
				continue;
			if ( getPara(line[i], "datatype") != getPara(line[x], "datatype") )
				continue;
			if ( getPara(line[i], "op") != getPara(line[x], "op") )
				continue;			
		}
		if (funcX == "MPI_Barrier")
		{
			;
		}
		if (funcX == "MPI_Comm_split")
		{
			;
		}
		if (funcX == "MPI_Comm_dup")
		{
			;
		}
		
		return r[i];
	}
	count++;
	return count;
}

void addTitleFor(string ti, int x)
{
	int p = line[save[x].s].rfind("FOR TIMES");
		
	if (p!=string::npos)
	{
		while (line[save[x].s][p]!='>')
			p++;
		p+=2;
		line[save[x].s].insert(p, ti);
	}
	else
	{
		line[save[x].s] = ti + line[save[x].s];
	}
}

/*
void reClen()
{
	int i,j,n;
	int stock[1024];
	int top;
	
	n=line.size();
	for (i=0;i<n;i++)
	{
		if (line[i].find()
	}
}*/

int main(int argc,char *argv[])
{
    int i,j,jj,k,n,now,r_count,save_count,u_count;
	//char ts1[16] = "output.txt";
	//char ts2[16] = "BTcircle.txt";
	
	
	
	
	if (argc != 3)
    {
        cout << "Usage: circle inputfile outputfile\n" << endl;
        return 0;		
    }
	
	
	fin.open(argv[1]);
	//fin.open(ts1);
	fout.open(argv[2]);
	//fout.open(ts2);
	
    init();
	
	fin.close();
	
	
	do
	{
		n=line.size();
		r_count=0;
		for(i=0;i<n;i++)
		{		
			r[i]=getRValue(i,r_count);
			cout << r[i] << endl;
		}
		r[n]=0;
	
		algorithm_da(r,sa,n+1,128);
		calheight(r,sa,n);
		for(i=1;i<=n;i++) 
			RMQ[i]=height[i];
		initRMQ(n);
		
		save_count = 0;
		for(i=1;i<n;i++)
		{
			for(j=0;j+i<n;j+=i)
			{
				k=lcp(j,j+i);
				
				if (k>=1)
				{
					jj=j-1;
					while (jj>j-i && jj>=0 && r[jj]==r[jj+i])
						jj--;
					if (jj>=0 && jj==j-i && r[jj]==r[jj+i])
						continue;
					if (k+j-jj-1>=i)
					{
						save[save_count].s=jj+1;
						save[save_count].e=(k+j+i-jj-1)/i*i+jj;
						save[save_count].clen=i;
						save_count++;
					}
				}
			}
		}
		memset(flag,0,sizeof(flag));
		memset(rem,0,sizeof(rem));
	
		sort(save,save+save_count,comp);
		
		u_count=0;
		for (i=0;i<save_count;i++)
		{
			k=1;
			for (j=save[i].s;j<=save[i].e;j++)
			{
				if (flag[j])
				{
					k=0;
					break;
				}
				if (j!=save[i].s && line[j].find("CLEN")!=string::npos)
				{
					k=0;
					break;
				}
				if (j!=save[i].e && line[j].find("END")!=string::npos)
				{
					k=0;
					break;
				}
			}
			if (k)
			{
				for (j=save[i].s;j<=save[i].e;j++)
				{
					flag[j]=1;
					if (j>=save[i].s+save[i].clen)
						rem[j]=1;
				}
				used[u_count++]=i;
			}
		}
	
		for (i=0;i<u_count;i++)
			cout << save[used[i]].s << " " << save[used[i]].e << " " << save[used[i]].clen << endl;
	
		for (i=0;i<u_count;i++)
		{
			int t,w,e;
			double sum, dBlank;
			string sBlank;
			
			j=used[i];			
			t=(save[j].e-save[j].s+1) / save[j].clen;
			e=save[j].s + save[j].clen - 1;
			
			addTitleFor("< FOR TIMES=" + my_itos(t) + ", CLEN=" + my_itos(save[j].clen) + " > ", j);
			line[ e ] = line[ e ] + " < FOR END > ";
			
			for (k = save[j].s; k <= e; k++)
			{
				sum=0;
				for (w = 1;w < t; w++)
				{					
					sBlank = getTime(line[k + w*save[j].clen ], "Blank=[");
					sscanf(sBlank.c_str(), "Blank=[%lf",&dBlank);
					sum+=dBlank;
				}
				replaceTime( line[ k ], "Blank=[", sum/(t-1));
				
			}
		}
		
		tmpLine.clear();
		for (i=0;i<n;i++)
		{
			if (!rem[i])
			{
				tmpLine.push_back(line[i]);
			}
		}
		
		n=tmpLine.size();
		line.clear();
		for (i=0;i<n;i++)
		{
			line.push_back(tmpLine[i]);
		}		
	}while (u_count != 0);
		
	//reClen();
	n=line.size();	
	for (i=0;i<n;i++)
	{
		fout << line[i] << endl;
	}
	fout.close();
    return 0;
}
